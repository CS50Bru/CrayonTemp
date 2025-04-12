#pragma once
#include<string>
namespace Crayon
{
	//ToDo: this is just a wrapper class and a relic from when you couldn't have custom display functions: now we can, so it's time to get rid of this.
	struct SoundAsset
	{
		std::string assetPath = "SoundFiles/laser_fired.wav";
	};
}