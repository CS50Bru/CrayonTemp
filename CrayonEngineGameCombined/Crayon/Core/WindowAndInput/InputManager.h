#pragma once
#include<vector>
#include<bitset>
#include"Bitset.h"
#include"KeyCode.h"
#include"InputEvent.h"
#include"Core.h"
#include"WindowsInputMessage.h"
namespace Crayon
{

    //Crayon's Input Promises:
    // 
    //1: Every single kind of input event has an enum called the InputName. So, if you move the mouse, then that's MouseMove. If you click the middle mouse button, that's MouseMiddle. Hit the a key , and that's 'A'. The MAME of the input source and the INFORMATION ABOUT THE INPUT are SEPARATE.
   // With Windows,sometimes they're separate and sometimes they're the same: with a normal keypress the 'name' of the MSG (as in, the MSG itself) is just KEY_DOWN and then you get the actual keycode from the wparam, but then in the case of a leftmouseclick the name of the message is left mouse click and then the extra info is the cursor position etc. It makes sense in some ways but introduces a layer of inconsistency that becomes a pain to deal with further down the line.
  
    //2: In Crayon, every InputEvent gives you a start event when the user starts the input, and an end event when they stop : there are no input events that only give you one or the other.Windows, again, is inconsistent : press PrtSc and you only get an event when the key is released, and move the mouse and there's no 'stopped moving' message released.

    //3: In Crayon, you get 'Continuing' input events from the second frame that an event has been ongoing : there's no delay (in Windows, you don't get repeated KEYDOWN messages until after a second or so because they want there to be a pause before repeated input events are triggered).


    //How this works:
    //The Window class hands in keydown, keyup messages etc., and the InputManager homogenizes these into InputEvents that meet the InputPromises laid out above, as well as setting/unsetting the corresponding bits in our keyboard map.
    //These InputEvents are laid out in an array, with one element for each InputName.
    //When we need to generate a vector of InputEvents use our keyboard map bitset to iterate through the keys that are down in this "sparse" array and add them to the vecotor. Because we also save the state of the keyboard map from the last frame, we can also use bitwise magic + iterator tricks to quickly add in all of the InputEvents from the keys that have just been released (i.e. all the keyup events).

	class InputManager
	{

	private:
        using KeyboardState = Bitset<inputNameCount>;

        KeyboardState m_oldKeyboardState;
        KeyboardState m_currentKeyboardState;

        glm::vec2 m_cursorPos;
        std::vector<unicode_char> m_characters;


        std::array<InputEvent, inputNameCount> m_inputEventSparseArray;
        std::vector<InputEvent> m_inputEvents;

        static inline int getXPos( LPARAM lp ) 
        {
            return static_cast<int>(static_cast<short>(LOWORD( lp )));
        }

        static inline int getYPos( LPARAM lp )
        {
            return static_cast<int>(static_cast<short>(HIWORD( lp )));
        }

        KeyboardState getNewlySetBits() const
        {
            return (~m_oldKeyboardState) & m_currentKeyboardState;
        }

        KeyboardState getUnsetBits() const
        {
            return (~m_currentKeyboardState) & m_oldKeyboardState;
        }
		
        KeyboardState getCommonBits() const
        {
            return m_currentKeyboardState & m_oldKeyboardState;
        }


        void manuallyUnsetEvents()
        {
            m_currentKeyboardState.reset( static_cast<size_t>(InputName::MouseMove) );
            m_inputEventSparseArray[static_cast<size_t>(InputName::MouseMove)].m_inputStatus = InputStatus::Stop;
            m_currentKeyboardState.reset( static_cast<size_t>(InputName::MouseWheel) );
            m_inputEventSparseArray[static_cast<size_t>(InputName::MouseWheel)].m_inputStatus = InputStatus::Stop;

        }

    public:

        //ToDo: do we actually need to do this manually? Won't we get the same info when a mousemove message comes through from Window?
        void updateCursorPos()
        {
            POINT cursorPos;
            GetCursorPos( &cursorPos );
            m_cursorPos = glm::vec2( static_cast<float>(cursorPos.x), static_cast<float>(cursorPos.y) );
        }

		bool getKeyIsDown( InputName keyCode ) const
		{
			return m_currentKeyboardState.test(static_cast<size_t>(keyCode));
		}
		
		std::vector<InputEvent>& getInputEvents()
		{
			return m_inputEvents;
		}


		void switchAndClearCurrentKeyboardState()
		{
            m_oldKeyboardState = m_currentKeyboardState;
		}

        void resetForNewFrame()
        {
            switchAndClearCurrentKeyboardState();
            manuallyUnsetEvents();
            m_characters.clear();
            m_inputEvents.clear();
        
        }

        void organizeInputEventsIntoVector()
        {
            addEventsToVector( getNewlySetBits() );
            addEventsToVector( getCommonBits() );
            addEventsToVector( getUnsetBits() );
        }


        void addEventsToVector( KeyboardState keyboardState )
        {
            for ( auto it =  keyboardState.begin() ; it !=  keyboardState.end() ; it++ )
            {
                m_inputEvents.push_back( m_inputEventSparseArray[*it] );
            }
        }

        void processInputMessages( std::vector<WindowsInputMessage> inputMessages )
        {
            for ( auto& inputMessage : inputMessages )
            {
                processInputMessage( inputMessage.msg, inputMessage.wParam, inputMessage.lParam );
            }
        }

        void processInputMessage( UINT msg, WPARAM wParam, LPARAM lParam )
        {
            InputEvent inputEvent;
            
            switch ( msg )
            {
                //Now start dealing with actual Input-related messages
            case WM_KEYDOWN:
                m_currentKeyboardState.set( wParam );
                inputEvent = generateInputEventFromMessage( static_cast<InputName>(wParam), InputExtraInfoType::None, wParam, lParam );
                m_inputEventSparseArray[wParam] = inputEvent;
                break;

            case WM_KEYUP:
                m_currentKeyboardState.reset( wParam );
                //PrtSc- related input messags from Windows are bizarre: even manually checking whether the button's down each frame, this 'KEYUP' message can still end up coming through before the button registers as being pressed.
                if ( static_cast<InputName>(wParam) == InputName::PrintScreen )
                {
                    break;
                }
                inputEvent = generateInputEventFromMessage( static_cast<InputName>(wParam), InputExtraInfoType::None, wParam, lParam );
                m_inputEventSparseArray[wParam] = inputEvent;
                break;


            case WM_LBUTTONDOWN:
                m_currentKeyboardState.set( static_cast<size_t>( InputName::MouseLeft) );
                inputEvent = generateInputEventFromMessage( InputName::MouseLeft, InputExtraInfoType::Vec2Int, wParam, lParam );
                m_inputEventSparseArray[static_cast<size_t>(InputName::MouseLeft)] = inputEvent;
                break;

            case WM_LBUTTONUP:
                m_currentKeyboardState.reset( static_cast<size_t>(InputName::MouseLeft) );
                inputEvent=generateInputEventFromMessage( InputName::MouseLeft, InputExtraInfoType::Vec2Int, wParam, lParam );
                m_inputEventSparseArray[static_cast<size_t>(InputName::MouseLeft)] = inputEvent;
                break;

                //So, we do get MSGs for mousewheel moves and mousemoves...OH! But I bet you we DON'T get MSGs when they STOP, unlike the Keypresses and mousebutton stuff where you get 'down' and 'up' messages

            case WM_MOUSEWHEEL:
                m_currentKeyboardState.set( static_cast<size_t>(InputName::MouseWheel) );
                inputEvent = generateInputEventFromMessage( InputName::MouseWheel, InputExtraInfoType::Float,  wParam, lParam);
                m_inputEventSparseArray[static_cast<size_t>(InputName::MouseWheel)] = inputEvent;
                break;

            case WM_MOUSEMOVE:
                m_currentKeyboardState.set( static_cast<size_t>(InputName::MouseMove) );
                inputEvent = generateInputEventFromMessage( InputName::MouseMove, InputExtraInfoType::Vec2Int, wParam, lParam );
                m_cursorPos = glm::ivec2( getXPos( lParam ), getYPos( lParam ) );
                m_inputEventSparseArray[static_cast<size_t>(InputName::MouseMove)] = inputEvent;
                break;

            case WM_CHAR:
                m_characters.push_back( static_cast<unicode_char>(wParam)) ;
                break;
            }
        }


        //Some keypresses don't trigger KEYDOWN messages in Windows, so we have to manually check each frame.
        void processIrregularInput()
        {

            auto manuallyGenerateInputEvent = [this](InputName inputName) 
            {
                constexpr int mostSignificantBit = 0x8000;

                m_currentKeyboardState[static_cast<size_t>(inputName)] = GetAsyncKeyState( VK_SNAPSHOT ) & mostSignificantBit ? true : false;
                InputEvent inputEvent;
                inputEvent.m_keyCode = inputName;
                inputEvent.m_inputStatus = getInputStatus( inputName );
                m_inputEventSparseArray[static_cast<size_t>(inputName)] = inputEvent;
            };

            manuallyGenerateInputEvent( InputName::PrintScreen );
        }



		
        InputEvent generateInputEventFromMessage( InputName keyCode, InputExtraInfoType extraInfoType, WPARAM wParam, LPARAM lParam ) const
        {
            InputEvent inputEvent;
            inputEvent.m_eventType = EventType::Input;
            inputEvent.m_keyCode = keyCode;
            inputEvent.m_inputStatus = getInputStatus(keyCode);
            inputEvent.m_extraInfoType = extraInfoType;


            switch ( inputEvent.m_extraInfoType )
            {
            case InputExtraInfoType::Vec2Int:
                inputEvent.screenPosition = glm::ivec2( getXPos( lParam ), getYPos( lParam ) );
                break;
            case InputExtraInfoType::Float:
                inputEvent.scrollValue = (float)GET_WHEEL_DELTA_WPARAM( wParam ) / (float)WHEEL_DELTA;
                break;
            default:
                break;
            }
            return inputEvent;
        }

        InputStatus getInputStatus( InputName keyCode ) const
        {
            size_t keyCodeAsSize = static_cast<size_t>(keyCode);
            if ( m_oldKeyboardState.test( keyCodeAsSize ) )
            {
                if ( m_currentKeyboardState.test( keyCodeAsSize ) )
                {
                    return InputStatus::Continuing;
                }
                else 
                { 
                    return InputStatus::Stop; 
                }
            }
            return InputStatus::Begin;
        }

        std::vector<unicode_char>& getChars() 
        { 
            return m_characters; 
        }


        glm::ivec2 getMousePosIntegerVersion() const
        {
            return glm::ivec2( m_cursorPos );
        }


	};



}