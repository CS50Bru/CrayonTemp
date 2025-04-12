#pragma once
#include"Core.h"
#include"Libraries/glm/glm.hpp"
#include"Event.h"
#include"KeyCode.h"
namespace Crayon
{
	enum class InputStatus{Begin, Stop, Continuing, NoInformation};
	enum class InputExtraInfoType{ Vec2Int, Vec2Float, Float, None };

	//From the Event class, it gets an 'isHandled' bool and an 'EventType' enum.
	//It contains 2 important pieces of info:
	//a 'keycode' that should really be renamed to 'InputSource' and a union that you can put extra info in (along with anothe enum that tells you how you should read the union... and which could maybe be done away with using the new C++ 20 version of a union which I'm pretty sure contains that info within itself and throws an error if you try to read it the wrong way)



	class InputEvent : public Event
	{
	public:
		InputEvent() = default;

		InputEvent( InputStatus inputStatus, InputName keyCode, InputExtraInfoType extraInfoType ) :
			m_inputStatus( inputStatus ), m_keyCode( keyCode ), m_extraInfoType( extraInfoType )
		{
			m_eventType = EventType::Input;
		}

		InputStatus m_inputStatus = InputStatus::NoInformation;
		InputName m_keyCode = InputName::InvalidValue;
		InputExtraInfoType m_extraInfoType = InputExtraInfoType::None;
		
		union
		{
			glm::ivec2 screenPosition;
			float scrollValue;
			char character;
		};

		static bool getActive( InputStatus inputSatus )
		{
			return (inputSatus == InputStatus::Begin || inputSatus == InputStatus::Continuing);
		}


		bool getActive() const
		{
			return m_inputStatus == InputStatus::Begin || m_inputStatus == InputStatus::Continuing;
		}
	};
}