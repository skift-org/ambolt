#include <karm-sys/entry.h>

import Karm.Fs;
import Karm.Cli;

using namespace Karm;

Async::Task<> entryPointAsync(Sys::Context& ctx, Async::CancellationToken) {
    auto mountOption = Cli::option<Ref::Url>(NONE, "mount"s, "volume to mount"s);
    auto fstabOption = Cli::option<Ref::Url>(NONE, "fstab"s, "Fs tab file to load and mount"s);
    auto pathOption = Cli::operand<Vec<Ref::Path>>("path"s, "Path to print information about"s);

    Cli::Command cmd{
        "disk-ls"s,
        "List the content of a disk image"s,
        {
            Cli::Section{
                .title = "Mount Options"s,
                .options = {mountOption, fstabOption},
            },
            Cli::Section{
                .title = "Listing Options"s,
                .options = {pathOption},
            },
        }
    };

    co_trya$(cmd.execAsync(ctx));
    if (not cmd)
        co_return Ok();

    if (not mountOption.has() and not fstabOption.has())
        co_return Error::invalidInput("volume not specified");

    auto root = co_trya$(Fs::mountAsync(mountOption.value()));

    for (auto& p : pathOption.value()) {
        if (pathOption.value().len())
            Sys::println("{}:", p);
        auto node = co_trya$(root->lookupAsync(p));
        auto entries = co_trya$(node->listAsync());
        for (auto entry : entries)
            Sys::print("{}{}\n", entry.name, entry.type == Sys::Type::DIR ? "/" : "");
        Sys::println();
    }

    co_return Ok();
}
