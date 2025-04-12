//The basic idea:
//This thing creates a Windows window and keeps a handle to it (an HWND).
//That Windows window needs a WndProc() function that tells it how to deal with window events like the red x button
//being pressed. So we define that function in this class and then plug it into the actual Windows window through the 
//WNDCLASS that we use to create it (which is basically a bunch of info laying out how to build a Windows window).
//Our WndProc() function currently just passes everything on to the default WndProc function, which takes care of closing
//the window if it receives a 'close the window' event etc.

//The Windows window doesn't do anything with its own message queue automatically: instead we get to go through the window's message
//queue ourselves, and then hand those messages over to the actual Windows window using DispatchMessage().

//This is quite a nice setup: basically it's a wrapper around an actual Windows window where we look at that Windows window's
//events at the start of each frame and handle them all in one go, which means things won't just happen willy-nilly as
//events fire off from the window.



#pragma once
//from MSDN: "In Win32, UNICODE is supported by #define-ing the UNICODE and _UNICODE macros. 
//This, in turn, causes your program to use the Unicode variants of the Win32 functions."
#ifndef UNICODE
#define UNICODE
#endif 

#include<iostream>
#include<stdint.h>
#include<Libraries/glm/glm.hpp>
#include<vector>
#include<Windows.h>

#include"Core.h"
#include"WindowsInputMessage.h"

namespace Crayon
{

	class Window
	{
	private:

		//this static Window* is here because the WndProc needs to call methods on the current window, and you don't seem to be able
		//to change a WndProc's function signature to include a reference to a window, so this was the only way
		//I could think of to allow the WndProc to call pWindow()-> setShouldClose etc.
		//There must be a way to pass more information in to a WndProc but I've run out of time!
		inline static Window* pWindow = nullptr;


		HWND m_hWnd;
		HINSTANCE m_hInstance;

		bool m_shouldClose;
		bool m_resized;

		uint32_t m_width;
		uint32_t m_height;

		inline static bool s_instanceExists = false;

		std::vector<WindowsInputMessage> m_inputMessages;

		bool m_isFullscreen = false;

	public:
		Window();
		Window& operator=( const Window& ) = delete;
		~Window();

		std::vector<WindowsInputMessage>& getInputMessages();
		void clearInputMessages();

		void addInputMessage( UINT msg, WPARAM wParam, LPARAM lParam );

		//some notes on CALLBACK, which expands to __stdcall: (so, to be clear, LRESULT is the return type and //CALLBACK is a macro that expands to the __stdcall keyword)

		//Basically, the big thing about __stdcall is that it specifies that the callee, not the caller, is in charge of cleaning up the stack frame, which can be more efficient, and it's a standard that makes it easier to put together .dlls because it inserts some extra (useful) info into the function name.
		//It's just a windows thing though, which is partly why they're using a macro here: what you normally do with __stdcall is to go: 

		//#ifdef _WIN32
		//#define MYCALLCONV __stdcall
		//#else
		//#define MYCALLCONV
		//#endif

		//or whatever so that it gets stripped out of non-Windows builds.


		//In the Windows API, every window created must have a window procedure — a function that receives and processes all messages sent to the window
		static LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );


		void initWindowsWindow( bool fullScreen );

		void processMessages();


		uint32_t getWidth() const;
		void setWidth( uint32_t width );
		uint32_t getHeight() const;

		glm::uvec2 getScreenExtent() const;
		void setHeight( uint32_t height );

		bool getShouldClose() const;
		void setShouldClose( bool shouldClose );

		bool getResized() const;
		void setResized( bool resizedState );

		HWND getHandle() const;

		void changeWindowFullscreenMode( bool wantFullscreen );


	};

}

