use std::fs;

fn main() {
    let file = fs::read_to_string("./input.txt").unwrap();
    let lines = file.lines();

    let sequences: Vec<Vec<i32>> = lines
        .map(|line| line.split(' ').map(|elem| elem.parse().unwrap()).collect())
        .collect();

    let mut sum = 0;
    for sequence in sequences {
        sum += sequence.last().unwrap() + parse_sequence(&sequence);
    }
    println!("Sum: {}", sum);
}

fn parse_sequence(sequence: &Vec<i32>) -> i32 {
    let diffs: Vec<i32> = sequence.windows(2).map(|vals| vals[1] - vals[0]).collect();

    if diffs.iter().all(|elem| *elem == 0) {
        return 0;
    }

    return *diffs.last().unwrap() + parse_sequence(&diffs);
}
