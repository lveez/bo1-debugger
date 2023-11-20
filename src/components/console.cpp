#include "console.hpp"

#include <thread>

#include "../tools/memory.hpp"

#include "../game/functions.hpp"

#include "../components/threads.hpp"

namespace components {
namespace console {

namespace g = game;

void Con_ToggleConsole() {
    g::fn::Field_Clear(g::globals::g_consoleField);
    g::fn::Con_CancelAutoComplete();

    g::globals::g_consoleField->widthInPixels = 620;
    g::globals::g_consoleField->charHeight = 16.0;
    g::globals::g_consoleField->fixedSize = 1;

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

/* add console commands */
void DumpThreads();
void DumpThreadsAndAnalyse();
void DumpThreadsToFile();
void DumpThreadsToFileAndAnalyse();
void __cdecl GivePoints(); /* __cdecl or crashes randomly */

void AddConsoleCommands() {
    /* this never gets deleted... */
    g::types::cmd_function_s* funcs = new g::types::cmd_function_s[5];
    g::fn::Cmd_AddCommandInternal("dumpthreads", DumpThreads, funcs);
    g::fn::Cmd_AddCommandInternal("dumpthreadsf", DumpThreadsToFile, &funcs[1]);
    g::fn::Cmd_AddCommandInternal("dumpthreadsa", DumpThreadsAndAnalyse, &funcs[2]);
    g::fn::Cmd_AddCommandInternal("dumpthreadsaf", DumpThreadsToFileAndAnalyse, &funcs[3]);
    g::fn::Cmd_AddCommandInternal("points", GivePoints, &funcs[4]);
}

/* these should be threaded otherwise they cause stutter */
/* TODO: is threading like this safe? */
void DumpThreads() {
    std::thread{threads::DebugThreads, false, false}.detach();
}

void DumpThreadsAndAnalyse() {
    std::thread{threads::DebugThreads, false, true}.detach();
}

void DumpThreadsToFile() {
    std::thread{threads::DebugThreads, true, false}.detach();
}

void DumpThreadsToFileAndAnalyse() {
    std::thread{threads::DebugThreads, true, true}.detach();
}

void __cdecl GivePoints() { /* cdecl or crashes randomly */
    g::types::CmdArgs* args = reinterpret_cast<g::types::CmdArgs*>(g::fn::Sys_GetValue(4));
    int argc = args->argc[args->nesting];

    if (argc != 2) {
        g::fn::Com_Printf(0, "USAGE: points <amount>");
        return;
    }

    std::string p_string = args->argv[args->nesting][1];
    int points = 0;
    try {
        points = std::stoi(p_string);
    } catch (...) {
        g::fn::Com_Printf(0, "Amount must be an integer.");
        return;
    }

    /* points address */
    *reinterpret_cast<int*>(0x1c0a6c8) = points;
}

void OnAttach() {
    EnableConsole();
    AddConsoleCommands();
}

}  // namespace console
};  // namespace components