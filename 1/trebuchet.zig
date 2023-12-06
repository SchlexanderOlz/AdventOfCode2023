const std = @import("std");
const ArrayList = std.ArrayList;

const game1 = true;
const game2 = true;

pub fn main() !void {
    var gp = std.heap.GeneralPurposeAllocator(.{ .safety = true }){};
    defer _ = gp.deinit();
    const allocator = gp.allocator();

    var path_buffer: [std.fs.MAX_PATH_BYTES]u8 = undefined;
    const path = try std.fs.realpath("./input.txt", &path_buffer);

    const file = try std.fs.openFileAbsolute(path, .{});
    defer file.close();

    const buffer_size = 1000000;
    const file_buffer = try file.readToEndAlloc(allocator, buffer_size);
    defer allocator.free(file_buffer);

    var iter = std.mem.split(u8, file_buffer, "\n");

    var result: u32 = 0;

    while (iter.next()) |line| {
        var res = extract_line(line);
        result += res;
        std.debug.print("{}\n", .{res});
    }
    std.debug.print("{}", .{result});
}

fn extract_line(line: []const u8) u32 {
    if (line.len == 0) return 0;

    var first: usize = undefined;
    var sum: u32 = 0;

    var pos: usize = 0;
    while (pos < line.len) : (pos += 1) {
        var element = line[pos];
        if (element < 0x30 or element > 0x39) continue;
        first = pos;
        sum += (element - 0x30) * 10;
        break;
    }

    pos = line.len - 1;
    while (pos >= 0) : (pos -= 1) {
        var element = line[pos];
        if (element < 0x30 or element > 0x39) continue;
        if (pos == first) break;
        sum += element - 0x30;
        break;
    }
    if (sum % 10 == 0) sum += sum / 10;
    return sum;
}
