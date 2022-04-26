#pragma once
#define LogValue(Value) MessageBox(0, std::to_string(Value).c_str(), "", MB_OK) //For Debugging
namespace ABot
{
	enum class ClickType
	{
		HardClick, NormalClick, SoftClick
	};

	enum class Button
	{
		Hold, Release
	};

	class AEngine
	{
	public:
		uint32_t CurrentTime = 0;
		uint32_t PreviousTime = 0;
		Engine FMODEngine;
	public:
		static uint32_t GetMS() { return std::chrono::system_clock::now().time_since_epoch().count(); }
		ClickType CheckClickType();
		std::string CreateClickPath(ClickType clickType, const Button button);
		uint64_t CreateClick(std::string ClickDirectory);
	};
}