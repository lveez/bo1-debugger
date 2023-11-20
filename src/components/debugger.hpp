/* functions for debugging the games threads */
#pragma once

namespace game {
namespace components {

namespace dbg {

/*  sets the game into developer mode, which is neede for
    debug info. Any hooks can be enabled here also. */
void Initialize();

void DebugThreads(bool dump_to_file, bool analysis);

};  // namespace dbg

};  // namespace components
};  // namespace game