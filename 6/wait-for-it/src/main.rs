use std::{fs, io::BufRead};

fn main() {
    let content = fs::read_to_string("./input.txt").unwrap();
    let mut lines = content.lines();
    let time = lines
        .next()
        .unwrap()
        .split(':')
        .skip(1)
        .next()
        .unwrap()
        .replace(" ", "")
        .parse::<u64>()
        .unwrap();

    let distance = lines
        .next()
        .unwrap()
        .split(':')
        .skip(1)
        .next()
        .unwrap()
        .replace(" ", "")
        .parse::<u64>()
        .unwrap();

    println!("Time: {}, Distance: {}", time, distance);
    let (start, end) = get_min_press_time(time as f64, distance as f64);
    let factor = (end - start) + 1;
    println!("Factor: {}", factor);
}

fn get_min_press_time(game_time: f64, to_beat_distance: f64) -> (u64, u64) {
    let mut x1 = -((game_time.powi(2) - 4.0 * to_beat_distance).sqrt() - game_time) / 2.0;
    let mut x2 = ((game_time.powi(2) - 4.0 * to_beat_distance).sqrt() + game_time) / 2.0;
    if x1 == x1.round() {
        x1 += 1.0
    }
    if x2 == x2.round() {
        x2 -= 1.0
    }
    (x1.ceil() as u64, x2.floor() as u64)
}
