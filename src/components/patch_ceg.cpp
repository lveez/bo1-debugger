#include "patch_ceg.hpp"

#include "../tools/memory.hpp"

namespace game {
namespace components {

/* from linkermod */
void PatchCEG() {
    memory::PatchBytes(0x662F20, "\xB8\x01\x00\x00\x00\xC3", 6);  // Kill Steam DRM IPC creation
    memory::PatchBytes(0x46C9A0, "\xCC", 1);
    memory::PatchBytes(0x5F3290, "\xCC", 1);

    memory::PatchBytes(0x4DFD60, "\xB8\x01\x00\x00\x00\xC3", 6);  // Registry key checks
    memory::PatchBytes(0x53F880, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x5A5360, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x4DFD60, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x5A5360, "\xB8\x01\x00\x00\x00\xC3", 6);

    memory::PatchBytes(0x64F6A0, "\xB8\x01\x00\x00\x00\xC3", 6);  // Single function, 32bit hash check
    memory::PatchBytes(0x5614A0, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x417360, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x56AB40, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x59BEB0, "\xB8\x01\x00\x00\x00\xC3", 6);

    memory::PatchBytes(0x676740, "\xB8\x01\x00\x00\x00\xC3", 6);  // Direct ExitProcess() check
    memory::PatchBytes(0x5DB020, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x4F02C0, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x572DF0, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x679B40, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x4BFB50, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x4D4B80, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x501080, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x5CAB50, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x4C0DE0, "\xB8\x01\x00\x00\x00\xC3", 6);

    memory::PatchBytes(0x41CEB0, "\xB8\x01\x00\x00\x00\xC3", 6);  // Wrapper ExitProcess() check, executes
    memory::PatchBytes(0x41CF50, "\xB8\x01\x00\x00\x00\xC3", 6);  // on certain days of the week
    memory::PatchBytes(0x427E00, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x437350, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x444E80, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x449C30, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x4545A0, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x45C550, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x462B60, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x4682B0, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x487D80, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x48C7B0, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x4A9970, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x4C3360, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x4D9650, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x4E3860, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x515B20, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x5268E0, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x527200, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x5474A0, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x54F280, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x561410, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x59D820, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x5A8800, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x5B4330, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x5D3F20, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x5EF2A0, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x6099E0, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x610A60, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x625500, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x625980, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x64FFB0, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x662EC0, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x662F80, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x671860, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x67B3B0, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x67D830, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x6857B0, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x68D300, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x68E8F0, "\xB8\x01\x00\x00\x00\xC3", 6);

    memory::PatchBytes(0x9A23B0, "\xB8\x01\x00\x00\x00\xC3", 6);  // Wrapper ExitProcess() check with HWBP detection,
    memory::PatchBytes(0x9A23F0, "\xB8\x01\x00\x00\x00\xC3", 6);  // executes on certain days of the week
    memory::PatchBytes(0x9A2430, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x9A2470, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x9A24B0, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x9A24F0, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x9A2530, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x9A2570, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x9A25B0, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x9A25F0, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x9A2630, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x9A2670, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x9A26B0, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x9A26F0, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x9A2730, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x9A2770, "\xB8\x01\x00\x00\x00\xC3", 6);

    memory::PatchBytes(0x9A2980, "\xB8\x01\x00\x00\x00\xC3", 6);  // Direct HWBP check
    memory::PatchBytes(0x9A29B0, "\xB8\x01\x00\x00\x00\xC3", 6);
    memory::PatchBytes(0x9A29E0, "\xB8\x01\x00\x00\x00\xC3", 6);

    // Detours::X86::DetourFunction((PBYTE)0x8EE640, (PBYTE)&sub_8EE640);  // Patch intentional nullptr
    memory::PatchNOP(0x8ee641, 12);

    // FixupFunction(0x0060CC10, 0x004F20F0);  // CEGObfuscate<LiveStats_Init> => LiveStats_Init
    // FixupFunction(0x0063DCC0, 0x0062DD40);  // CEGObfuscate<LiveStats_ResetStats> => LiveStats_ResetStats
    // FixupFunction(0x00580460, 0x0079E6D0);  // CEGObfuscate<Con_Restricted_SetLists> => Con_Restricted_SetLists
    memory::PatchJump(0x60CC10, 0x4F20F0);
    memory::PatchJump(0x63DCC0, 0x62DD40);
    memory::PatchJump(0x580460, 0x79E6D0);
}

};  // namespace components
};  // namespace game