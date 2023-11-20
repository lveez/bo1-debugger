#include "debugger.hpp"

#include <fstream>
#include "../stdc++.hpp"

#include "../game/functions.hpp"

namespace game {
namespace components {

namespace dbg {

bool IsStackVariable(const types::VariableValueInternal& var) {
    if (var.w.status & 0x60 == 0)  // status = free
        return false;

    if ((var.w.type & 0x1f) == types::VAR_STACK)
        return true;

    return false;
}

/*  Adapted from Scr_GetPrevSourcePos
    takes a codePos and returns its position in the source buffer
    returns 0xffffffff on failure (MAX_UINT32) */
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

/*  my version of Scr_GetSourceBuffer
    returns the index in sourceBufferLookup that the codepos is contained in
    returns 0xffffffff on failure */
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

/* returns the function that contains the position of the source_pos */
/* returns "" on failure */
/* TODO: this function should probably have a more sophisticated search */
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

/* calculates number of new lines up to the source pos */
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

/*  Takes a codePos char* and finds the source buffer
    and source position to get the file, function and line number
    returns "" on failure */
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

void DebugThreads(bool dump_to_file, bool analysis) {
    if (globals::gScrVarPub[0].developer == false) {
        return;
    }

    std::vector<types::ThreadDebugInfo> thread_information; /* stores information for all found threads */

    types::ThreadDebugInfo current_thread_info;
    types::VariableStackBuffer* current_stack_buffer;
    types::VariableUnion current_variable;

    auto game_vars = std::span{globals::gScrVarGlob[0].variableList, 65536};
    for (const auto& var : game_vars) {
        current_thread_info.pos.clear();

        /* discard all non-stack variables */
        if (IsStackVariable(var) == false) {
            continue;
        }

        current_stack_buffer = var.u.u.stackValue;
        if (current_stack_buffer == nullptr || current_stack_buffer->buf == nullptr) {
            continue;
        }

        /* check stack for VAR_CODEPOS and add to current thread info */
        for (size_t i = 0; i < current_stack_buffer->size; i += 5) {
            if (*(current_stack_buffer->buf + i) == types::VAR_CODEPOS) {
                current_variable.intValue = *reinterpret_cast<int*>(current_stack_buffer + i + 1);
                current_thread_info.pos.push_back(current_variable.codePosValue);
            }
        }

        /* treyarch does it backwards so reverse it to match them */
        std::reverse(current_thread_info.pos.begin(), current_thread_info.pos.end());
        current_thread_info.pos.push_back(current_stack_buffer->pos);

        /* here you can get var and endon usage if you want to (TODO) */

        thread_information.push_back(current_thread_info);
    }

    std::ofstream file;
    if (thread_information.size() == 0) {
        return;
    }

    if (dump_to_file == true) {
        file.open("thread_dump.txt", std::ios::trunc | std::ios::out);
    }

    std::vector<std::string> thread_positions;
    std::vector<std::pair<std::string, int>> thread_pos_count; /* stores the count of each thread pos */

    for (const auto& thread : thread_information) {
        for (auto& pos : thread.pos) {
            thread_positions.push_back(FormatCodePos(pos));
        }

        /* save time if they don't want to see the counts and ordered */
        if (analysis == false) {
            continue;
        }

        /* if first time position has been seen add it to vector */
        /* TODO: can we increment count here aswell ? seems pointless to iterate twice */
        if (std::ranges::find(thread_pos_count, thread_positions.back(), &std::pair<std::string, int>::first) == thread_pos_count.end()) {
            thread_pos_count.push_back({thread_positions.back(), 0});
        }
    }

    /* sort strings so same threads are near eachother */
    std::sort(thread_positions.begin(), thread_positions.end(),
              [](const std::string& lhs, const std::string& rhs) {
                  return lhs.substr(0, lhs.find_first_of('\n')) < rhs.substr(0, rhs.find_first_of('\n'));
              });

    /* print all thread positions */
    for (const auto& thread_pos : thread_positions) {
        if (file.is_open()) {
            file << thread_pos;
        }
        std::cout << thread_pos;
    }

    if (file.is_open()) {
        file << thread_information.size() << " threads debugged.\n";
    }
    std::cout << thread_information.size() << " threads debugged.\n";

    if (analysis == false) {
        if (file.is_open()) {
            file.close();
        }
        return;
    }

    /* formatting */
    if (file.is_open()) {
        file << "\n\n\n";
    }
    std::cout << "\n\n\n";

    /* use two seperate for loops so can sort by count */
    /* count uses of each thread pos */
    for (auto& thread : thread_pos_count) {
        thread.second = std::count(thread_positions.begin(), thread_positions.end(), thread.first);
    }

    /* sort so highest count is at the bottom */
    std::ranges::sort(
        thread_pos_count.begin(),
        thread_pos_count.end(),
        [](const auto& lhs, const auto& rhs) {
            return lhs < rhs;
        },
        &std::pair<std::string, int>::second);

    for (const auto& thread : thread_pos_count) {
        /* print uses */
        if (file.is_open()) {
            file << thread.first;
            file << "count: " << thread.second << "\n\n";
        }
        std::cout << thread.first;
        std::cout << "count: " << thread.second << "\n\n";
    }

    file.close();
}

void Initalize() {
    /* enable dev mode */
    fn::Dvar_SetCommand("developer", "1");
}

};  // namespace dbg

};  // namespace components
};  // namespace game