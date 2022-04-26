#pragma once
namespace ABot
{
	class Pipe
	{
	private:
		HANDLE m_Pipe;
	private:
		virtual void OnReadPipe();
		virtual void OnWritePipe();
	public:
		char PipeBuffer[512];
	public:
		auto& GetPipe() { return m_Pipe; }
		void WritePipe(std::string_view Data);
		void ReadPipe();

		void CreatePipe(std::string_view PipeName);
		void LoadPipe(std::string_view PipeName);
	};
	/*
	namespace Pipe
	{
		using JSON = nlohmann::json;

		void Update(const JSON Data);
		void RunPipe();

	}
	*/
}