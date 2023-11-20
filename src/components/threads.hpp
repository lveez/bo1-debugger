/* functions for debugging the games threads */
#pragma once

namespace components {
namespace threads {

/*  sets the game into developer mode, which is neede for
    debug info. Any hooks can be enabled here also. */
void OnAttach();

/*  prints the position (translated to source) of all threads
    if dump_to_file is true it also outputs it to thread_dump.txt
    if analysis is true it counts the duplicate thread positions (for leaks) */
void DebugThreads(bool dump_to_file, bool analysis);

};  // namespace threads
};  // namespace components