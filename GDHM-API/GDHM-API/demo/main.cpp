#include <Windows.h>
#include <fstream>
#include <gdhm.h>
#include <json.hpp>
#include "../AutoUpdate.h"

using JSON = nlohmann::json;

struct aBot
{
	bool IsABot, IsSoftClick, IsHardClick;
	float Volume = 2.f;
	uint8_t SelectedClickPack;
	std::vector<std::string> ClickPackFolders = { "" };
	std::string ClickPackDirectory;
};
aBot data;


void UpdatePipe()
{
	JSON PipeData;
	PipeData["ABot"] = data.IsABot;
	PipeData["SoftClick"] = data.IsSoftClick;
	PipeData["HardClick"] = data.IsHardClick;
	PipeData["Volume"] = data.Volume;
	PipeData["Current ClickPack Directory"] = "Clicks\\" + data.ClickPackFolders.at(data.SelectedClickPack);

	std::fstream Pipe("\\\\.\\pipe\\ABot");
	Pipe << PipeData;
	Pipe.close();
}
std::vector<std::string> GetClickPacks(const std::string_view& path) {
	std::vector<std::string> ClickPacks;
	const auto dirIter = std::filesystem::recursive_directory_iterator(path);

	for (auto& file : dirIter)
	{
		if (file.is_directory()) {
			std::string StrPath = file.path().string();
			StrPath.erase(0, 7);
			if (StrPath.find("\\") == std::string::npos) { //Removes clicks, releases, etc
				std::replace(StrPath.begin(), StrPath.end(), '/', '\\');
				ClickPacks.emplace_back(StrPath);
			}
		}
	}
	if (ClickPacks.empty())
	{
		ClickPacks.emplace_back(" ");
	}

	return ClickPacks;
}

void _main_callback()
{
	data.ClickPackFolders = GetClickPacks("Clicks\\");
}

Update AutoUpdate;

void _header()
{
	gdhm::gui::checkbox(gdhm_new_id(), "ABot", &data.IsABot, nullptr, UpdatePipe);
	gdhm::gui::checkbox(gdhm_new_id(), "SoftClick", &data.IsSoftClick, nullptr, UpdatePipe);
	gdhm::gui::checkbox(gdhm_new_id(), "HardClick", &data.IsHardClick, nullptr, UpdatePipe);
	gdhm::gui::input_float(gdhm_new_id(), &data.Volume, "%.3f", 1, 0, 10.f, UpdatePipe);

	gdhm::gui::list_box(gdhm_new_id(), &data.SelectedClickPack, data.ClickPackFolders, [&]()
	{
		UpdatePipe();
		data.ClickPackFolders = GetClickPacks("Clicks\\");
	});
	if (AutoUpdate.GetUpdate())
	{
		gdhm::gui::label("Your ABot Version Is Outdated");
		gdhm::gui::label("Update Your ABot Version");
	}
}
DWORD WINAPI _dll_main(LPVOID lpParam)
{
	if (!std::filesystem::is_directory("Clicks") || !std::filesystem::exists("Clicks"))
	{
		std::filesystem::create_directory("Clicks");
	}
	AutoUpdate.LoadVersion();


	// Example of loader
	if (gdhm::is_loaded())
	{
		// Example of normal window
		gdhm::gui::window("ABot 1.8", "", nullptr, _main_callback, _header);
	}

	return TRUE;
}
