#include "Window.h"
#include"Core.h"
#include"Logger.h"
#include"Libraries/glm/glm.hpp"


namespace Crayon
{

    Window::Window() :
        m_hWnd( NULL )
        , m_hInstance( NULL )
        , m_shouldClose( false )
        , m_resized( false )
        , m_width( 0 )
        , m_height( 0 )
    {
        CRAYON_ASSERT( !s_instanceExists );
        s_instanceExists = true;
        pWindow = this;
    }

    Window::~Window()
    {
        DestroyWindow( m_hWnd );
    }

    void Window::addInputMessage( UINT msg, WPARAM wParam, LPARAM lParam )
    {
        m_inputMessages.emplace_back( msg, wParam, lParam );
    }


    std::vector<WindowsInputMessage>& Window::getInputMessages()
    {
        return m_inputMessages;
    }

    void Window::clearInputMessages()
    {
        m_inputMessages.clear();
    }
   

    


    void Window::initWindowsWindow( bool fullScreen)
    {

        m_isFullscreen = fullScreen;

        m_hInstance = GetModuleHandle( NULL );



        ////////////////////////////////////////////////////////////////////////////
        //1) so, let's set up the class object

        //NB whcar_t is a built-in type that the Visual C++ compiler gives the language to deal
        //with 16-bit characters.
        const wchar_t CLASS_NAME[] = L"CrayonWindow";


        //create a window class
        //A window class essentially describes a set of attributes that will be common to all windows that are created with that class.
        //If you're wondering why it seems to disappear and not be used in the actual creation of the window, it's the NAME we pass in when registering the window class and creating the window that links the two.
        //It also has a field where you can add some properties like CS_OWNDC, which gives each window its own "device context". This was crucial for OpenGL but Vulkan talks 'directly' to the GPU, so it's not needed anymore: in Handmade Hero Casey wonders if it's worth setting, which I think in his case it absolutely was. AFAIK the WNDCLASS is really mostly just legacy settings at this point, and instead we'll set up the window settings manually after creating it using SetForegroundColor() etc.
        WNDCLASS wc = { };


        // this is the function that we're going to call on events for this window.
        //It'll take care of things like closing the window, but it won't actually close the program.
        //We are assigning a function pointer here.
        wc.lpfnWndProc = &WndProc;



        //hInstance is the handle to the application instance: i.e. THIS PROGRAM 
        //Get this value from the hInstance parameter of wWinMain.
        wc.hInstance = m_hInstance;
        wc.lpszClassName = CLASS_NAME;


        wc.hCursor = LoadCursor( NULL, IDC_ARROW );

        /////////////////////////////////////////////////////////////////////////////////////
        //2) Now let's register the class
        RegisterClass( &wc );

        ////////////////////////////////////////////////////////////////////////////////////
        //3) Now let's create an instance of it

        const long windowStyle = fullScreen ? WS_POPUP : WS_OVERLAPPEDWINDOW;
        m_isFullscreen = fullScreen;

        //when it comes to the size and position, on startup it's fine to just use the defaults here because ShowWindow with SW_MAXIMIZE will automatically have it fill the screen (getting the 'full screen size' etc. before the window has been created is a bit of a pain: you need to factor in the taskbar etc. so this way is a lot cleaner).

        m_hWnd = CreateWindowEx
        (
            0,                              // Optional window styles.
            CLASS_NAME,                     // Window class
            L"Crayon",                      // Window text
            windowStyle,                    // Window style: it's best to leave out WINDOW_VISIBLE or whatever the flag is here, because if you immediately make the window visible before you properly set its show mode etc. with ShowWindow you can get odd visual artefacts.

            // Size and position
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

            NULL,       // Parent window    
            NULL,       // Menu
            m_hInstance,  // Instance handle
            NULL        // Additional application data
        );

        CRAYON_ASSERT( m_hWnd != NULL );

        /// //////////////////////////////////////////////////////////////////////////////
        //Now we can do stuff with the window.



        ShowWindow( m_hWnd, SW_MAXIMIZE );
   

        SetForegroundWindow( m_hWnd );
        SetFocus( m_hWnd );


    }

    //wparam: "word param" (originally a 16-bit value)
    //lparam: "long param" (originally a 32-bit value)

    //Look at a MSG.
    //For "normal" KEKUP/ KEYDOWN messages, generate a new InputEvent and add it to the vector of raw input events. For KEYDOWN events, we don't do any further filtering at this point: the InputStatus in "Begin" and the InputManager can worry about it later.
    LRESULT Window::WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
    {
        switch ( msg )
        {

            //Handle any WINDOW-SPECIFIC messages: i.e. the Window has been closed or resized. Not really 'input'
        case WM_CLOSE:
            pWindow->setShouldClose( true );
            break;

        case WM_SIZE:
            pWindow->setResized( true );
            pWindow->setWidth( LOWORD( lParam ) );
            pWindow->setHeight( HIWORD( lParam ) );
            break;

        case WM_SETCURSOR:
            SetCursor( LoadCursor( NULL, IDC_ARROW ) );
            break;

        default:
            pWindow->addInputMessage( msg, wParam, lParam );
            break;
        }


        //NB you MUST HIT THIS LINE, if you want things like mousing over the edge of the window to set the pointer
        //to the appropriate "resizing double arrow" image etc.
        return DefWindowProc( hWnd, msg, wParam, lParam );
    }


    void Window::processMessages()
    {

        POINT cursorPos;
        GetCursorPos(&cursorPos);


        //MSG is a structure that contains info. about a message.
        //It has a .message member that contains the code that represents the message itself (i.e. what kind of message
        // it is), and a bunch
        //of other stuff like wParam which contains whatever extra info the message needs to pass over
        //MSG msg;

        MSG msg;



        //most Windows GUI apps are event-based, and you don't want them to do anything when there are no events firing off. So they'll use GetMessage, which hangs the program until it's got smth to return, at which point the program will start up again and it'll pop the message from the front of the message queue.
        //So, it's not that GetMessage will return 0 if there's no message: the program will ACTUALLY STOP RUNNING if there are no messages.
        //PeekMessage is much more normal: you can just look at the queue directly, and it returns 0 if there are nonmessages.
        //NB PeekMessage doesn't automatically remove that message from the queue, so you need to plug PM_REMOVE into it so that it actually does that.
        while ( PeekMessage( &msg, m_hWnd, 0, 0, PM_REMOVE ) )
        {

            //so, if the message was input/key related, TranslateMessage  will turn it into a specific keypress message and send it back to the message queue. This is done because sometimes people want to intercept keypress messages and treat them as smth. else... don't even worry about it
            TranslateMessage( &msg );


            //dispatch message passes the message along to the WinProc for the window (the message itself knows what window it applies to)
            DispatchMessage( &msg );

        }

    }


    uint32_t Window::getWidth() const
    {
        return m_width;
    }

    void Window::setWidth( uint32_t width )
    {
        m_width = width;
    }



    uint32_t Window::getHeight() const
    {
        return m_height;
    }

    glm::uvec2 Window::getScreenExtent() const
    {
        return glm::ivec2( m_width, m_height );
    }

    void Window::setHeight( uint32_t height )
    {
        m_height = height;
    }

    bool Window::getShouldClose() const
    {
        return m_shouldClose;
    }

    void Window::setShouldClose( bool shouldClose )
    {
        m_shouldClose = shouldClose;
    }

    bool Window::getResized() const
    {
        return m_resized;
    }

    void Window::setResized( bool resizedState )
    {
        m_resized = resizedState;
    }

    HWND Window::getHandle() const
    {
        return m_hWnd;
    }

    void Window::changeWindowFullscreenMode( bool wantFullscreen )
    {
        //if there's no actual change then return
        if ( m_isFullscreen == wantFullscreen )
        {
            return;
        }

        const int screenWidth = GetSystemMetrics( SM_CXSCREEN );
        const int screenHeight = GetSystemMetrics( SM_CXSCREEN );
        //if you're switching to windowed mode
        if ( m_isFullscreen && !wantFullscreen )
        {
            SetWindowLong( m_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW );
            //by default, have the new 'windowed window' be half the width and height of the screen
            const int windowWidth = screenWidth / 2;
            const int windowHeight = screenHeight / 2;

            //have the x pos of the top-left of the window be half the difference between the screen width and the window width; this will give you that:
            //---++++++++---
            //..and then just do the same for the height.
            SetWindowPos( m_hWnd, NULL, (screenWidth - windowWidth) / 2, (screenHeight - windowHeight) / 2, windowWidth, windowHeight, SWP_FRAMECHANGED | SWP_NOZORDER | SWP_SHOWWINDOW );
        }

        else if (!m_isFullscreen && wantFullscreen )
        {
            SetWindowLong( m_hWnd, GWL_STYLE, WS_POPUPWINDOW );

            SetWindowPos( m_hWnd, NULL, 0, 0, screenWidth, screenHeight, SWP_FRAMECHANGED | SWP_NOZORDER | SWP_SHOWWINDOW );
        }
        m_isFullscreen = wantFullscreen;
    }

}