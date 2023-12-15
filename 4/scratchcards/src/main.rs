use rayon::prelude::*;
use std::{fs, str::Lines};

fn main() {
    let file = fs::read_to_string("input.txt").unwrap();

    let mut sum = 0;

    let lines = file.lines();
    for line in lines.clone() {
        fn sum_lines(lines: &Lines<'_>, partial_line: &str) -> u32 {
            let mut split = partial_line.split(':');
            let card = split.next().unwrap();
            let game = split.next().unwrap();

            let id: usize = card.replace("Card", "").trim().parse().unwrap();

            let mut split = game.split('|');
            let winning = split
                .next()
                .unwrap()
                .split(' ')
                .filter(|e| e.len() > 0)
                .map(|e| e.parse::<u32>().unwrap());

            let values = split
                .next()
                .unwrap()
                .split(' ')
                .filter(|e| e.len() > 0)
                .map(|e| e.parse::<u32>().unwrap());

            let mut card_sum = 0;
            winning.for_each(|w| {
                if values.clone().any(|v| v == w) {
                    card_sum += 1;
                }
            });

            lines
                .clone()
                .skip(id)
                .take(card_sum)
                .fold(1, |acc, e| acc + sum_lines(lines, e))
        }
        sum += sum_lines(&lines, line);
    }
    println!("{}", sum);
}
