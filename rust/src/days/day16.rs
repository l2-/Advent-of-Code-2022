use std::mem;
use std::time::Instant;

use std::collections::*;
use std::cmp::*;

use super::super::ulitity::*;
use super::super::dayx::*;

// (valve id, flow rate, [connected valve id])
type ValveNode = (String, i64, Vec<String>);
// (current location id, visited bitmask, minute, players_left)
type State = (usize, usize, i64, i64);
// (distances, flow_mapping, vertex_count, non_zero_flow_vertex_count, initial_state)
// Cant declare refs in type aliases... causing me to have to useless copies of data within
type Constants = (Vec<i64>, HashMap<usize, i64>, usize, usize, State);
// type Memoisation = HashMap<State, i64>;
// For part 1 (1 player) Hashmap is much much faster than dense lookup table aka array
// For part 2 (2 players) Dense array is much faster most likely due to pre-allocating the memory and cheaper key calculation
type Memoisation = Vec<i64>;

const OPENING_COST: i64 = 1;
const MAX_LOCATIONS: i64 = 60;
const MAX_CYCLES: i64 = 31;
const MAX_PLAYERS: i64 = 2;
const MAX_VISITED_VALUE: i64 = 1 << 15;

fn max_flow(consts: &Constants, state: &State, memoisation: &mut Memoisation) -> i64 {
    let &(loc, visited, cycle, players_left) = state;
    let (distances, flow_map, keys, nz_keys, 
        (initial_loc, _, initial_cycle, _)) = consts;
    let keys = *keys; let nz_keys = *nz_keys;
    if cycle == 0 { 
        if players_left > 0 { return max_flow(consts, &(*initial_loc, visited, *initial_cycle, players_left - 1), memoisation); }
        return 0; 
    }

    let table_index = visited as i64 * MAX_LOCATIONS * MAX_CYCLES * MAX_PLAYERS
    + loc as i64 * MAX_CYCLES * MAX_PLAYERS
    + cycle * MAX_PLAYERS
    + players_left;
    if table_index >= 0 && memoisation[table_index as usize] >= 0 {
        return memoisation[table_index as usize];
    }
    // if memoisation.contains_key(state) {
    //     return memoisation[state];
    // }

    let mut max_pressure = 0;
    // see if we can move to next unopened valve
    for nzk in 0..nz_keys {
        if (visited & (1 << nzk)) == 0 {
            // the time we arrive there
            let travel_cost = distances[loc + nzk * keys];
            // the cycle when we open it
            let open_cycle = cycle - travel_cost - OPENING_COST;
            if open_cycle < 0 { continue; } // no point checking anymore
            let pressure_from_valve = flow_map[&nzk];
            let potential_pressure = open_cycle * pressure_from_valve;
            let new_visited = visited | (1 << nzk);
            max_pressure = max(max_pressure, potential_pressure + max_flow(consts, &(nzk, new_visited, open_cycle, players_left), memoisation));
        }
    }

    // at every turn consider letting the next player go
    if players_left > 0 {
        max_pressure = max(max_pressure, max_flow(consts, &(loc, visited, 0, players_left), memoisation));
    }

    if table_index >= 0 {
        memoisation[table_index as usize] = max_pressure;
    }
    // memoisation.insert(*state, max_pressure);
    return max_pressure;
}

pub fn day() {
    let day = 16;
    print_day(day);
    let lines = read_lines(&input_path(day));
    let _valves: Vec<ValveNode> = lines.iter().map(|l| l.split(' ').collect::<Vec<&str>>()).filter(|splits| splits.len() >= 10).map(|splits| {
        let v = String::from(splits[1]); let flowrate = string_to_ints(splits[4])[0]; let mut connected_valves: Vec<String> = Vec::new();
        for i in 9..splits.len() { let mut _v: &str = splits[i]; _v = _v.trim_end_matches(","); connected_valves.push(String::from(_v)); }
        return (v, flowrate, connected_valves);
    }).collect::<Vec<ValveNode>>();
    // use ints instead of strings
    // build floyd warshall map
    // run min-max in recursive dfs manner in dp style with memoisation

    let mut valves_mapping: HashMap<String, usize> = HashMap::new();
    // First add flow > 0 valves
    _valves.iter().filter(|(_, f, _)| *f > 0).enumerate().for_each(|(i, (v, _, _))| { valves_mapping.insert(v.to_string(), i); });
    // Second add 0 flow valves
    let non_zero_flow_count = valves_mapping.len();
    _valves.iter().filter(|(_, f, _)| *f == 0).enumerate().for_each(|(i, (v, _, _))| { valves_mapping.insert(v.to_string(), i + non_zero_flow_count); });
    let valves_mapping = valves_mapping;
    let flow_map: HashMap<usize, i64> = _valves.iter().map(|(v, f, _)| (valves_mapping[v], *f)).collect();
    let vertex_count = valves_mapping.len();

    let mut adjacent_mapping: HashMap<usize, Vec<usize>> = HashMap::new();
    _valves.iter().for_each(|(v,_,ns)| { adjacent_mapping.insert(valves_mapping[v], ns.iter().map(|n| valves_mapping[n]).collect()); }); 
    let adjacent_mapping = adjacent_mapping;
    let mut distance_matrix: Vec<i64> = vec![i64::MAX / 2 - 1; vertex_count * vertex_count];
    
    // floyd warshall
    for (&v1, ns) in adjacent_mapping.iter() {
        for &v2 in ns.iter() { distance_matrix[v1 + v2 * vertex_count] = 1; }
        distance_matrix[v1 + v1 * vertex_count] = 0;
    }
    (0..vertex_count).for_each(|k| { 
        (0..vertex_count).for_each(|i| { 
            (0..vertex_count).for_each(|j| { 
                let ij = i + j * vertex_count; let ik = i + k * vertex_count; let kj = k + j * vertex_count;
                if distance_matrix[ij] > distance_matrix[ik] + distance_matrix[kj] { distance_matrix[ij] = distance_matrix[ik] + distance_matrix[kj]; }
    }); }); });
    println!("Mapping cost:");
    print_single_digit_matrix(&distance_matrix, vertex_count, vertex_count);

    let start = Instant::now();
    // let mut memoisation: Memoisation = HashMap::new();
    let mut memoisation: Memoisation = vec![-1; (MAX_PLAYERS * MAX_LOCATIONS * MAX_VISITED_VALUE * MAX_CYCLES) as usize];
    println!("Memoisation table size {0}mb in {1}ms", (memoisation.len() * mem::size_of::<i64>()) as f64 / 1e6, start.elapsed().as_millis());
    let parts = [(1, (valves_mapping["AA"], 0usize, 30, 0)), (2, (valves_mapping["AA"], 0usize, 26, 1))];
    for (part, state@(_, _, minute, _)) in parts {
        let start = Instant::now();
        let consts: Constants = (distance_matrix.clone(), flow_map.clone(), vertex_count, non_zero_flow_count, state);
        let max_pressure = max_flow(&consts, &state, &mut memoisation);
        println!("Part {0} Max pressure after {1} is {2} in {3}ms", part, minute, max_pressure, start.elapsed().as_millis());
    }
}