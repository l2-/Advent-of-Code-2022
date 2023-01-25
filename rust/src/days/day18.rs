use super::super::ulitity::*;
use super::super::dayx::*;

use std::collections::*;

type SparseGrid = HashSet<Int3>;
const OFFSETS: [Int3; 6] = [(-1,0,0), (1,0,0), (0,-1,0), (0,1,0), (0,0,-1), (0,0,1)];

fn fill(cubes : &SparseGrid, set : &mut SparseGrid, pos : Int3, aabb : AABB3) -> i64 {
    let mut q: VecDeque<Int3> = VecDeque::new();
    let mut face_count = 0;
    if !cubes.contains(&pos) { q.push_back(pos); }
    while !q.is_empty() {
        let &pos@(x, y, z) = q.front().unwrap(); q.pop_front();
        if cubes.contains(&pos) { face_count+=1; }
        if !cubes.contains(&pos) && !set.contains(&pos) { 
            set.insert(pos);
            OFFSETS.iter().for_each(|(x_o, y_o, z_o)| {
                let pos = (x + x_o, y + y_o, z + z_o);
                if pos.in_bounds(aabb) { q.push_back(pos); }
            });
        }
    }
    return face_count;
}

pub fn day() {
    let day = 18;
    print_day(day);
    let lines: Vec<String> = read_lines(&input_path(day));
    let cubes: SparseGrid = lines.iter().map(|l| {let ints = string_to_ints(l); return (ints[0], ints[1], ints[2]); }).collect();
    let exposed_sum = cubes.iter().fold(0i64, |sum_cube, (x1,y1,z1)| 
        sum_cube + OFFSETS.iter().fold(0, |sum, &(x_o, y_o, z_o)| sum + (!cubes.contains(&(x1 - x_o, y1 - y_o, z1 - z_o)) as i64))
    );
    println!("Part 1: Answer {:?}", exposed_sum);
    println!("Performing flood fill...");
    let mut _min = (999,999,999);
    let mut _max = (0,0,0);
    cubes.iter().for_each(|c| { _min = c.element_wise_min(_min); _max = c.element_wise_max(_max); });
    let _min = _min.sub((1, 1, 1));
    let _max = _max.add((1, 1, 1));
    println!("min {:?} max {:?}", _min, _max);
    let mut flood: SparseGrid = HashSet::new();
    let face_count = fill(&cubes, &mut flood, (20,20,20), (_min, _max));
    println!("Flooded {:?} for {:?} cubes", flood.len(), cubes.len());
    println!("Part 2: Answer {:?}", face_count);
}