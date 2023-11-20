#include "threads.hpp"

#include <fstream>
#include "../stdc++.hpp"

#include "../game/functions.hpp"
#include "../game/utils.hpp"

namespace components {
namespace threads {

namespace g = game;

void DebugThreads(bool dump_to_file, bool analysis) {
    if (g::globals::gScrVarPub[0].developer == false) {
        return;
    }

    std::vector<g::types::ThreadDebugInfo> thread_information; /* stores information for all found threads */

    g::types::ThreadDebugInfo current_thread_info;
    g::types::VariableStackBuffer* current_stack_buffer;
    g::types::VariableUnion current_variable;

    auto game_vars = std::span{g::globals::gScrVarGlob[0].variableList, 65536};
    for (const auto& var : game_vars) {
        current_thread_info.pos.clear();

        /* discard all non-stack variables */
        if (g::utils::IsStackVariable(var) == false) {
            continue;
        }

        current_stack_buffer = var.u.u.stackValue;
        if (current_stack_buffer == nullptr || current_stack_buffer->buf == nullptr) {
            continue;
        }

        /* check stack for VAR_CODEPOS and add to current thread info */
        for (size_t i = 0; i < current_stack_buffer->size; i += 5) {
            if (*(current_stack_buffer->buf + i) == g::types::VAR_CODEPOS) {
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
            thread_positions.push_back(g::utils::FormatCodePos(pos));
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

void OnAttach() {
    /* enable dev mode */
    g::fn::Dvar_SetCommand("developer", "1");
}

};  // namespace threads
};  // namespace components