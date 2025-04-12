#include"Crayon/GameInstance.h"

#include<windows.h>
#include<iostream>


//HINSTANCE: a unique id for a process. Really just a relic from a time when multiple processes might share code in memory and you needed to tell them apart using IDs.

//WINAPI is a calling convention macro - it tells the compiler how functions should pass parameters and manage the stack. In Windows programming, it's defined as __stdcall, which is the standard calling convention for the Windows API.
//You may also see CALLBACK, which also becomes __stdcall: it's not a big deal, but WINAPI is the more accepted convention, with CALLBACK normally being used for functions that you pass in as, well, callback functions to be used by Windows (like all the WndProc stuff).

//It specifies how parameters are pushed onto the stack (right to left), and specifies that the called function cleans up the stack


//_In_ etc.: SAL (Source Annotation Language) is a Microsoft-specific feature that helps with static code analysis. Let's dig deeper:_In_ Input parameter that can't be NULL
//_In_opt_   Input parameter that can be NULL
//_Out_      Output parameter (function will write to it)
//_Out_opt_  Optional output parameter
//_Inout_    Parameter that's both read and modified
//_Reserved_ Parameter that must be zero/NULL

//PWSTR: a pointer to a 'wide' (Unicode) string
//With a console app, we get int argc and char** argv. argc is the argument count, and argv is a pointer to a bunch of strings (a pointer to a bunc of char pointers).
//With wWinMain, we get all of the command line arguments fused together. If you want to break this up into individual arguments, then you have to go:

//int argc;
//LPWSTR* argv = CommandLineToArgvW( GetCommandLineW(), &argc );

#ifdef WINDOWS

int WINAPI wWinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE previousInstance, _In_ PWSTR pCmdLine, _In_ int cmdShow)
{

#ifdef DEBUG
	//create the console
	AllocConsole();

	//redirect standard output to the console: because we're not actually outputting to any file by default, we have to create a dummy file to 'redirect from'
	FILE* fDummy;
	freopen_s( &fDummy, "CONOUT$", "w", stdout );
	freopen_s( &fDummy, "CONIN$", "r", stdin );
	freopen_s( &fDummy, "CONOUT$", "w", stderr );
	std::cerr << "Errors printing to console" << std::endl;
#endif

	Crayon::GameInstance gameInstance{};

	gameInstance.init();
	
	gameInstance.loadDefaultScene();
	
	
	gameInstance.startGameLoop();

	std::cout << std::endl<< " Hit 'Enter' key to close console";
	std::cin.get();
	return 0;
}

#endif //WIN32_API