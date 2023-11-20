#include "hook.hpp"

namespace memory {

/* forces MH_Initialization */
/* don't uninitialize because it removes the hooks? */
class _ {
    _() {
        MH_Initialize();
    }
} __;

void Hook::Enable() {
    if (!enabled_) {
        MH_EnableHook(address_);
    }

    enabled_ = true;
}

void Hook::Disable() {
    if (enabled_) {
        MH_DisableHook(address_);
    }

    enabled_ = false;
}

void Hook::Create_(LPVOID fn_to_hook, LPVOID detour_fn, bool enable) {
    address_ = fn_to_hook;
    MH_CreateHook(fn_to_hook, detour_fn, reinterpret_cast<LPVOID*>(&original_));

    if (enable) {
        this->Enable();
    }
}

};  // namespace memory