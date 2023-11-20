#include "console.hpp"

#include "../tools/memory.hpp"

#include "../game/functions.hpp"

namespace game {
namespace components {

void Con_ToggleConsole() {
    fn::Field_Clear(globals::g_consoleField);
    fn::Con_CancelAutoComplete();

    globals::g_consoleField->widthInPixels = 620;
    globals::g_consoleField->charHeight = 16.0;
    globals::g_consoleField->fixedSize = 1;

    /* con.outputVisible = false */
    *reinterpret_cast<bool*>(0xc6924c) = false;
    /* clientUIActives->keyCatches ^= 1 */
    *reinterpret_cast<int*>(0x2910160) ^= 1;
}

void EnableConsole() {
    /* let console show suggestions */
    memory::PatchNOP(0x5f5d4e, 2);
    memory::PatchNOP(0x610a94, 2);
    memory::PatchNOP(0x82Ee63c, 6);

    /* toggle console is removed so replace calls to it */
    memory::PatchCall(0x587dc8, reinterpret_cast<unsigned int>(Con_ToggleConsole)); /* replace removed function */
    memory::PatchCall(0x587633, reinterpret_cast<unsigned int>(Con_ToggleConsole)); /* replace removed function */
    memory::PatchBytes(0x58761c, "\xEB", 1);                                        /* always jump */

    /* remove #dcr# check (allows commands to be used) */
    memory::PatchNOP(0x829b42, 5);
}

};  // namespace components
};  // namespace game