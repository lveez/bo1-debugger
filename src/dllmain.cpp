#include "stdc++.hpp"

BOOL Init() {
    /* allocate external consol */
    if (AllocConsole()) {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
        freopen("CONIN$", "r", stdin);
    } else {
        return FALSE;
    }

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