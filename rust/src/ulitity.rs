use std::*;
use regex::Regex;

pub fn read_lines(file_path:&str) -> Vec<String> {
    let res = fs::read_to_string(file_path);
    return match res {
        Ok(_str) => _str.lines().map(|l| String::from(l)).collect::<Vec<_>>(),
        Err(_) => panic!("No file found for {}", file_path),
    }
}

pub fn string_split(_str:&str, pattern:&str) -> Vec<String> {
    return _str.split(pattern).map(|f| String::from(f)).collect::<Vec<_>>();
}

pub fn string_to_ints(_str:&str) -> Vec<i32> {
    let mut res = vec![];
    let re = Regex::new(r"-?\d+").unwrap();
    for m in re.find_iter(_str) {
        match m.as_str().parse::<i32>() {
            Ok(i) => res.push(i),
            Err(_) => (),
        }
    }
    return res;
}