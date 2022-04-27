#include "pch.h"

DWORD WINAPI RunBot(void* hMod)
{
    using FMODEngine = ABot::Engine;
    using namespace ABot;

    gd::init();

    auto GDEngine = gd::FMODAudioEngine::sharedEngine();

    FMOD::System_Create(&FMODEngine::System);
    FMODEngine::System->init(1024 * 2, FMOD_INIT_NORMAL, GDEngine->m_pExtraDriverData);
    FMODEngine::System->setSoftwareFormat(48 * 1000, FMOD_SPEAKERMODE_STEREO, 0);
    FMODEngine::System->createDSPByType(FMOD_DSP_TYPE_FADER, &FMODEngine::Dsp);

    guiPipe.CreatePipe("\\\\.\\pipe\\ABot");

    MH_Initialize();

    PlayerObject::MemoryInit();
    PlayLayer::MemoryInit();

    MH_EnableHook(MH_ALL_HOOKS);

    static std::vector<std::future<void>> Future;

    Future.emplace_back(std::async(std::launch::async, []
    {
            while (guiPipe.GetPipe() != INVALID_HANDLE_VALUE)
            guiPipe.ReadPipe();
    }));

    return TRUE;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(0, 0x1000, RunBot, hModule, 0, 0);
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


