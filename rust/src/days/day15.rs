use std::collections::*;

use crate::ulitity;

use super::super::ulitity::*;
use super::super::dayx::*;

pub fn day() {
    let day = 15;
    print_day(day);
    let lines = read_lines(&input_path(day));
    let mut beacons = HashMap::<i64, HashSet<i64>>::new();
    // sbs is sensor and beacon tuples
    let sbs: Vec<_> = lines.iter().filter(|l| string_to_ints(&l).len() == 4).map(|l| {
        let ints = string_to_ints(&l); return (ints[0], ints[1], ints[2], ints[3]);
    }).collect();
    for (_, _, x2, y2) in sbs.iter()  {
        if beacons.contains_key(y2) {
            beacons.get_mut(y2).unwrap().insert(*x2);
        }
        else {
            beacons.insert(*y2, HashSet::from([*x2]));
        }
    }

    let diamond_linesegments_around_points = |(x, y, d) : (i64, i64, i64)| -> ((i64, i64), (i64, i64), (i64, i64), (i64, i64)) {
        let (x_top, y_top) = (x, y - d);
        let (x_bottom, y_bottom) = (x, y + d);
        let (x_left, y_left) = (x - d, y);
        let (x_right, y_right) = (x + d, y);
        let left_bottom = line_from_points(x_left, y_left, x_bottom, y_bottom);
        let right_bottom = line_from_points(x_bottom, y_bottom, x_right, y_right);
        let left_top = line_from_points(x_left, y_left, x_top, y_top);
        let right_top = line_from_points(x_top, y_top, x_right, y_right);
        return (left_bottom, right_bottom, left_top, right_top);
    };

    let y: i64 = 2000000;
    // lines around the sensor in diamond shape
    let line_segments: Vec<_> = sbs.iter().map(|(x1, y1, x2, y2)| (*x1, *y1, manhattan_distance(*x1, *y1, *x2, *y2)))
    // if y within manhattan distance
    .filter(|(_sx, _sy, _d)| (*_sy - y).abs() <= *_d)
    .map(diamond_linesegments_around_points).collect();
    // Intersect the lines with y(0) = a(0) + b and store the shortest line segments. 
    // We filtered by distance before so the 2 closest (and thus middle) intersections are always valid.
    let line_segments = line_segments.iter().map(|&(line1, line2, line3, line4)| {
        let line = (0, y);
        let mut x_out:i64 = 0; let mut y_out:i64 = 0;
        let mut intersections = Vec::new();
        if intersect(line1, line, &mut x_out, &mut y_out) { intersections.push(x_out); }
        if intersect(line2, line, &mut x_out, &mut y_out) { intersections.push(x_out); }
        if intersect(line3, line, &mut x_out, &mut y_out) { intersections.push(x_out); }
        if intersect(line4, line, &mut x_out, &mut y_out) { intersections.push(x_out); }
        assert!(intersections.len() == 4);
        intersections.sort();
        return (intersections[1], intersections[2]);
    }).collect();

    let reduced_line_segements = reduce_line_segments(&line_segments);
    
    let number_of_beacons_on_y = if beacons.contains_key(&y) {beacons[&y].len()} else {0} as i64;
    let answer: i64 = reduced_line_segements.iter().map(|(start, end)| distance(*start, *end)).sum::<i64>() - number_of_beacons_on_y;
    println!("Answer for y={0} is {1}", y, answer);

    let sensors: Vec<_> = sbs.iter().map(|(x1, y1, x2, y2)| (*x1, *y1, manhattan_distance(*x1, *y1, *x2, *y2))).collect();
    let bounds: ((i64, i64), (i64, i64)) = ((0, 0),(4000000, 4000000));

    // a has positive gradient
    let mut acoeffs:HashSet<i64> = HashSet::new();
    // b has negative gradient
    let mut bcoeffs:HashSet<i64> = HashSet::new();
    for &(x, y, d) in sensors.iter() {
        let (l1, l2, l3, l4) = diamond_linesegments_around_points((x, y, d + 1));
        acoeffs.insert(l1.1);
        acoeffs.insert(l4.1);
        bcoeffs.insert(l2.1);
        bcoeffs.insert(l3.1);
    }

    let mut point = (0,0);
    let mut found = false;
    for &a in acoeffs.iter() {
        if found { break; }
        for &b in bcoeffs.iter() {
            if found { break; }

            let mut out = (0, 0);
            let l1= (1, a);
            let l2 = (-1, b);
            intersect(l1, l2, &mut out.0, &mut out.1);
            let x = out.0;
            let y = out.1;

            let mut valid = true;
            for &(_x, _y, d) in sensors.iter() {
                let distance = manhattan_distance(x, y, _x, _y);
                if distance <= d {
                    valid = false;
                }
            }
            if valid && (x, y).in_bounds(bounds)
            {
                point = (x, y);
                found = true;
            }
        }
    }
    
    let index = point.0 * bounds.1.0 + point.1;
    println!("Found at {0} {1} with index {2}", point.0, point.1, index);
}