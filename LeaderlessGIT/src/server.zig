const std = @import("std");
const zap = @import("zap");
const api = @import("api.zig");


fn serve404(r: zap.Request) void {
    if (r.sendFile("frontend/dist/404.html")) {} else |_| {
        std.debug.print("Error: 404 page not found: {s}\n", .{r.path.?});
        std.process.exit(1);
    }
}

pub fn serve(r: zap.Request) void {
    r.setHeader("Cache-Control", "no-cache") catch unreachable;

    if(std.mem.startsWith(u8, r.path.?, "/api/")) {
        api.serve(r);
        return;
    }

    const path1 = std.fmt.allocPrint(std.heap.page_allocator, "frontend/dist{s}/index.html", .{r.path.?}) catch |err| {
        std.debug.print("FATAL ERROR: {?}\n", .{err});
        std.process.exit(1);
    };
    defer std.heap.page_allocator.free(path1);
    if (r.sendFile(path1)) {} else |_| {
        serve404(r);
    }
}