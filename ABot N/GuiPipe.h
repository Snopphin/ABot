#pragma once
namespace ABot
{
	class GuiPipe : public Pipe, public aBot
	{
		using JSON = nlohmann::json;
	private:
		JSON m_PipeData;
	private:
		void OnReadPipe() override;
	};

	inline GuiPipe guiPipe;
}