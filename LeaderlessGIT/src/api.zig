const std = @import("std");
const zap = @import("zap");
const database = @import("database.zig");

const ApiError = error {
    NoAuthToken,
    BadAuthToken,
    MethodNotAllowed,
    InvalidRequest,
    UsernameTaken,
    UserNotFound,
    InvalidPassword,
    FieldTooLong,
    NotFound
};

fn getUsernameFromToken(token: []const u8) ![]const u8 {
    const dot_pos = std.mem.indexOfScalar(u8, token, '.');

    if(dot_pos == null) {
        return ApiError.BadAuthToken;
    }

    const username_hash = token[0..dot_pos.?];
    const salt = token[dot_pos.? + 1..];

    try database.verifyToken(username_hash, salt);

    const username_size = try std.base64.standard.Decoder.calcSizeForSlice(username_hash);

    const username = try std.heap.page_allocator.alloc(u8, username_size);
    _ = try std.base64.standard.Decoder.decode(username, username_hash);

    return username;
}


fn serveAPI404(r: zap.Request) void {
    r.sendJson("{ \"error\": \"404 not found\" }") catch unreachable;
}
fn newPost(r: zap.Request) void {
    if(r.methodAsEnum() != zap.Method.POST) {
        r.sendError(ApiError.MethodNotAllowed,if (@errorReturnTrace()) |t| t.* else null,405);
        return;
    }
    const name = r.getHeader("post-name");
    const token = r.getHeader("auth-token");

    if (token == null) {
        r.sendError(ApiError.NoAuthToken,if (@errorReturnTrace()) |t| t.* else null,401);
        return;
    }

    if(name == null) {
        r.sendError(ApiError.InvalidRequest,if (@errorReturnTrace()) |t| t.* else null,400);
        return;
    }

    if (name.?.len > 64) {
        r.sendError(ApiError.FieldTooLong,if (@errorReturnTrace()) |t| t.* else null,400);
        return;
    }
    if(token.?.len > 256) {
        r.sendError(ApiError.FieldTooLong,if (@errorReturnTrace()) |t| t.* else null,400);
        return;
    }


    const username = getUsernameFromToken(token.?) catch |e| {
        r.sendError(e,if (@errorReturnTrace()) |t| t.* else null,401);
        return;
    };

    const author = database.getUserByUsername(username) catch |e| {
        r.sendError(e,if (@errorReturnTrace()) |t| t.* else null,400);
        return;
    };

    _ =std.io.getStdOut().write("Post posted with name \"") catch unreachable;
    _ =std.io.getStdOut().write(name.?) catch unreachable;
    _ =std.io.getStdOut().write("\"!\n") catch unreachable;

    var new_id = database.getHighestPostId() catch unreachable;
    new_id += 1;

    database.insertPost(.{.id = new_id, .type = 0, .title = name.?, .author_id = author.id, .timestamp = std.time.timestamp()}) catch unreachable;
}

fn getSpecificPost(r: zap.Request) void {
    if(r.methodAsEnum() != zap.Method.GET) {
        r.sendError(ApiError.MethodNotAllowed,if (@errorReturnTrace()) |t| t.* else null,405);
        return;
    }

    const id = std.fmt.parseInt(i64, r.path.?[15..], 10) catch {
        //r.sendBody(r.path.?[15..]) catch unreachable;
        r.sendError(ApiError.InvalidRequest,if (@errorReturnTrace()) |t| t.* else null,400);
        return;
    };

    const post = database.getPost(id) catch |e| {
        r.sendError(e,if (@errorReturnTrace()) |t| t.* else null,404);
        return;
    };

    var string = std.ArrayList(u8).init(std.heap.page_allocator);
    std.json.stringify(post, .{}, string.writer()) catch unreachable;

    r.sendJson(string.items) catch unreachable;
}

fn servePosts(r: zap.Request) void {
    if(std.mem.startsWith(u8, r.path.?, "/api/posts/new")) {
        newPost(r);
        return;
    }
    if(std.mem.startsWith(u8, r.path.?, "/api/posts/get")) {
        getSpecificPost(r);
        return;
    }

    if(r.methodAsEnum() != zap.Method.GET) {
        r.sendError(ApiError.MethodNotAllowed,if (@errorReturnTrace()) |t| t.* else null,405);
        return;
    }

    var batch_num = r.getHeader("batch-num");
    var batch_size = r.getHeader("batch-size");

    if(batch_num == null){
        batch_num = "0";
    }
    
    if(batch_size == null){
        batch_size = "10";
    }

    const num_batch_num = std.fmt.parseInt(u64, batch_num.?, 10) catch unreachable;
    const num_batch_size = std.fmt.parseInt(u64, batch_size.?, 10) catch unreachable;

    const posts = database.getLatestPosts(num_batch_size,num_batch_num) catch unreachable;

    var string = std.ArrayList(u8).init(std.heap.page_allocator);
    std.json.stringify(posts, .{}, string.writer()) catch unreachable;

    r.sendJson(string.items) catch unreachable;
}

fn registerUser(r: zap.Request) void {
    if(r.methodAsEnum() != zap.Method.POST) {
        r.sendError(ApiError.MethodNotAllowed,if (@errorReturnTrace()) |t| t.* else null,405);
        return;
    }

    const name = r.getHeader("new-username");
    const passwd = r.getHeader("new-password-hash");

    if(name == null or passwd == null) {
        r.sendError(ApiError.InvalidRequest,if (@errorReturnTrace()) |t| t.* else null,400);
        return;
    }

    if(name.?.len > 64) {
        r.sendError(ApiError.FieldTooLong,if (@errorReturnTrace()) |t| t.* else null,400);
        return;
    }

    if (passwd.?.len > 256) {
        r.sendError(ApiError.FieldTooLong,if (@errorReturnTrace()) |t| t.* else null,400);
        return;
    }


    if(!database.isUsernameAvailable(name.?)) {
        r.sendError(ApiError.UsernameTaken,if (@errorReturnTrace()) |t| t.* else null,409);
        return;
    }

    var new_id = database.getHighestUserId() catch unreachable;
    new_id += 1;

    database.register(.{.id = new_id, .username = name.?, .passwd_hash = passwd.?, .avatar_url = ""}) catch unreachable;
}

fn login(r: zap.Request) void {
    if(r.methodAsEnum() != zap.Method.POST) {
        r.sendError(ApiError.MethodNotAllowed,if (@errorReturnTrace()) |t| t.* else null,405);
        return;
    }

    const name = r.getHeader("username");
    const passwd = r.getHeader("password-hash");

    if(name == null or passwd == null) {
        r.sendError(ApiError.InvalidRequest,if (@errorReturnTrace()) |t| t.* else null,400);
        return;
    }

    if(database.isUsernameAvailable(name.?)) {
        r.sendError(ApiError.UserNotFound,if (@errorReturnTrace()) |t| t.* else null,404);
        return;
    }

    const u = database.getUserByUsername(name.?) catch |e| {
        r.sendError(e,if (@errorReturnTrace()) |t| t.* else null,500);
        return;
    };

    if(!std.mem.eql(u8,u.passwd_hash, passwd.?)) {
        r.sendError(ApiError.InvalidPassword,if (@errorReturnTrace()) |t| t.* else null,401);
        return;
    }

    const token = database.generateToken(u.username) catch |e| {
        r.sendError(e,if (@errorReturnTrace()) |t| t.* else null,500);
        return;
    };

    var json = std.ArrayList(u8).init(std.heap.page_allocator);

    _ = std.json.stringify(.{.token = token}, .{}, json.writer()) catch unreachable;

    r.sendJson(json.items) catch unreachable;
}

fn getSpecificUser(r: zap.Request) void {
    if(r.methodAsEnum() != zap.Method.GET) {
        r.sendError(ApiError.MethodNotAllowed,if (@errorReturnTrace()) |t| t.* else null,405);
        return;
    }

    const id = std.fmt.parseInt(i64, r.path.?[15..], 10) catch {
        //r.sendBody(r.path.?[15..]) catch unreachable;
        r.sendError(ApiError.InvalidRequest,if (@errorReturnTrace()) |t| t.* else null,400);
        return;
    };

    var u = database.getUser(id) catch |e| {
        r.sendError(e,if (@errorReturnTrace()) |t| t.* else null,500);
        return;
    };

    u.passwd_hash = "n0pe";

    var json = std.ArrayList(u8).init(std.heap.page_allocator);
    _ = std.json.stringify(u, .{}, json.writer()) catch unreachable;
    r.sendJson(json.items) catch unreachable;
}


fn serveUsers(r: zap.Request) void {
    if(std.mem.startsWith(u8, r.path.?, "/api/users/register")) {
        registerUser(r);
        return;
    }
    if(std.mem.startsWith(u8, r.path.?, "/api/users/login")) {
        login(r);
        return;
    }
    if(std.mem.startsWith(u8, r.path.?, "/api/users/get")) {
        getSpecificUser(r);
        return;
    }

    serveAPI404(r);
}


pub fn serve(r: zap.Request) void {
    r.setHeader("Cache-Control", "no-cache") catch unreachable;

    if(std.mem.startsWith(u8, r.path.?, "/api/posts")) {
        servePosts(r);
        return;
    }
    if(std.mem.startsWith(u8, r.path.?, "/api/users")) {
        serveUsers(r);
        return;
    }

    serveAPI404(r);
}