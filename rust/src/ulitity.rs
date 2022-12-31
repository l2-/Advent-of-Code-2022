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

pub fn string_to_ints(_str:&str) -> Vec<i64> {
    let mut res = vec![];
    let re = Regex::new(r"-?\d+").unwrap();
    for m in re.find_iter(_str) {
        match m.as_str().parse::<i64>() {
            Ok(i) => res.push(i),
            Err(_) => (),
        }
    }
    return res;
}

// returns (a, b) in y = ax + b given 2 points
pub fn line_from_points(x1: i64, y1: i64, x2: i64, y2: i64) -> (i64, i64) {
    let a = (y2 - y1) / (x2 - x1);
    let b = y1 - x1 * a;
    return (a, b);
}

pub fn manhattan_distance(x1: i64, y1: i64, x2: i64, y2: i64) -> i64 {
    return (x1 - x2).abs() + (y1 - y2).abs();
    // return distance(x1, x2) + distance(y1, y2);
}

pub fn reduce_line_segments(_segments: &Vec<(i64, i64)>) -> Vec<(i64, i64)> {
    let mut segments = _segments.clone();
    segments.sort_by(|(a,_), (b,_)| a.partial_cmp(b).unwrap());
    let mut result:Vec<(i64, i64)> = vec![];
    if segments.len() < 1 { return result; }
    let mut start_segment = segments[0].0;
    let mut end_segment = segments[0].1;
    for (start, end) in segments.into_iter() {
        if start > end_segment {
            result.push((start_segment, end_segment));
            start_segment = start;
        }
        end_segment = std::cmp::max(end, end_segment);
    }
    result.push((start_segment, end_segment));
    return result;
}

pub fn intersect((a1, b1): (i64, i64), (a2, b2): (i64, i64), x_out: &mut i64, y_out: &mut i64) -> bool {
    if a1 - a2 == 0 { return false; }
    *x_out = (b2 - b1) / (a1 - a2);
    *y_out = a1 * (*x_out) + b1;
    return true;
} 

// inclusive
pub fn distance(a: i64, b: i64) -> i64 {
    return i64::abs(a - b) + 1;
}

pub fn in_bounds(val: i64, _min: i64, _max: i64) -> bool {
    return val >= _min && val <= _max;
}
pub fn in_bounds2d((x, y) : (i64, i64), ((min_x, min_y), (max_x, max_y)) : ((i64, i64), (i64, i64))) -> bool {
    return in_bounds(x, min_x, max_x) && in_bounds(y, min_y, max_y);
}