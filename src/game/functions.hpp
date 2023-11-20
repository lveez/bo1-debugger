/* Collection of functions from BO1. */
#pragma once

#include "structs.hpp"

namespace game {
namespace fn {

/* console */
__declspec(selectany) auto Field_Clear = reinterpret_cast<void (*)(types::field_t*)>(0x50db60);
__declspec(selectany) auto Con_CancelAutoComplete = reinterpret_cast<void (*)(void)>(0x51b6b0);

/* commands */
// __declspec(selectany) auto Dvar_AddCommands = reinterpret_cast<void (*)(void)>(0x600e00);
__declspec(selectany) auto Cmd_AddCommandInternal = reinterpret_cast<void (*)(const char*, void (*)(void), types::cmd_function_s*)>(0x661400);
// __declspec(selectany) auto Cmd_FindCommand = reinterpret_cast<types::cmd_function_s* (*)(char*)>(0x479dd0);
__declspec(selectany) auto Sys_GetValue = reinterpret_cast<void* (*)(int)>(0x67d4f0);

/* init */
// __declspec(selectany) auto Com_Init = reinterpret_cast<void (*)(char*)>(0x4069c0);
// __declspec(selectany) auto CG_Init = reinterpret_cast<void (*)(int, int, int, int)>(0x64f710);

/* scr parsing */
// __declspec(selectany) auto Scr_ReadFile_FastFile = reinterpret_cast<char* (*)(types::scriptInstance_t, char*, char*, char*, bool)>(0x8a57b0);
// __declspec(selectany) auto Scr_PrintPrevCodePos = reinterpret_cast<void (*)(types::scriptInstance_t, int, char*, unsigned int)>(0x685280);
// __declspec(selectany) auto Scr_GetSourceBuffer = reinterpret_cast<unsigned int (*)(types::scriptInstance_t, char*)>(0x649af0);
// __declspec(selectany) auto Scr_DumpScriptThreads = reinterpret_cast<void (*)(types::scriptInstance_t)>(0x687f50);

/* printing */
// __declspec(selectany) auto Com_PrintMessage = reinterpret_cast<void (*)(int, char*, int)>(0x43c520);
__declspec(selectany) auto Com_Printf = reinterpret_cast<void (*)(int, const char*)>(0x43bf30);

/* Dvars */
// __declspec(selectany) auto Dvar_FindVar = reinterpret_cast<const types::dvar_t* (*)(const char*)>(0x5ae810);
__declspec(selectany) auto Dvar_SetCommand = reinterpret_cast<void (*)(const char*, const char*)>(0x40c0d0);
__declspec(selectany) auto Dvar_GetString = reinterpret_cast<const char* (*)(const char*)>(0x57ff80);

/* allocation */
// __declspec(selectany) auto AllocValue = reinterpret_cast<unsigned int(__cdecl*)()>(0x8a6d20);
// __declspec(selectany) auto AllocVariable = reinterpret_cast<unsigned short (*)(int)>(0x51f7c0);

/* running scripts */
// __declspec(selectany) auto VM_Execute = reinterpret_cast<unsigned int (*)(types::scriptInstance_t, unsigned int, const char*, unsigned int)>(0x8ace60);

};  // namespace fn
};  // namespace game