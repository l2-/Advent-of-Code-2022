use super::super::ulitity::*;

pub fn day10(file_path:&str) {
    let _lines = read_lines(file_path);
    
    let mut register_x: i32 = 1;
    let mut sum: i32 = 0;
    let cycle_registration: i32 = 40;
    let mut cycle: i32 = 1;
    let mut is_set = false;
    let width: i32 = cycle_registration;
    let height: i32 = 6;
    let mut pixels:Vec<bool> = vec![false; (width * height) as usize];
    let mut do_cycle = |cycle:i32, register_x:i32| { 
        if (cycle + 20) % cycle_registration == 0 || cycle == 20 {
            sum += cycle * register_x;
        }

        let pixel = (cycle - 1) % cycle_registration;
        let row = (cycle - 1) / cycle_registration;
        if register_x >= pixel - 1 && register_x <= pixel + 1 {
            let pixel_i = (pixel + row * width) as usize;
            if pixel_i < pixels.len() {
                pixels[pixel_i] = true;
            }
        }
    };
    for line in _lines {
        do_cycle(cycle, register_x);

        if line != "noop"
        {
            is_set = true;
        }
        cycle += 1;

        if is_set
        {
            is_set = false;

            do_cycle(cycle, register_x);

            let split: Vec<String> = string_split(&line, " ");
            let add_x = match split.get(1) {
                None => 0,
                Some(_s) => match _s.parse::<i32>() {
                    Ok(_i) => _i,
                    Err(_) => 0,
                },
            };
            register_x += add_x;
            
            cycle += 1;
        }
    }

    println!("part 1: sum {}", sum);
    println!("part 2:");
    for y in 0..height {
        for x in 0..width {
            let p = pixels[(x + y * width) as usize];
            if p { print!("#"); } else {print!("."); }
        }
        println!();
    }
}