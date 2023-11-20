#include "utils.hpp"

namespace game {
namespace utils {

bool IsStackVariable(const types::VariableValueInternal& var) {
    if (var.w.status & 0x60 == 0)  // status = free
        return false;

    if ((var.w.type & 0x1f) == types::VAR_STACK)
        return true;

    return false;
}

unsigned int GetSourceBufferPosition(types::scriptInstance_t script_instance, const char* code_pos, unsigned int index) {
    if (globals::gScrVarPub[script_instance].developer == false) {
        return 0xffffffff;
    }

    size_t idx = globals::gScrParserGlob[script_instance].opcodeLookupLen - 1;
    for (idx; idx >= 0; idx--) {
        if (globals::gScrParserGlob[script_instance].opcodeLookup[idx].codePos == nullptr) {
            return 0xffffffff;
        }

        if (globals::gScrParserGlob[script_instance].opcodeLookup[idx].codePos < code_pos)
            break;

        if (idx == 0)
            return 0xffffffff;
    }

    return globals::gScrParserGlob[script_instance].sourcePosLookup[globals::gScrParserGlob[script_instance].opcodeLookup[idx].sourcePosIndex + index].sourcePos;
}

unsigned int GetSourceBufferIndex(types::scriptInstance_t script_instance, const char* code_pos) {
    if (globals::gScrVarPub[script_instance].developer == false) {
        return 0xffffffff;
    }

    /* start at top, find first codepos lower than our codepos and return that source buffer index */
    for (size_t idx = globals::gScrParserPub[script_instance].sourceBufferLookupLen - 1; idx >= 0; idx--) {
        if (globals::gScrParserPub[script_instance].sourceBufferLookup[idx].codePos == nullptr)
            continue;

        if (globals::gScrParserPub[script_instance].sourceBufferLookup[idx].codePos < code_pos)
            return idx;
    }
    return 0xffffffff;
}

std::string GetFunctionName(const char* source_buf, unsigned int source_pos) {
    /*  work backwards to the beginning of the source buffer, the
        first new line that contains a function call is the calling function */
    for (size_t i = source_pos; i > 0; i--) {
        /* not a new line, function can't be adjacent */
        if (source_buf[i] != '\0') {
            continue;
        }

        /* if next character after a new line isn't a brace, the line doesn't contain the function name */
        if (source_buf[i + 1] != '{') {
            continue;
        }

        /* we have the correct line, work back to the beginning to get the fn name */
        for (size_t j = i - 1; j > 0; j--) {
            if (source_buf[j] == '\0') {
                return std::string(source_buf + j + 1);
            }
        }
    }

    return "";
}

std::string FormatCodePos(const char* code_pos) {
    unsigned int source_pos = GetSourceBufferPosition(types::SCRIPTINSTANCE_SERVER, code_pos, 0);
    if (source_pos == 0xffffffff) {
        return "";
    }

    unsigned int source_buffer_index = GetSourceBufferIndex(types::SCRIPTINSTANCE_SERVER, code_pos);
    if (source_buffer_index == 0xffffffff) {
        return "";
    }

    /* get file name from source buffer */
    std::string calling_file = globals::gScrParserPub[0].sourceBufferLookup[source_buffer_index].buf;

    /* get calling function name */
    std::string calling_fn = GetFunctionName(globals::gScrParserPub[0].sourceBufferLookup[source_buffer_index].sourceBuf,
                                             source_pos);

    size_t line_number = GetLineNumber(globals::gScrParserPub[0].sourceBufferLookup[source_buffer_index].sourceBuf,
                                       source_pos);

    std::string line = (globals::gScrParserPub[0].sourceBufferLookup[source_buffer_index].sourceBuf + source_pos);

    return std::format("{} [{}]\n{}\n{}\n", calling_file, line_number, calling_fn, line);
}

size_t GetLineNumber(const char* source_buf, unsigned int source_pos) {
    size_t line_num = 1;
    /* Look for new line characters, and increment the line num */
    for (int i = 0; i <= source_pos; i++) {
        if (source_buf[i] == '\0') {
            line_num++;
        }
    }
    return line_num;
}

};  // namespace utils
};  // namespace game