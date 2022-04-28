#include "pch.h"

namespace ABot
{
	namespace PlayLayer
	{
		void Update_hook(void* self, void*, float delta)
		{
			if (guiPipe.IsABot)
			{
				static auto GDEngine = gd::FMODAudioEngine::sharedEngine();
				GDEngine->m_bMetering = true;

				const float GDMusicVolume = Engine::GetMusicVolume(self);
				Engine::Channel->setVolume(GDMusicVolume + GDEngine->m_fBackgroundMusicVolume + guiPipe.Volume);
				Engine::Dsp->setParameterFloat(FMOD_DSP_FADER::FMOD_DSP_FADER_GAIN, GDMusicVolume + GDEngine->m_fBackgroundMusicVolume);
			}
			return PlayLayer::Update(self, delta);
		}

		void MemoryInit()
		{
			MH_CreateHook((void*)(gd::base + 0x2029C0), Update_hook, (void**)&Update);
		}
	}
}
