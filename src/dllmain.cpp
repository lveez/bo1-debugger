#include "stdc++.hpp"

#include "components/console.hpp"
#include "components/patch_ceg.hpp"
#include "components/threads.hpp"

BOOL OnAttach() {
    /* allocate external consol */
    if (AllocConsole()) {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
        freopen("CONIN$", "r", stdin);
    } else {
        return FALSE;
    }

    components::PatchCEG();

    components::console::OnAttach();

    components::threads::OnAttach();

    return TRUE;
}

BOOL APIENTRY DllMain(HMODULE h_module, DWORD ul_reason_for_call, LPVOID lp_reserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        return OnAttach();
    }
    if (ul_reason_for_call == DLL_PROCESS_DETACH) {
        return FreeConsole();
    }
    return TRUE;
}