use std::collections::VecDeque;
use std::collections::vec_deque;
use std::io::Read;

use super::super::ulitity::*;
use super::super::dayx::*;

pub fn parse(_lines: Vec<String>) -> (Vec<i32>, usize, usize, (i32, i32), (i32, i32)) {
    let width = _lines[0].len();
    let height = _lines.len();
    let mut grid: Vec<i32> = vec![0; width * height];
    let mut start = (-1,-1);
    let mut end = (-1,-1);
    for y in 0..height {
        for x in 0..width {
            let _str:&str = &_lines[y];
            let c = _str.as_bytes()[x] as char;
            let mut elevation = c as i32 - 'a' as i32;
            if c == 'S' {
                start = (x as i32, y as i32);
                elevation = 0;
            }
            if c == 'E' {
                end = (x as i32, y as i32);
                elevation = 'z' as i32 - 'a' as i32;
            }
            grid[x + y * width] = elevation as i32;
        }
    }
    return (grid, width, height, start, end);
}

pub fn day() {
    let day = 12;
    print_day(day);
    let _lines:Vec<String> = read_lines(&*crate::dayx::input_path(day));
    let (grid, width, height, start, end) = parse(_lines);

    let dx = vec![-1, 1];
    let dy = vec![-1, 1];

    let parts = vec![1, 2];
    for &part in parts.iter() {
        let mut q:VecDeque<(i32, i32, i32)> = VecDeque::from([(end.0, end.1, 0)]);
        let mut seen:Vec<bool> = vec![false; grid.len()];
    
        let mut last = (-1,-1,0);
        while !q.is_empty() {
            let current = q.pop_front().unwrap();
            last = current;
            if (current.0, current.1) == (start.0, start.1) {
                break;
            }
            let x = current.0;
            let y = current.1;
            let round = current.2;
            let index = (x + y * width as i32) as usize;
            let old_elevation = grid[index];
            if part == 2 && old_elevation == 0 {
                break;
            }
            if seen[index] {
                continue;
            }
            seen[index] = true;
            let mut neighbours:Vec<(i32,i32,i32)> = vec![];
            for xo in dx.iter() {
                neighbours.push((x + xo, y, round + 1));
            }
            for yo in dy.iter() {
                neighbours.push((x, y + yo, round + 1));
            }
            for &(nx, ny, nr) in neighbours.iter() {
                if nx >= 0 && nx < width as i32 && ny >= 0 && ny < height as i32 {
                    let new_index = (nx + ny * width as i32) as usize;
                    let new_elevation = grid[new_index];
                    if new_elevation >= old_elevation - 1 {
                        q.push_back((nx, ny, nr));
                    }
                }
            }
        }
        println!("Found {} {} after {}", last.0, last.1, last.2);
    }
}