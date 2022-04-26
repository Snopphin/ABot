#pragma once
#include <string_view>

class Update
{
private:
	const std::string m_Version = "1.6";
	bool m_IsFoundUpdate = false;
public:
	void LoadVersion();
	bool GetUpdate() const { return m_IsFoundUpdate; }
	std::string replaceAll(std::string subject, const std::string_view& search, const std::string_view& replace);
	std::string DownloadString(std::string_view URL);
};