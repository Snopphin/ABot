#include "pch.h"

namespace ABot
{
	void GuiPipe::OnReadPipe()
	{
		m_PipeData = JSON::parse(PipeBuffer);
		IsABot = m_PipeData.at("ABot");
		IsSoftClick = m_PipeData.at("SoftClick");
		IsHardClick = m_PipeData.at("HardClick");
		Volume = m_PipeData.at("Volume");
		ClickPackDirectory = m_PipeData.at("Current ClickPack Directory");
	}

}
