#include <karm-sys/entry.h>

using namespace Karm;

Async::Task<> entryPointAsync(Sys::Context&) {
    Sys::println("{}", Sys::dateTime());
    co_return Ok();
}
