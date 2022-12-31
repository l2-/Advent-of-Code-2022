use super::super::ulitity::*;
use super::super::dayx::*;

use std::cmp::*;
use std::collections::HashSet;

type Coord = (i32, i32);
type LineSegment = (Coord, Coord);

enum Placement{
    DONE, SUNK, BLOCKED, DOWN, LEFT, RIGHT,
}

pub fn day() {
    let day = 14;
    print_day(day);
    let lines = read_lines(&input_path(day));

    let mut line_segments: Vec<LineSegment> = vec![];
    let mut width = 0;
    let mut height = 0;
    for line in lines.iter() {
        let ints = string_to_ints(line);
        let mut i = 2;
        let mut start = (ints[0], ints[1]);
        width = std::cmp::max(width, ints[0]);
        height = std::cmp::max(height, ints[1]);
        loop {
            if i >= ints.len() - 1 { break; }
            let next = (ints[i], ints[i + 1]);
            line_segments.push((start, next));
            start = next;
            width = std::cmp::max(width, ints[i]);
            height = std::cmp::max(height, ints[i + 1]);
            i += 2;
        }
    }

    let width = width * 2;
    let height = height + 2;
    let mut blocked_set: HashSet<i32> = HashSet::new();
    for &((x1, y1), (x2, y2)) in line_segments.iter() {
        for x in min(x1, x2)..max(x1, x2) + 1 {
            let index = x + y1 * width;
            blocked_set.insert(index);
        }
        for y in min(y1, y2)..max(y1, y2) + 1 {
            let index = x1 + y * width;
            blocked_set.insert(index);
        }
    }

    let is_stable = |set: &HashSet<i32>, x: i32, y: i32, width: i32, height: i32| -> Placement {
        if y >= height - 1 { return SUNK; }
        let index = x + y * width;
        use Placement::*;
        if set.contains(&index) { return DONE; }
        let below_index = x + (y + 1) * width;
        if !set.contains(&below_index) { return DOWN; }
        if x > 0 { //otherwise out of bounds and we just continue. shouldnt happen
            let left_index = (x - 1) + (y + 1) * width;
            if !set.contains(&left_index) { return LEFT; }
        }
        if x < width - 1 {
            let right_index = (x + 1) + (y + 1) * width;
            if !set.contains(&right_index) { return RIGHT; }
        }
        return BLOCKED;
    };

    let drop_sand = |set: &mut HashSet<i32>, x: &mut i32, y: &mut i32, width: i32, total_sand_dropped: &mut i32| -> () {
        let index = *x + *y * width;
        set.insert(index); 
        *x = 500; *y = 0; *total_sand_dropped += 1;
    };

    let mut sand_x = 500;
    let mut sand_y = 0;
    let mut total_sand_dropped = 0;
    let parts = vec![1, 2];
    for part in parts {
        loop {
            let stable = is_stable(&blocked_set, sand_x, sand_y, width, height);
            match stable {
                Placement::SUNK => { if part == 1 { break; } else { drop_sand(&mut blocked_set, &mut sand_x, &mut sand_y, width, &mut total_sand_dropped); }},
                Placement::DONE => { break; },
                Placement::BLOCKED => { drop_sand(&mut blocked_set, &mut sand_x, &mut sand_y, width, &mut total_sand_dropped); },
                Placement::DOWN => { sand_y += 1; },
                Placement::LEFT => { sand_x -= 1; sand_y += 1; },
                Placement::RIGHT => { sand_x += 1; sand_y += 1; },
            }
        }
        println!("Part {} {} sand dropped", part, total_sand_dropped);
    }
}