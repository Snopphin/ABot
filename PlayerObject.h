#pragma once

namespace ABot 
{
	namespace PlayerObject 
	{
		inline bool(__thiscall* PushButton)(void* self, bool PlayerButton);
		bool PushButton_hook(void* self, void*, bool PlayerButton);

		inline bool(__thiscall* ReleaseButton)(void* self, bool PlayerButton);
		bool ReleaseButton_hook(void* self, void*, bool PlayerButton);

		void MemoryInit();
	}

}