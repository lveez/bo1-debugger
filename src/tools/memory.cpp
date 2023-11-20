#include "memory.hpp"

namespace memory {

bool PatchNOP(DWORD address, size_t num_bytes) {
    DWORD old_protect = 0;

    if (VirtualProtect(reinterpret_cast<void*>(address), num_bytes, PAGE_EXECUTE_READWRITE, &old_protect) == FALSE) {
        return false;
    }

    for (size_t i = 0; i < num_bytes; i++) {
        *reinterpret_cast<BYTE*>(address + i) = '\x90';
    }

    return VirtualProtect(reinterpret_cast<void*>(address), num_bytes, old_protect, nullptr);
}

bool PatchNOP(DWORD address, DWORD fn_to_call) {
    DWORD old_protect = 0;
    DWORD data = fn_to_call - address - 5;

    if (VirtualProtect(reinterpret_cast<void*>(address), 5, PAGE_EXECUTE_READWRITE, &old_protect) == FALSE) {
        return false;
    }

    *reinterpret_cast<BYTE*>(address) = '\xe8';

    *reinterpret_cast<DWORD*>(address + 1) = data;

    return VirtualProtect(reinterpret_cast<void*>(address), 5, old_protect, nullptr);
}

bool PatchJump(DWORD address, DWORD destination) {
    DWORD old_protect = 0;
    DWORD jump = destination - address - 5;

    if (VirtualProtect(reinterpret_cast<void*>(address), 5, PAGE_EXECUTE_READWRITE, &old_protect) == FALSE) {
        return false;
    }

    *reinterpret_cast<BYTE*>(address) = '\xe9';

    *reinterpret_cast<DWORD*>(address + 1) = jump;

    return VirtualProtect(reinterpret_cast<void*>(address), 5, old_protect, nullptr);
}

bool PatchNOP(DWORD address, const char* const bytes, size_t bytes_len) {
    DWORD old_protect = 0;

    if (VirtualProtect(reinterpret_cast<void*>(address), bytes_len, PAGE_EXECUTE_READWRITE, &old_protect) == FALSE) {
        return false;
    }

    for (size_t i = 0; i < bytes_len; i++) {
        *reinterpret_cast<BYTE*>(address + i) = *(bytes + i);
    }

    return VirtualProtect(reinterpret_cast<void*>(address), bytes_len, old_protect, nullptr);
}

};  // namespace memory