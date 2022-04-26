#pragma once

namespace ABot
{
	class Engine
	{
	private:
		FMOD::Sound* Sound;
	public:
		static inline FMOD::System* System;
		static inline FMOD::ChannelGroup* Group;
		static inline FMOD::Channel* Channel;
		static inline FMOD::DSP* Dsp;
	private:
		float GetAudioSpeed();
	public:
		static float GetMusicVolume(void* self);
		void playSound(std::string path);
		void Update();
	};
}