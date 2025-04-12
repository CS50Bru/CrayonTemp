#pragma once

#include"ReflectionHelpers.h"

namespace Crayon
{

	class InputComponent
	{
	REGISTER_CLASS(InputComponent)
	public: 
		InputComponent() = default;

		bool m_inputActive = true;

	FINISH_REGISTRATION(InputComponent)
	};

}