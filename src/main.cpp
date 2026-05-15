#include <karm/entry>

import Karm.Sys;

using namespace Karm;
using namespace Karm::Literals;

Async::Task<> entryPointAsync(Sys::Env&, Async::CancellationToken) {
    Sys::Command cmd{"/bin/ls"s};
    auto proc = co_try$(cmd.spawn());
    co_try$(proc.wait());
    co_return Ok();
}
