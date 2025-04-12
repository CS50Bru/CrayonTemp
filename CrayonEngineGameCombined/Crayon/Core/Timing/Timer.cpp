#include"Timer.h"

#include<string>



namespace Crayon
{
	Timer::Timer()
		:
		m_startTime( std::chrono::steady_clock::now() )
	{
	}


		//steady_clock::now() and m_startTime are both time points. They have a clock, and a duration. We'll just worry about the duration for now.

		//now() and m_startTime are both time points.When you subtract one from another, you get a duration.The duration will use the period employed by the 
		// clock part of the time point : so, let's say microseconds or whatever. time elapsed doesn't specify a period, though for clairty's sake I'd like to), 
		//so we're doing an implicit cast from std::chrono::duration<int64, std::ratio<1, 1000000> to std::chrono::duration<double, std::ratio<1>. 


	void Timer::reset()
	{
		m_startTime = std::chrono::steady_clock::now();
		m_isStopped = false;
	}


	std::string Timer::getDateTimeStringString()
	{
		//std::time is basically an int-ish thing that stores time in SECONDS. So you couldn't use it for performance profiling or anything like that


		//get the current time from the steady clock as a timepoint and immediately convert it into an old-school
		//time_t structure (because that's what the rest of our code wants to work with)
		std::time_t now = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );

		//a tm structure represents time broken down into day, month, year etc.
		tm readableTime=  *(std::localtime( &now ));

		//I don't understand these 2 lines: to be honest, I'm kind of stunned that there isn't a simpler way of breaking
		//an std::time_t (or indeed an std::chrono::time_point) down into date, month and year to begin with...very
		//annoying!
		std::stringstream stringStream;
		stringStream<<std::put_time( &readableTime, "%Y-%m-%d %H:%M:%S" );

	//	std::string debugString = stringStream.str();
		return stringStream.str();
	}
}
