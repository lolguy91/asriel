const zap = @import("zap");
const std = @import("std");
const server = @import("server.zig");
const database = @import("database.zig");

fn nocert(filename: []const u8, err: anyerror) void {
    std.debug.print("Error: no certificate found at {s}: {s}\n", .{ filename, @errorName(err) });
    std.process.exit(1);
}

pub fn main() !void {

        try database.init();

        const CERT_FILE = "certificates/mycert.pem";
        const KEY_FILE = "certificates/mykey.pem";

        std.fs.cwd().access(CERT_FILE, .{}) catch |err| {
            nocert(CERT_FILE, err);
        };

        std.fs.cwd().access(KEY_FILE, .{}) catch |err| {
            nocert(KEY_FILE, err);
        };

        const tls = try zap.Tls.init(.{
            .server_name = "localhost:3000",
            .public_certificate_file = CERT_FILE,
            .private_key_file = KEY_FILE,
        });
        defer tls.deinit();

        // setup listener
        var listener = zap.HttpListener.init(
            .{
                .port = 3000,
                .on_request = server.serve,
                .log = true,
                .public_folder = "frontend/dist",
                .max_clients = 100000,
                .max_body_size = 100 * 1024 * 1024,
                .tls = tls,
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