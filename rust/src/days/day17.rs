use std::time::Instant;

use std::collections::*;
use std::cmp::*;

use super::super::ulitity::*;
use super::super::dayx::*;

type Shape = Vec<Int2>;

fn translate_shape(x: i64, y: i64, shape: &Shape) -> Shape {
    return shape.iter().map(|(_x, _y)| (_x + x, _y + y)).collect();
}
fn shape_in_bounds(shape: &Shape, bounds: AABB2) -> bool {
    return !shape.iter().any(|p| !p.in_bounds(bounds));
}
fn shape_collides_with_previous(previous: &HashSet<Int2>, shape: &Shape) -> bool {
    return shape.iter().any(|p| previous.contains(p));
}
fn settle_shape(previous: &mut HashSet<Int2>, shape: &Shape) -> () {
    shape.iter().for_each(|p| {previous.insert(*p);});
}
fn max_y_from_shape(shape: &Shape) -> i64 {
    return shape.iter().max_by(|s1, s2| s1.1.cmp(&s2.1)).unwrap().1;
}
fn printcolumn(previous: &HashSet<Int2>) -> () {
    let min_x = previous.iter().min_by(|s1, s2| s1.0.cmp(&s2.0)).unwrap().0;
    let min_y = previous.iter().min_by(|s1, s2| s1.1.cmp(&s2.1)).unwrap().1;
    let max_x = previous.iter().max_by(|s1, s2| s1.0.cmp(&s2.0)).unwrap().0;
    let max_y = previous.iter().max_by(|s1, s2| s1.1.cmp(&s2.1)).unwrap().1;
    for y in (min_y..max_y + 1).rev() {
        let mut str = String::from("");
        for x in min_x..max_x + 1 {
            str += if previous.contains(&(x, y)) {"#"} else {"."};
        }
        println!("{0}", str);
    }
}

// number of rocks, number of jets, depth
type ColumnStateKey = (usize, usize, i64);
// rock1, top1, rock2, top2
type ColumnState = (i64, i64, i64, i64);

pub fn day() {
    let day = 17;
    print_day(17);
    let lines: Vec<String> = read_lines(&input_path(day));
    let jet_streams: Vec<i64> = (&lines[0]).chars().filter(|c| c == &'<' || c == &'>').map(|c| if c == '<' {return -1;} else {return 1;}).collect();
    let shapes: [Shape; 5] = [vec![(0,0), (1,0), (2,0), (3,0)], 
    vec![(1,0), (0,1), (1,1), (2,1), (1,2)], 
    vec![(0,0), (1,0), (2,0), (2,1), (2,2)],
    vec![(0,0), (0,1), (0,2), (0,3)],
    vec![(0,0), (1,0), (0,1), (1,1)]];
    let parts = [(1, 2022), (2, 1000000000000)];
    for (part, rock_count) in parts {
        let start = Instant::now();
        let mut column: HashSet<Int2> = HashSet::new();
        let mut column_states: HashMap<ColumnStateKey, ColumnState> = HashMap::new(); //top
    
        let mut top = 0;
        let bounds: AABB2 = ((0,0), (6, i64::MAX));
        let mut js_i = 0; //jetstream index
        let mut rock_i = 0;
        let mut top_offset = 0;
        loop {
            if rock_i >= rock_count { break; }
            let shape: &Shape = &shapes[rock_i % shapes.len()].clone();
            let start_pos = (2, top + 3);
            let mut depth = 0;
            let mut shape = translate_shape(start_pos.0, start_pos.1, &shape);
            // apply jet stream
            let jetstream = jet_streams[js_i % jet_streams.len()].clone(); js_i+=1;
            let new_shape = translate_shape(jetstream, 0, &shape);
            let collides = shape_collides_with_previous(&column, &new_shape);
            let in_bounds = shape_in_bounds(&new_shape, bounds);
            if in_bounds && !collides { shape = new_shape; }
            loop {
                // move down
                let new_shape = translate_shape(0, -1, &shape);
                // check if stuck -> settle else repeat
                let collides = shape_collides_with_previous(&column, &new_shape);
                let in_bounds = shape_in_bounds(&new_shape, bounds);
                if !in_bounds || collides { break; }
                else if shape_in_bounds(&new_shape, bounds) && !shape_collides_with_previous(&column, &new_shape) { shape = new_shape; depth +=1; }
                // apply jet stream
                let jetstream = jet_streams[js_i % jet_streams.len()].clone(); js_i+=1;
                let new_shape = translate_shape(jetstream, 0, &shape);
                let collides = shape_collides_with_previous(&column, &new_shape);
                let in_bounds = shape_in_bounds(&new_shape, bounds);
                if in_bounds && !collides { shape = new_shape; }
                // repeat
            }
            settle_shape(&mut column, &shape);
            top = std::cmp::max(top, max_y_from_shape(&shape) + 1);
            let key = (rock_i % shapes.len(), (js_i - 1) % jet_streams.len(), depth);
            if column_states.contains_key(&key) {
                column_states.insert(key, (column_states[&key].0, column_states[&key].1, rock_i as i64, top));
                let delta_top = top - column_states[&key].1;
                let delta_rock = rock_i as i64 - column_states[&key].0;
                // let predicted_top = top + delta_top;
                // let predicted_rock = rock_i as i64 + delta_rock;
                // println!("Found loop rock1 {0} top1 {1} rock2 {2} top2 {3} depth {4} predicted top {5} for rock {6}", 
                //     column_states[&key].0, column_states[&key].1, column_states[&key].2, column_states[&key].3, depth, predicted_top, predicted_rock);
                let multiplier = (rock_count - rock_i) as i64 / delta_rock;
                let value = multiplier * delta_top;
                let new_rock_i = rock_i + (multiplier * delta_rock) as usize;
                rock_i = new_rock_i;
                top_offset = top_offset + value;
            }
            else {
                column_states.insert(key, (rock_i as i64, top, -1, -1));
            }
            //println!("Rock {0} settled. Top at {1}", rock_i, top);
            rock_i += 1;
        }
        //printcolumn(&column);
        println!("Part {0}. Rock {1} settled. Top at {2}. Length of Data {3}. In {4}ms.", part, rock_count, top + top_offset, column.len(), start.elapsed().as_millis());
    }
}