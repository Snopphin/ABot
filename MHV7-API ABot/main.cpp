#include <Windows.h>
#include <extensions2.h>
#include <json.hpp>
#include <fstream>
#include <future>
#include <AutoUpdate.h>

using JSON = nlohmann::json;

struct aBot
{
	bool IsABot = false, IsSoftClick = false, IsHardClick = false;
	float Volume = 2.f;
	std::string ClickPackDirectory;
};
aBot data;


void UpdatePipe()
{
	static std::mutex mutex;
	std::unique_lock lock(mutex);
	JSON PipeData;

	PipeData["ABot"] = data.IsABot;
	PipeData["SoftClick"] = data.IsSoftClick;
	PipeData["HardClick"] = data.IsHardClick;
	PipeData["Volume"] = data.Volume;
	PipeData["Current ClickPack Directory"] = "Clicks\\" + data.ClickPackDirectory;

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
				ClickPacks.emplace_back(StrPath.c_str());
			}
		}
	}
	if (ClickPacks.empty())
	{
		ClickPacks.emplace_back(std::string());
	}

	return ClickPacks;
}
Update AutoUpdate;

DWORD WINAPI _dll_main(LPVOID lpParam)
{
	if (!std::filesystem::is_directory("Clicks") || !std::filesystem::exists("Clicks"))
	{
		std::filesystem::create_directory("Clicks");
	}

	AutoUpdate.LoadVersion();

	using namespace MegaHackExt;

	Window* window = Window::Create("ABot 1.7");

	CheckBox* ABot = CheckBox::Create("ABot");
	ABot->setCallback([](CheckBox* a, bool b) 
	{ 
		data.IsABot = b; 
		UpdatePipe();
	});

	CheckBox* SoftClick = CheckBox::Create("SoftClick");
	SoftClick->setCallback([](CheckBox* a, bool b) 
	{
		data.IsSoftClick = b; 
		UpdatePipe(); 
	});

	CheckBox* HardClick = CheckBox::Create("HardClick");
	HardClick->setCallback([](CheckBox* a, bool b)
	{ 
		data.IsHardClick = b;
		UpdatePipe(); 
	});

	TextBox* Volume = TextBox::Create("Volume");
	Volume->set("2.0");
	Volume->setCallback([](TextBox* a, const char* Slider) 
	{ 
		data.Volume = std::stof(Slider); 
		UpdatePipe();
	});

	const char* ClickPack[1024] = { "", nullptr };

	auto GeneralClickPack = GetClickPacks("Clicks\\");

	for (size_t size = 0; size != GeneralClickPack.size() - 1; size++)
	{
		ClickPack[size] = GeneralClickPack[size].c_str();
	}

	ComboBox* ClickPacks = ComboBox::Create("", nullptr);
	ClickPacks->setCallback([](ComboBox* obj, int index, const char* str) 
	{
		data.ClickPackDirectory = str; 
		UpdatePipe();
	});
	ClickPacks->setValues(ClickPack);

	std::string_view AutoUpdateText[2] = { "", "" };
	if (AutoUpdate.GetUpdate())
	{
		AutoUpdateText[0] = "ABot Version Is Outdated";
		AutoUpdateText[1] = "Update Your ABot Version";
	}

	Label* AutoUpdate = Label::Create(AutoUpdateText[0].data());
	Label* AutoUpdate2 = Label::Create(AutoUpdateText[1].data());

	window->add(AutoUpdate);
	window->add(AutoUpdate2);
	window->add(ClickPacks);
	window->add(Volume);
	window->add(HardClick);
	window->add(SoftClick);
	window->add(ABot);


	Client::commit(window);

	return TRUE;
}