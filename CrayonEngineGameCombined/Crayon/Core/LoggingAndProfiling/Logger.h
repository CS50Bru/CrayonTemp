#pragma once

#include<iostream>
#include<mutex>
#include<ostream>
#include<sstream>
#include"Timing/Timer.h"

//To do: this is absolutely unusable. You can't just call Logger::log(); you have to first get a reference to the logger? No idea what I was thinking but this needs to be redone (or just have a static log() function that gets the singleton instance automatically or whatever)

//The logger is a Meyers' Singleton. I think this makes sense, because code that gets called durin the static initialization phase might need it.

//For now, it is basically just a wrapper around std::cout, with a LogLevel enum where the LogLevel of the message has to be as high as the LogLevel that the Logger's been set to to actually be printed out to the console. It has an overloaded << operator that returns a reference to the logger so that you can chain messages together, just as you can with any outstream.

//It also changes the colour of the message in the console depending on the LogLevel of the message.

//We have a LOG() macro that lets you strip out your logging code in non-release builds.

//Multithreading: threads write out to a shared stringstream (the 'active buffer'). So they do block each other when writing to the buffer, but these should only be very rare, and brief, clashes. The most expensive thing that the Logger does is to write out to wherever the final output is, and this is not blocking: when we want to do our expensive write, we briefly lock the active buffer and swap its contents out into a back buffer. We then unlock the active buffer again while we write out to the console or whatever.

namespace Crayon
{

#ifdef DEBUG
#define LOGGING_ENABLED
#endif // DEBUG


#ifdef LOGGING_ENABLED
#define LOG(message) do{Logger::get().log(message);} while (0)
#else
#define LOG(message)
#define ADD_TO_LOG_STREAM(message)
#endif //LOGGING_ENABLED


	enum class LogLevel
	{
		Debug,
		Info,
		Warning,
		Error
	};

	class Logger
	{

	private:
		Logger()=default;


	public:
		static Logger& get()
		{
			static Logger logger;
			return logger;
		}

	private:

		 LogLevel m_logLevel=LogLevel::Debug;

		 std::atomic<bool> m_running{ true };
		 
		 //activeBufferMutex also protects the actual activeBuffer as well as our condition variable and its associated bool
		 std::mutex m_activeBufferMutex;
		 std::stringstream m_activeBuffer;
		 std::condition_variable m_timeToWrite_cv;
		 bool m_timeToWrite_Bool = false;
		 
		 
		 std::stringstream m_backBuffer;

		 std::jthread m_logWriteThread;

		 ~Logger()
		 {
			 {
				 m_running = false;
				 std::lock_guard<std::mutex> lock( m_activeBufferMutex );
				 m_timeToWrite_cv.notify_one();
			 }
		 }

	public:
		template <typename T>
		Logger& log( const T& message, LogLevel logLevel=LogLevel::Debug )
		{

			std::lock_guard<std::mutex> lock( m_activeBufferMutex );

			constexpr const char* CONCOMMAND_SETCOLOR_RED = "\033[31m";
			constexpr const char* CONCOMMAND_RESETSTYLE = "\033[0m";
			constexpr const char* CONCOMMAND_SETCOLOR_GREEN = "\033[32m";

			if ( logLevel < m_logLevel )
			{
				return *this;
			}

			std::string timeAsString = Crayon::Timer::getDateTimeStringString();
			switch ( logLevel )
			{
			case LogLevel::Debug: m_activeBuffer << CONCOMMAND_SETCOLOR_GREEN;
				break;
			case LogLevel::Warning: m_activeBuffer << CONCOMMAND_SETCOLOR_RED;
				break;
			case LogLevel::Error: m_activeBuffer << CONCOMMAND_SETCOLOR_RED;
				break;
			default: m_activeBuffer << CONCOMMAND_SETCOLOR_GREEN;

			}
			m_activeBuffer << timeAsString << "  " << message << '\n' << CONCOMMAND_RESETSTYLE;
			return *this;
		}

		void startWriteThread()
		{
			m_logWriteThread= std::jthread( [&]()
				{
					while ( m_running )
					{
						std::unique_lock<std::mutex> lock( m_activeBufferMutex );
						m_timeToWrite_cv.wait( lock, [&]()
							{
								return m_timeToWrite_Bool || !m_running;
							});
						m_activeBuffer.swap( m_backBuffer );
						m_timeToWrite_Bool = false;

						lock.unlock();
						std::cout << m_backBuffer.str();//each message has been put on a new line so no need for a '\n' here
						m_backBuffer.str( "" );
						//clear() clears any error bits: if you do something weird like ss>>someInt then an error bit can be set that prevents the stream from working. It's unlikely to happen but it's worth always clearing the error bits.
						m_backBuffer.clear();
					}
				}
			);
		}


		void triggerWrite()
		{
			std::lock_guard<std::mutex> lock( m_activeBufferMutex );
			m_timeToWrite_Bool = true;
			m_timeToWrite_cv.notify_one();
		}

		template< typename T>
		Logger& operator<<( const T& value)
		{
			return log( value );
		}

	};

}