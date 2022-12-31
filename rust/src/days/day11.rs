use super::super::ulitity::*;
use super::super::dayx::*;

#[derive(Default)]
#[derive(Clone)]
struct Monkey {
    starting_items:Vec<i64>,
    op_var_1: i64,
    op_var_2: i64,
    op_p: bool,
    divisible_by: i64,
    target1: i64,
    target2: i64,
    inspected_count: i64,
}

fn build_monkey() -> Monkey {
    return Monkey {
        starting_items: vec![],
        op_var_1: -999,
        op_var_2: -999,
        op_p: false,
        divisible_by: 1,
        target1: 0,
        target2: 0,
        inspected_count: 0,
    };
}

pub fn day11() {
    print_day(11);
    let _lines:Vec<String> = read_lines(&*crate::dayx::input_path(11));
    let mut current_monkey_id = 0;
    let mut monkeys:Vec<Monkey> = vec![];
    for _line in _lines {
        let _str: &str = (&_line).trim();
        if _str.starts_with("Monkey") {
            current_monkey_id = match string_to_ints(_str).get(0) { Some(val) => *val, None => panic!("Wrong index?")};
            monkeys.push(build_monkey());
        }
        if _str.starts_with("S") {
            for i in string_to_ints(_str) {
                monkeys[current_monkey_id as usize].starting_items.push(i as i64);
            }
        }
        if _str.starts_with("O") {
            let splits = string_split(_str, " ");
            if splits[3] != "old" { monkeys[current_monkey_id as usize].op_var_1 = splits[3].parse::<i64>().unwrap(); }
            if splits[5] != "old" { monkeys[current_monkey_id as usize].op_var_2 = splits[5].parse::<i64>().unwrap(); }
            if splits[4] == "+" { monkeys[current_monkey_id as usize].op_p = true; }
        }
        if _str.starts_with("T") {
            monkeys[current_monkey_id as usize].divisible_by = string_to_ints(_str)[0] as i64;
        }
        if _str.starts_with("If true") {
            monkeys[current_monkey_id as usize].target1 = string_to_ints(_str)[0];
        }
        if _str.starts_with("If false") {
            monkeys[current_monkey_id as usize].target2 = string_to_ints(_str)[0];
        }
    }
    
    let mut _monkeys = monkeys.clone();
    for _ in 1..21 {
        for m_id in 0.._monkeys.len() {
            let m = _monkeys[m_id].clone();
            for worry in m.starting_items.clone() {
                let mut new_worry = worry;
                let mut var1 = m.op_var_1;
                let mut var2 = m.op_var_2;
                if var1 == -999 {var1 = new_worry;}
                if var2 == -999 {var2 = new_worry;}
                if m.op_p {new_worry = var1 + var2;}
                else {new_worry = var1 * var2;}
                new_worry = new_worry / 3;
                if new_worry % m.divisible_by == 0 { _monkeys[m.target1 as usize].starting_items.push(new_worry); }
                else { _monkeys[m.target2 as usize].starting_items.push(new_worry); }
                _monkeys[m_id].inspected_count+=1;
            }
            _monkeys[m_id].starting_items.clear();
        }
    }
    let mut counts = vec![];
    for m in _monkeys.iter() {
        counts.push(m.inspected_count);
    }
    counts.sort_by(|a, b| b.cmp(a));
    println!("part 1 sum: {}", counts[0] * counts[1]);

    let mut _monkeys = monkeys.clone();
    let mut lcm = 1;
    for m in _monkeys.iter() {
        lcm *= m.divisible_by;
    }
    for _ in 1..10001 {
        for m_id in 0.._monkeys.len() {
            let m = _monkeys[m_id].clone();
            for worry in m.starting_items.clone() {
                let mut new_worry = worry;
                let mut var1 = m.op_var_1;
                let mut var2 = m.op_var_2;
                if var1 == -999 {var1 = new_worry;}
                if var2 == -999 {var2 = new_worry;}
                if m.op_p {new_worry = var1 + var2;}
                else {new_worry = var1 * var2;}
                new_worry = new_worry % lcm;
                if new_worry % m.divisible_by == 0 { _monkeys[m.target1 as usize].starting_items.push(new_worry); }
                else { _monkeys[m.target2 as usize].starting_items.push(new_worry); }
                _monkeys[m_id].inspected_count+=1;
            }
            _monkeys[m_id].starting_items.clear();
        }
    }
    let mut counts = vec![];
    for m in _monkeys.iter() {
        counts.push(m.inspected_count);
    }
    counts.sort_by(|a, b| b.cmp(a));
    println!("part 2 sum: {}", counts[0] * counts[1]);
}