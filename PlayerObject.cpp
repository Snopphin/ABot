#include "pch.h"

namespace ABot
{
	namespace PlayerObject
	{
		AEngine Engine;

		bool PushButton_hook(void* self, void*, bool PlayerButton)
		{
			if (guiPipe.IsABot && !PlayerButton)
			{
				ClickType CurrentClickType = Engine.CheckClickType();
				std::string ClickPath = Engine.CreateClickPath(CurrentClickType, Button::Hold);
				std::string CurrentClick = std::to_string(Engine.CreateClick(ClickPath)) + ".wav";

				Engine.FMODEngine.playSound(ClickPath + CurrentClick);
				Engine.FMODEngine.Update();
			}

			return PlayerObject::PushButton(self, PlayerButton);
		}

		bool ReleaseButton_hook(void* self, void*, bool PlayerButton)
		{
			if (guiPipe.IsABot && !PlayerButton)
			{
				ClickType CurrentClickType = Engine.CheckClickType();
				std::string ClickPath = Engine.CreateClickPath(CurrentClickType, Button::Release);
				std::string CurrentClick = std::to_string(Engine.CreateClick(ClickPath)) + ".wav";

				Engine.FMODEngine.playSound(ClickPath + CurrentClick);
				Engine.FMODEngine.Update();
			}

			Engine.PreviousTime = AEngine::GetMS();

			return PlayerObject::ReleaseButton(self, PlayerButton);
		}

		void MemoryInit()
		{
			MH_CreateHook((void*)(gd::base + 0x1F4E40), PushButton_hook, (void**)&PushButton);
			MH_CreateHook((void*)(gd::base + 0x1F4F70), ReleaseButton_hook, (void**)&ReleaseButton);
		}
	}
}