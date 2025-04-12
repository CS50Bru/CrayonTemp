#pragma once
#include<chrono>

class String;

namespace Crayon
{
	using Seconds = std::ratio<1>;
	using Milliseconds = std::ratio<1, 1000>;
	using Microseconds = std::ratio<1, 1000000>;

	class Timer
	{
	private:
		//chrono seems to be all about stopping you from accidentally adding/subtracting/assigning things in ways that
		//don't make sense. It's particularly worried that you're going to mix up durations and points in time.

		//You get your time points from 2 different kinds of clock.
		//The steady clock is like a timer that starts when your application boots up. It's "steady" because, well,
		//you're not going to do anything weird with the timer, right? It's just going to keep ticking forwards.

		//The system clock, on the other hand, is like a wall clock: it's tied up with your timezone etc., and it can
		//therefore go backwards.

		//Use the steady clock for delta time etc., and use the system clock for logging (as in, you know how in each log entry
		//you output the time that it was logged? Yeah, use it for that).


		std::chrono::time_point<std::chrono::steady_clock> m_startTime;
		std::chrono::time_point<std::chrono::steady_clock> m_timeStopped;

		bool m_isStopped = false;

	public:
		Timer();

		template < typename Period>
		double getTimeStarted() const
		{
			const std::chrono::duration<double, Period> duration = m_startTime.time_since_epoch();
			return duration.count();
		}

		template< typename Period>
		double stopIfRunningAndGetTimeStopped()
		{
			stopIfRunning();
			std::chrono::duration<double, Period> duration = m_timeStopped.time_since_epoch();
			return duration.count();

		}

		template < typename Period>
		double getTimeSinceStart() const
		{
			const std::chrono::duration<double, Period> duration = std::chrono::steady_clock::now() - m_startTime;
			return duration.count();
		}

		template< typename Period>
		double getTime() const
		{
			if ( m_isStopped )
			{
				const std::chrono::duration<double, Period> duration = m_timeStopped.time_since_epoch();
				return duration.count();
			}
			const std::chrono::duration<double, Period> duration = std::chrono::steady_clock::now().time_since_epoch();
			return duration.count();
		}

		void stopIfRunning()
		{
			if ( !m_isStopped )
			{
				m_timeStopped = std::chrono::steady_clock::now();
				m_isStopped = true;
			}
		}


		void reset();

		static std::string getDateTimeStringString();
	};

}