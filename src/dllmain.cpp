#include "stdc++.hpp"

#include "components/console.hpp"
#include "components/debugger.hpp"
#include "components/patch_ceg.hpp"

BOOL Init() {
    /* allocate external consol */
    if (AllocConsole()) {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
        freopen("CONIN$", "r", stdin);
    } else {
        return FALSE;
    }

    game::components::PatchCEG();

    game::components::EnableConsole();

    game::components::dbg::Initialize();

    game::components::AddConsoleCommands();

    return TRUE;
}

BOOL APIENTRY DllMain(HMODULE h_module, DWORD ul_reason_for_call, LPVOID lp_reserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        return Init();
    }
    if (ul_reason_for_call == DLL_PROCESS_DETACH) {
        return FreeConsole();
    }
    return TRUE;
}