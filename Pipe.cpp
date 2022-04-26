#include "pch.h"

namespace ABot {

    void Pipe::WritePipe(std::string_view Data)
    {
        DWORD Bytes;
        WriteFile(m_Pipe, Data.data(), Data.length(), &Bytes, nullptr);
        OnWritePipe();
    }

    void Pipe::ReadPipe()
    {
        DWORD Bytes;

        if (ConnectNamedPipe(m_Pipe, nullptr) != false)   // wait for someone to connect to the pipe
        {
            while (ReadFile(m_Pipe, PipeBuffer, sizeof(PipeBuffer) - 1, &Bytes, nullptr) != false)
            {
                PipeBuffer[Bytes] = '\0';
                OnReadPipe();
                DisconnectNamedPipe(m_Pipe);
            }
        }
    }
    void Pipe::OnReadPipe()
    {

    }

    void Pipe::OnWritePipe()
    {

    }

    void Pipe::CreatePipe(std::string_view PipeName)
    {
        auto& CurrentPipe = GetPipe();
        CurrentPipe = 
            CreateNamedPipe(PipeName.data(), PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
            1,
            1024 * 16,
            1024 * 16,
            NMPWAIT_USE_DEFAULT_WAIT,
            NULL);

    }

    void Pipe::LoadPipe(std::string_view PipeName)
    {
        auto& CurrentPipe = GetPipe();
        CurrentPipe = 
            CreateFile(PipeName.data(),
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            0,
            NULL);

    }
    /*
    namespace Pipe
    {
        void Update(const JSON Data)
        {
            data.IsABot = Data.at("ABot");
            data.IsSoftClick = Data.at("SoftClick");
            data.IsHardClick = Data.at("HardClick");
            data.Volume = Data.at("Volume");
            data.ClickPackDirectory = Data.at("Current ClickPack Directory");
        }
        void RunPipe()
        {
            static std::mutex mutex;
            std::unique_lock lock(mutex);
            HANDLE hPipe;
            DWORD dwRead;
            char Pipebuffer[1024];

            hPipe = CreateNamedPipeA
            (
                "\\\\.\\pipe\\ABot",
                PIPE_ACCESS_DUPLEX,
                PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
                1,
                1024 * 16,
                1024 * 16,
                NMPWAIT_USE_DEFAULT_WAIT,
                nullptr
            );

            while (hPipe != INVALID_HANDLE_VALUE)
            {

                if (ConnectNamedPipe(hPipe, nullptr) != false)
                {
                    while (ReadFile(hPipe, Pipebuffer, sizeof(Pipebuffer) - 1, &dwRead, nullptr) != false)
                    {
                        Pipebuffer[dwRead] = '\0';
                        const JSON Data = JSON::parse(Pipebuffer);
                        Update(Data);
                    }
                    DisconnectNamedPipe(hPipe);
                }
            }
        }
    }
    */
}