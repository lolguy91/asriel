const sqlite = @import("sqlite");
const std = @import("std");

var db: sqlite.Db = undefined;

pub const Post = struct { id: i64, type: i64, title: []const u8, author_id: i64, timestamp: i64 };

pub const User = struct {
    id: i64,
    username: []const u8,
    avatar_url: []const u8,
    passwd_hash: []const u8,
};

fn createTables() !void {
    _ = std.io.getStdOut().write("Initializing database...\n") catch unreachable;
    const create_posts_cmd =
        \\CREATE TABLE Posts (
        \\    id int,
        \\    type int,
        \\    title vchar(255),
        \\    author_id int,
        \\    timestamp int
        \\);
    ;
    var create_posts = try db.prepare(create_posts_cmd);
    defer create_posts.deinit();
    try create_posts.exec(.{}, .{});

    const create_users_cmd =
        \\CREATE TABLE Users (
        \\    id int,
        \\    username vchar(255),
        \\    avatar_url vchar(255),
        \\    passwd_hash vchar(255)
        \\);
    ;
    var create_users = try db.prepare(create_users_cmd);
    defer create_users.deinit();
    try create_users.exec(.{}, .{});

    const create_tokens_cmd =
        \\CREATE TABLE Tokens (
        \\    username_base64 vchar(255),
        \\    salt vchar(255)
        \\);
    ;
    var create_tokens = try db.prepare(create_tokens_cmd);
    defer create_tokens.deinit();
    try create_tokens.exec(.{}, .{});

    const create_messages_cmd =
        \\CREATE TABLE Messages (
        \\    id int,
        \\    post_id int,
        \\    content vchar(255),
        \\    author_id int,
        \\    timestamp int
        \\);
    ;
    var create_messages = try db.prepare(create_messages_cmd);
    defer create_messages.deinit();
    try create_messages.exec(.{}, .{});

    const create_polls_cmd =
        \\CREATE TABLE Polls (
        \\    id int,
        \\    post_id int,
        \\    yes_count int,
        \\    no_count int,
        \\    created_at int,
        \\    lasts_for int
        \\);
    ;
    var create_polls = try db.prepare(create_polls_cmd);
    defer create_polls.deinit();
    try create_polls.exec(.{}, .{});

    const create_repos_cmd =
        \\CREATE TABLE Repos (
        \\    id int,
        \\    name vchar,
        \\    desc vchar,
        \\    open bool
        \\);
    ;
    var create_repos = try db.prepare(create_repos_cmd);
    defer create_repos.deinit();
    try create_repos.exec(.{}, .{});
}
pub fn init() !void {
    var isDbNew = false;

    std.fs.cwd().access("database.db", .{}) catch |err| {
        if (err == error.FileNotFound) {
            isDbNew = true;
        }
    };

    db = try sqlite.Db.init(.{
        .mode = sqlite.Db.Mode{ .File = "database.db" },
        .open_flags = .{
            .write = true,
            .create = true,
        },
        .threading_mode = .MultiThread,
    });

    if (isDbNew) {
        try createTables();
    }
}

pub fn deinit() void {
    db.deinit();
}

//===================Post Stuff===================
pub fn insertPost(post: Post) !void {
    const query = "INSERT INTO Posts (id, type, title, author_id,timestamp) VALUES (?, ?, ?, ?, ?);";
    var stmt = try db.prepare(query);
    defer stmt.deinit();

    try stmt.exec(.{}, .{ post.id, post.type, post.title, post.author_id, post.timestamp });
}
pub fn getLatestPosts(batch_size: u64, batch_num: u64) ![]Post {
    const query = "SELECT id, type, title, author_id, timestamp FROM Posts ORDER BY id DESC LIMIT ? OFFSET ? * ?;";
    var stmt = try db.prepare(query);
    defer stmt.deinit();

    const ids = try stmt.all(Post, std.heap.page_allocator, .{}, .{ batch_size, batch_num, batch_size });

    return ids;
}

pub fn getPost(id: i64) !Post {
    const query = "SELECT id, type, title, author_id,timestamp FROM Posts WHERE id = ?;";

    var stmt = try db.prepare(query);
    defer stmt.deinit();
    const post = try stmt.oneAlloc(Post, std.heap.page_allocator, .{}, .{id});

    if (post == null) {
        return error.PostNotFound;
    }

    return post.?;
}

pub fn getHighestPostId() !i64 {
    const query = "SELECT MAX(id) FROM Posts;";
    var stmt = try db.prepare(query);
    defer stmt.deinit();

    return (try stmt.one(i64, .{}, .{})).?;
}

//===================User Stuff===================

pub fn getHighestUserId() !i64 {
    const query = "SELECT MAX(id) FROM Users;";
    var stmt = try db.prepare(query);
    defer stmt.deinit();

    return (try stmt.one(i64, .{}, .{})).?;
}

pub fn register(user: User) !void {
    const query = "INSERT INTO Users (id, username, avatar_url, passwd_hash) VALUES (?, ?, ?, ?);";
    var stmt = try db.prepare(query);
    defer stmt.deinit();

    try stmt.exec(.{}, .{ user.id, user.username, user.avatar_url, user.passwd_hash });
}

pub fn getUser(id: i64) !User {
    const query = "SELECT id, username, avatar_url, passwd_hash FROM Users WHERE id = ?;";

    var stmt = try db.prepare(query);
    defer stmt.deinit();

    const user = try stmt.oneAlloc(User, std.heap.page_allocator, .{}, .{id});

    if (user == null) {
        return error.UserNotFound;
    }

    return user.?;
}

pub fn getUserByUsername(username: []const u8) !User {
    const query = "SELECT id, username, avatar_url, passwd_hash FROM Users WHERE username = ?;";

    var stmt = try db.prepare(query);
    defer stmt.deinit();

    const user = try stmt.oneAlloc(User, std.heap.page_allocator, .{}, .{username});

    if (user == null) {
        return error.UserNotFound;
    }

    return user.?;
}

pub fn generateToken(username: []const u8) ![]const u8 {
    var username_base64: [64]u8 = [_]u8{0} ** 64;
    _ = std.base64.standard.Encoder.encode(username_base64[0..], username);
    const username_base64_size = std.base64.standard.Encoder.calcSize(username.len);

    const check_query = "SELECT COUNT(*) FROM Tokens WHERE username_base64 = ?;";

    var check_stmt = try db.prepare(check_query);
    defer check_stmt.deinit();

    const count = try check_stmt.one(i64, .{}, .{username_base64[0..username_base64_size]});

    var salt: [64]u8 = [_]u8{0} ** 64;
    var salt_size: usize = 0;

    if (count == 0) {
        const salt_int = std.crypto.random.int(u64);
        var salt_raw: [16]u8 = undefined;
        _ = std.fmt.bufPrint(salt_raw[0..16], "{x}", .{salt_int}) catch unreachable;
        _ = std.base64.standard.Encoder.encode(salt[0..], salt_raw[0..]);
        salt_size = std.base64.standard.Encoder.calcSize(16);

        const query = "INSERT INTO Tokens (username_base64, salt) VALUES (?, ?);";

        var stmt = try db.prepare(query);
        defer stmt.deinit();

        try stmt.exec(.{}, .{ username_base64[0..username_base64_size], salt[0..salt_size] });
    } else {
        const query = "SELECT token FROM Tokens WHERE username_base64 = ?;";
        var stmt = try db.prepare(query);
        defer stmt.deinit();

        const newsalt = (try stmt.oneAlloc([]const u8, std.heap.page_allocator, .{}, .{username_base64})).?[0..];

        salt_size = newsalt.len;

        std.mem.copyForwards(u8, salt[0..], newsalt);
    }

    const token_str = try std.fmt.allocPrint(std.heap.page_allocator, "{s}.{s}", .{ username_base64[0..username_base64_size], salt[0..salt_size] });

    return token_str[0..(username_base64_size + salt_size + 1)];
}

pub fn deleteToken(username_base64: []const u8, salt: []const u8) !void {
    const query = "DELETE FROM Tokens WHERE username_base64 = ? AND salt = ?;";
    var stmt = try db.prepare(query);
    defer stmt.deinit();

    try stmt.exec(.{}, .{ username_base64, salt });
}

pub fn verifyToken(username_base64: []const u8, salt: []const u8) !void {
    const query = "SELECT COUNT(*) FROM Tokens WHERE username_base64=? AND salt=?;";
    var stmt = try db.prepare(query);
    defer stmt.deinit();
    const count = (try stmt.one(i64, .{}, .{ .username_base64 = username_base64, .salt = salt })).?;

    if (count == 0) {
        return error.InvalidToken;
    }
}

pub fn isUsernameAvailable(username: []const u8) bool {
    const query = "SELECT COUNT(*) FROM Users WHERE username = ?;";

    var stmt = db.prepare(query) catch unreachable;
    defer stmt.deinit();

    return (stmt.one(i64, .{}, .{username}) catch unreachable).? == 0;
}
//
