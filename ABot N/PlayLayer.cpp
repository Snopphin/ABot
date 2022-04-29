#include "pch.h"

namespace ABot
{
	namespace PlayLayer
	{
		void Update_hook(void* self, void*, float delta)
		{
			if (guiPipe.IsABot)
			{
				const float GDMusicVolume = Engine::GetMusicVolume(self);
				Engine::Dsp->setParameterFloat(FMOD_DSP_FADER::FMOD_DSP_FADER_GAIN, GDMusicVolume);
			}
			return PlayLayer::Update(self, delta);
		}

		void MemoryInit()
		{
			MH_CreateHook((void*)(gd::base + 0x2029C0), Update_hook, (void**)&Update);
		}
	}
}
