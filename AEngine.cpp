#include "pch.h"

namespace ABot
{
	ClickType AEngine::CheckClickType()
	{
		CurrentTime = GetMS() - PreviousTime;

		if (CurrentTime < 1276667 && guiPipe.IsSoftClick)
		{
			return ClickType::SoftClick;
		}
		if (CurrentTime < 2400000 && guiPipe.IsHardClick)
		{
			return ClickType::HardClick;
		}

		return ClickType::NormalClick;
	}

	std::string AEngine::CreateClickPath(ClickType clickType, const Button button)
	{
		switch (clickType)
		{
		case ClickType::HardClick:
			if (button == Button::Hold && guiPipe.IsHardClick)
				return guiPipe.ClickPackDirectory + "\\hardClicks\\";

			else if (button == Button::Release && guiPipe.IsHardClick)
				return guiPipe.ClickPackDirectory + "\\hardReleases\\";
			break;

		case ClickType::NormalClick:
			if (button == Button::Hold)
				return guiPipe.ClickPackDirectory + "\\clicks\\";

			else if (button == Button::Release)
				return guiPipe.ClickPackDirectory + "\\releases\\";
			break;

		case ClickType::SoftClick:
			if (button == Button::Hold && guiPipe.IsSoftClick)
				return guiPipe.ClickPackDirectory + "\\softClicks\\";

			else if (button == Button::Release && guiPipe.IsSoftClick)
				return guiPipe.ClickPackDirectory + "\\softReleases\\";
			break;
		}
	}

	uint64_t AEngine::CreateClick(std::string ClickDirectory)
	{
		auto dirIter = std::filesystem::directory_iterator(ClickDirectory);

		const int fileCount = std::count_if(begin(dirIter), end(dirIter), [](auto& entry) 
		{ 
			return entry.is_regular_file();
		});

		std::uniform_int_distribution<int> CurrentClick(1, fileCount);
		std::random_device Seed;
		std::mt19937 RandomEngine(Seed());

		return CurrentClick(RandomEngine);
	}
}