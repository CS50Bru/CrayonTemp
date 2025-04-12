#pragma once

#include<xaudio2.h>

namespace Crayon
{
	struct AudioHandle
	{
		XAUDIO2_BUFFER buffer;
		WAVEFORMATEX waveFormat;
	};
}