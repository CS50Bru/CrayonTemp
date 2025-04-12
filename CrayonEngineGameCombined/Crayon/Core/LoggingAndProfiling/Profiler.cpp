#include "Profiler.h"
#include<algorithm>
#include<filesystem>
#include<thread>S
#include"Timing/Timer.h"
#include"Logger.h"
#include<utility>

void Crayon::Profiler::reset()
{
	std::lock_guard<std::mutex> lock( m_profileResultsMutex );
	m_profileResults.clear();
}

void Crayon::Profiler::addToProfileResults( const ProfileResult& profileResult )
{
	std::lock_guard<std::mutex> lock( m_profileResultsMutex );
	m_profileResults.push_back( profileResult );
}

void Crayon::Profiler::writeProfileResultsToFile( const std::string& filepath, std::vector<ProfileResult>&& profileRestults, std::atomic<bool>& writeInProgress)
{
		writeInProgress = true;

			if ( !std::filesystem::exists( "Profiling" ) )
			{
				std::filesystem::create_directories( "Profiling" );
			}
		

			std::filesystem::path fullPath = std::filesystem::current_path() / "Profiling" / filepath;
			std::ofstream outStream( fullPath );


			if ( outStream.is_open() )
			{

				outStream << CHROME_VISUALIZER_HEADER;

				
				for ( auto it= profileRestults.begin();it!= profileRestults.end(); it++ )
				{
					addProfileResultToStream( *it, outStream );

					if ( std::next( it ) != profileRestults.end() )
					{
						outStream << ',';
					}
				}
				profileRestults.clear();


				outStream << CHROME_VISUALIZER_FOOTER;
				outStream.flush();
			}
		 
			writeInProgress = false;
}

void Crayon::Profiler::startFileWriteThread(const std::string& filepath)
{
	if ( m_writingToFile )
	{
		return;
	}

	m_writingToFile = true;
	std::vector<ProfileResult> profileResults;

	{
		std::lock_guard<std::mutex> resultsLock(m_profileResultsMutex);
		profileResults = std::move(m_profileResults);
		m_profileResults.clear();
	}

	std::thread fileWriteThread(&writeProfileResultsToFile, filepath, std::move(profileResults), std::ref(m_writingToFile));

	fileWriteThread.detach();
}


void Crayon::Profiler::addProfileResultToStream( const ProfileResult& profileResult, std::ostream& outStream )
{

	std::string profileName = profileResult.m_name;
	//replace all double quotes in our string with single quotes: this is just a standard safety step (JSON uses double quotes to separate things so if you
	//plug in double quotes of your own in the middle of an actual value you'll mess it up)
	std::replace( profileName.begin(), profileName.end(), '"', '\'' );

		outStream << "{"
		<< "\"cat\":\"function\","
		<< "\"dur\":" << (profileResult.m_endMicroSeconds - profileResult.m_startMicroSeconds) << ','
		<< "\"name\":\"" << profileName << "\","
		<< "\"ph\":\"X\","
		<< "\"pid\":0,"
		<< "\"tid\":" << profileResult.m_threadID << ","
		<< "\"ts\":" << profileResult.m_startMicroSeconds
		<< "}";
}



Crayon::Profiler& Crayon::Profiler::get()
{
	static Profiler profiler;
	return profiler;
}



uint64_t Crayon::ProfileResult::getDurationMicroseconds()
{
	return m_endMicroSeconds - m_startMicroSeconds;
}

Crayon::ProfilerTimer::ProfilerTimer( const char* inName ):
	m_name( inName )
{
	m_startTime = std::chrono::steady_clock::now();
}


void Crayon::ProfilerTimer::stopAndOutputResult()
{
	m_isStopped = true;
	std::chrono::duration<double, Crayon::Microseconds> startTime = m_startTime.time_since_epoch();
	std::chrono::duration<double, Crayon::Microseconds> endTime = std::chrono::steady_clock::now().time_since_epoch();
	
	ProfileResult profileResult;
	profileResult.m_name = m_name;
	profileResult.m_startMicroSeconds = startTime.count();
	profileResult.m_endMicroSeconds = endTime.count();

	//Claude says: This is a common C++ idiom for creating and immediately using a function object, especially when you don't need to keep the function object around for later use.
	//The design of std::hash as a function object is largely due to historical reasons and consistency with other parts of the C++ standard library.
	profileResult.m_threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());

	Profiler::get().addToProfileResults( profileResult );
}


Crayon::ProfilerTimer::~ProfilerTimer()
{
	if (!m_isStopped)
	{
		stopAndOutputResult();
	}
}
