#include <karm-sys/entry.h>

import Karm.Sys;

using namespace Karm;

Async::Task<> entryPointAsync(Sys::Context&) {
    Sys::Command cmd{"/bin/ls"s};
    auto proc = co_try$(cmd.run());
    co_try$(proc.wait());
    co_return Ok();
}
