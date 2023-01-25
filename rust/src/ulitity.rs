use std::{*, os::windows};
use regex::Regex;
pub type Int2 = (i64, i64);
pub type Int3 = (i64, i64, i64);
pub type AABB2 = (Int2, Int2);
pub type AABB3 = (Int3, Int3);

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
pub fn line_from_points(x1: i64, y1: i64, x2: i64, y2: i64) -> Int2 {
    let a = (y2 - y1) / (x2 - x1);
    let b = y1 - x1 * a;
    return (a, b);
}

pub fn manhattan_distance(x1: i64, y1: i64, x2: i64, y2: i64) -> i64 {
    return (x1 - x2).abs() + (y1 - y2).abs();
    // return distance(x1, x2) + distance(y1, y2);
}

pub fn reduce_line_segments(_segments: &Vec<Int2>) -> Vec<Int2> {
    let mut segments = _segments.clone();
    segments.sort_by(|(a,_), (b,_)| a.partial_cmp(b).unwrap());
    let mut result:Vec<Int2> = vec![];
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

pub fn intersect((a1, b1): Int2, (a2, b2): Int2, x_out: &mut i64, y_out: &mut i64) -> bool {
    if a1 - a2 == 0 { return false; }
    *x_out = (b2 - b1) / (a1 - a2);
    *y_out = a1 * (*x_out) + b1;
    return true;
} 

// inclusive
pub fn distance(a: i64, b: i64) -> i64 {
    return i64::abs(a - b) + 1;
}

pub trait Bounds1d {
    fn in_bounds (&self, _min: i64, _max: i64) -> bool;
}
impl Bounds1d for i64 {
    fn in_bounds (&self, _min: i64, _max: i64) -> bool {
        return self >= &_min && self <= &_max;
    }
}
pub trait Bounds2d {
    fn in_bounds(&self, aabb : AABB2) -> bool;
}
impl Bounds2d for Int2 {
    fn in_bounds(&self, ((min_x, min_y), (max_x, max_y)) : AABB2) -> bool {
        return self.0.in_bounds(min_x, max_x) && self.1.in_bounds(min_y, max_y)
    }
}
pub trait Bounds3d {
    fn in_bounds(&self, aabb : AABB3) -> bool;
}
impl Bounds3d for Int3 {
    fn in_bounds(&self, (_min, _max) : AABB3) -> bool {
        return self.0.in_bounds(_min.0, _max.0) && self.1.in_bounds(_min.1, _max.1) && self.2.in_bounds(_min.2, _max.2);
    }
}
pub trait Maths3i64 {
    fn add(&self, other : Int3) -> Int3;
    fn sub(&self, other : Int3) -> Int3;
    fn element_wise_min(&self, other : Int3) -> Int3;
    fn element_wise_max(&self, other : Int3) -> Int3;
}
impl Maths3i64 for Int3 {
    fn add(&self, (x, y, z) : Int3) -> Int3 {
        (self.0 + x, self.1 + y, self.2 + z)
    }
    fn sub(&self, (x, y, z) : Int3) -> Int3 {
        (self.0 - x, self.1 - y, self.2 - z)
    }
    fn element_wise_min(&self, (x, y, z) : Int3) -> Int3 {
        return (self.0.min(x), self.1.min(y), self.2.min(z));
    }
    fn element_wise_max(&self, (x, y, z) : Int3) -> Int3 {
        return (self.0.max(x), self.1.max(y), self.2.max(z));
    }
}

pub fn print_single_digit_matrix(matrix: &Vec<i64>, width: usize, height: usize) -> () {
    for y in 0..height {
        let mut s: String = String::from("");
        for x in 0..width {
            let mut c = String::from("*");
            let d = matrix[x + y * width];
            if d.in_bounds(0, 9) { c = d.to_string(); }
            s += &c;
        }
        println!("{0}", s);
    }
}