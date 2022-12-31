use std::*;
use super::super::dayx::*;

pub fn day1() {
    print_day(1);
    let contents = fs::read_to_string(input_path(1)).expect("Should have been able to read the file");
    let lines = contents.lines();
    let mut max_sum = 0;
    let mut sum = 0;
    for line in lines.clone() {
        if line == "" {
            max_sum = cmp::max(sum, max_sum);
            sum = 0;
        }
        else {
            sum += line.parse::<i32>().unwrap();
        }
    }
    println!("part 1 {}", max_sum);

    let mut calories: Vec<i32> = vec![0, 0, 0];
    let mut sum = 0;
    for line in lines.clone() {
        if line == "" {
            let mut smallest_i = 999;
            let mut smallest_sum = sum;
            for i in 0..calories.len() {
                if smallest_sum >= calories[i] {
                    smallest_i = i;
                    smallest_sum = calories[i];
                }
            }
            if smallest_i < calories.len() {
                calories[smallest_i] = sum;
            }
            sum = 0;
        }
        else {
            sum += line.parse::<i32>().unwrap();
        }
    }
    let mut sum = 0;
    for cal in calories {
        sum += cal;
    }
    println!("part 2: calories {}", sum);
}