use regex::Regex;
use std::fs;

fn main() {
    let content = fs::read_to_string("input.txt").unwrap();
    let mut statements = content.split(':');

    let maping_pattern = Regex::new(r"[a-z]").unwrap();

    _ = statements.next();

    let mut seeds: Vec<u64> = statements
        .next()
        .unwrap()
        .split('\n')
        .next()
        .unwrap()
        .split(' ')
        .filter(|x| !maping_pattern.is_match(x) && x.len() > 0)
        .map(|x| x.parse().unwrap())
        .collect();

    for statement in statements {
        let mapings = statement
            .split('\n')
            .filter(|x| !maping_pattern.is_match(x) && x.len() > 0)
            .map(|x| {
                let mut split = x.split(' ');
                let mut parse_deez = || split.next().unwrap().parse().unwrap();
                Lable::new(parse_deez(), parse_deez(), parse_deez())
            })
            .collect();

        for (i, seed) in seeds.clone().iter().enumerate() {
            seeds[i] = map_value(*seed, &mapings);
        }
    }
    let distance = seeds.iter().min().unwrap();

    println!("{}", distance);
}

fn map_value(val: u64, lables: &Vec<Lable>) -> u64 {
    for lable in lables {
        if !(val >= lable.src && val <= lable.src + lable.range) {
            continue;
        }
        return (val as i64 + (lable.dest as i64 - lable.src as i64)) as u64;
    }
    return val;
}

struct Lable {
    src: u64,
    dest: u64,
    range: u64,
}

impl Lable {
    pub fn new(dest: u64, src: u64, range: u64) -> Self {
        Self { src, dest, range }
    }
}

enum MapTypes {
    SeedSoil,
    SoilFertilizer,
    FertilizerWater,
    WaterLight,
    LightTemperature,
    TemperatureHumidity,
    HumidityLocation,
}
