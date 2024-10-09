const zap = @import("zap");
const std = @import("std");
const server = @import("server.zig");
const database = @import("database.zig");

pub fn main() !void {
    try database.init();

    // setup listener
    var listener = zap.HttpListener.init(
        .{
            .port = 3000,
            .on_request = server.serve,
            .log = true,
            .public_folder = "frontend/dist",
        },
    );
    try listener.listen();

    std.debug.print("Listening on 0.0.0.0:3000\n", .{});

    // and run
    zap.start(.{
        .threads = 12,
        .workers = 1,
    });
}
