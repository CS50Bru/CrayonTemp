#pragma once
#include<string>
#include<fstream>
#include<chrono>
#include<mutex>
#include"Paths.h"
#include"Core.h"
namespace Crayon
{
//This is a Meyers' Singleton.

//Multithreading: we have a vector of ProfileResult structs. Profiler controls access to this, and when you want to add smth. a mutex is locked. When prompted to write out the results to a file, the vector will very briefly be locked while it is shallow-copied to another vector before the actual file write operation happends on another thread using that vector copy.

//What Profiler actually produces:
//we're going to write a .json file that the Tracer in Chrome can display visually as profiling data.
//You can get to the Chrome Tracer by entering in: "chrome://tracing". You display the information by dragging and dropping the .json file onto the open tracer page.
//To navigate around the page, use WASD to zoom in and out, move left and right etc.

//The .json file isn't difficult to put together. There's some boilerplate: a header and footer that need to go at the start and end of the file. Then, for the information itself, you have a bunch of profiling blocks (not the official name: just what I'm calling them). This gathers together the function name, the thread id, and how long the code took to run. So that's a block of standardised text that you just slot the correct values into.

//The way we handle profiling is: in DEBUG mode, you use macros to create and destroy timers around blocks of code that you want to profile: these are the ProfileTimers. They bundle their profiling information up in a ProfileResult struct and hand it to the Profiler.


//logic to strip out the PROFILE_SCOPE code in release builds

#ifdef DEBUG
#define PROFILING_ENABLED
#endif

#ifdef PROFILING_ENABLED
#define PROFILE_SCOPE(name) ProfilerTimer timer##__LINE__(#name);
#else
#define PROFILE_SCOPE(name)
#endif

#ifdef PROFILING_ENABLED
#define PROFILE_WRAP_START(name)  ProfilerTimer timer##name(#name); 
#define PROFILE_WRAP_END(name) timer##name.stopAndOutputResult();
#else
#define PROFILE_WRAP_START(name)
#define PROFILE_WRAP_END(name)

#endif

	//holds info about how long something took, plus what thread it was running on
	struct ProfileResult
	{

		std::string m_name;
		uint64_t m_startMicroSeconds=0;
		uint64_t m_endMicroSeconds=0;
		uint32_t m_threadID=0;

		uint64_t getDurationMicroseconds();

	};



	//writes a group of ProfileResults out to a JSON file.
	//beginProfileGroup opens the file, you then call writeProfile() to add results, and endProfileGroup() closes the file
	class Profiler
	{
		constexpr static const char* CHROME_VISUALIZER_HEADER = "{\"otherData\": {},\"traceEvents\":[";
		constexpr static const char* CHROME_VISUALIZER_FOOTER = "]}";

		
		Profiler()=default;
		~Profiler()=default;


		std::vector<ProfileResult> m_profileResults;

		static void addProfileResultToStream( const ProfileResult& profileResult, std::ostream& outStream);

		static void writeProfileResultsToFile( const std::string& filepath, std::vector<ProfileResult>&& profileResults, std::atomic<bool>& writeInProgress);
	public:
		std::mutex m_profileResultsMutex;
		std::atomic<bool> m_writingToFile = false;

		void reset();

		void addToProfileResults( const ProfileResult& profileResult );
		void startFileWriteThread(const std::string& filepath);


		static Profiler& get();
		void clearOutput();

	};

	class ProfilerTimer
	{

		bool m_isStopped = false;
		const char* m_name;
		std::chrono::time_point<std::chrono::steady_clock> m_startTime;

	public:
		ProfilerTimer( const char* inName );

		void stopAndOutputResult();


		~ProfilerTimer();
	};
}