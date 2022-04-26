#pragma once

namespace ABot
{
	namespace PlayLayer
	{
		inline void(__thiscall* Update)(void* self, float delta);
		void Update_hook(void* self, void*, float delta);

		void MemoryInit();
	}
}