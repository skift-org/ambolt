#include <karm-sys/entry.h>

import Karm.Cli;
import Karm.Http;
import Karm.Core;

using namespace Karm;

Async::Task<> entryPointAsync(Sys::Context& ctx, Async::CancellationToken ct) {
    auto urlArg = Cli::operand<Str>("url"s, "URL to fetch"s, "localhost"s);

    Cli::Command cmd{
        "http-head"s,
        "Send a HEAD request to a URL and print the response headers"s,
        {
            {
                "Request Options"s,
                {
                    urlArg,
                },
            },
        }
    };

    co_trya$(cmd.execAsync(ctx));

    auto url = Ref::parseUrlOrPath(urlArg.value(), co_try$(Sys::pwd()));
    auto header = co_trya$(Http::headAsync(url, ct))->header;
    co_try$(header.unparse(Sys::out()));

    co_return Ok();
}
