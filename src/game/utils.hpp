#pragma once

#include "structs.hpp"

namespace game {
namespace utils {

bool IsStackVariable(const types::VariableValueInternal& var);

/*  Adapted from Scr_GetPrevSourcePos
    takes a codePos and returns its position in the source buffer
    returns 0xffffffff on failure (MAX_UINT32) */
unsigned int GetSourceBufferPosition(types::scriptInstance_t script_instance, const char* code_pos, unsigned int index);

/*  my version of Scr_GetSourceBuffer
    returns the index in sourceBufferLookup that the codepos is contained in
    returns 0xffffffff on failure */
unsigned int GetSourceBufferIndex(types::scriptInstance_t script_instance, const char* code_pos);

/* returns the function that contains the position of the source_pos */
/* returns "" on failure */
/* TODO: this function should probably have a more sophisticated search */
std::string GetFunctionName(const char* source_buf, unsigned int source_pos);

/*  Takes a codePos char* and finds the source buffer
    and source position to get the file, function and line number
    returns "" on failure */
std::string FormatCodePos(const char* code_pos);

/* calculates number of new lines up to the source pos */
size_t GetLineNumber(const char* source_buf, unsigned int source_pos);

};  // namespace utils
};  // namespace game