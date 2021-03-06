#include "pch.h"

namespace ABot
{
	void Engine::playSound(std::string path)
	{
		System->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &Sound);
		System->playSound(Sound, nullptr, true, &Channel);
		System->update();
	}
	float Engine::GetAudioSpeed()
	{
		static auto GDEngine = gd::FMODAudioEngine::sharedEngine();
		float GDAudioSpeed = 1;
		GDEngine->m_pCurrentSoundChannel->getPitch(&GDAudioSpeed);
		return GDAudioSpeed;
	}
	float Engine::GetMusicVolume(void* self)
	{
		void* Player = *(void**)((char*)self + 0x224);
		void* PlayerWave = *(void**)((char*)Player + 0x514);
		float WavePulse = *(float*)((uint32_t)PlayerWave + 0x012C); 
		static auto GDEngine = gd::FMODAudioEngine::sharedEngine();
		float GDMusicVolume = WavePulse + GDEngine->m_fPulse1 + GDEngine->m_fPulse2 + GDEngine->m_fPulse3;
		return GDMusicVolume;
	}
	void Engine::Update()
	{
		const float TargetPitch = pow(2, 0.01147f);

		std::uniform_real_distribution<float> Pitch(TargetPitch * 1.0004f, TargetPitch);
		std::random_device Seed;
		std::mt19937 RandomEngine(Seed());

		Channel->addDSP(0, Dsp);

		const float CurrentPitch = Pitch(RandomEngine);
		const float GDAudioSpeed = GetAudioSpeed();
		Channel->setPitch(TargetPitch / GDAudioSpeed);
		Channel->setVolume(guiPipe.Volume);

		Channel->setPaused(false);
	}
}
