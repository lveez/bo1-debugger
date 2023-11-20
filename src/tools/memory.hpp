/*  basic wrappers for reading and writing to memory pages
    with restrictions. */

#pragma once

#include "../stdc++.hpp"

namespace memory {

/* Patches num_bytes with NOP starting at address */
bool PatchNOP(DWORD address, size_t num_bytes);

/* Patchs a call (0xe8) at address to call fn_to_call instead */
bool PatchCall(DWORD address, DWORD fn_to_call);

/* Patches a jump (0xe9) to jump to destination instead */
bool PatchJump(DWORD address, DWORD destination);

/* Patches bytes at address with string of bytes */
bool PatchBytes(DWORD address, const char* const bytes, size_t bytes_len);

};  // namespace memory