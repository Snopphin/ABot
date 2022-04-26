#include "AutoUpdate.h"
#include <Windows.h>
#include <wininet.h>

void Update::LoadVersion()
{
	std::string WebSite = DownloadString("https://leginsoffi.gitbook.io/abot/");
	std::string DataVersion = "/abot/updates/" + m_Version;

	if (WebSite.find(DataVersion) != std::string::npos ? m_IsFoundUpdate = false : m_IsFoundUpdate = true);
}

std::string Update::replaceAll(std::string subject, const std::string_view& search, const std::string_view& replace)
{
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

std::string Update::DownloadString(std::string_view URL)
{
	HINTERNET interwebs = InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
	HINTERNET urlFile = nullptr;
	std::string rtn;
	if (interwebs) {
		urlFile = InternetOpenUrlA(interwebs, URL.data(), NULL, NULL, NULL, NULL);
		if (urlFile) {
			char buffer[300];
			DWORD bytesRead;
			do {
				InternetReadFile(urlFile, buffer, 300, &bytesRead);
				rtn.append(buffer, bytesRead);
				memset(buffer, 0, 300);
			} while (bytesRead);
			InternetCloseHandle(interwebs);
			InternetCloseHandle(urlFile);

			return replaceAll(rtn, "|n", "\r\n");
		}
	}
	InternetCloseHandle(interwebs);
	InternetCloseHandle(urlFile);

	return replaceAll(rtn, "|n", "\r\n");
}