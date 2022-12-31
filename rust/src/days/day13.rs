use serde::Deserialize;
use std::cmp::Ordering;

use super::super::ulitity::*;
use super::super::dayx::*;

#[derive(Debug, Clone, Deserialize, Eq, PartialEq)]
#[serde(untagged)]
enum Packet {
    Term(u8),
    Nest(Vec<Packet>),
}
impl PartialOrd for Packet {
    fn partial_cmp(&self, rhs: &Self) -> Option<Ordering> {
        Some(self.cmp(rhs))
    }
}
impl Ord for Packet {
    fn cmp(&self, rhs: &Self) -> Ordering {
        use Packet::*;
        match (self, rhs) {
            (Term(l), Term(r)) => l.cmp(r),
            (Nest(l), Nest(r)) => l.cmp(r),
            (Term(l), Nest(r)) => vec![Term(*l)].cmp(r),
            (Nest(l), Term(r)) => l.cmp(&vec![Term(*r)]),
        }
    }
}

pub fn day() {
    let day = 13;
    print_day(day);
    let lines= read_lines(&input_path(day));
    let packets: Vec<Packet> = lines.iter()
        .filter(|l| !l.is_empty())
        .map(|l| serde_json::from_str::<Packet>(l).unwrap()).collect();
    let mut sum = 0;
    let mut i = 0;
    loop {
        if i > packets.len() - 2 {
            break;
        }
        let left = &packets[i];
        let right = &packets[i + 1];
        if left < right { sum += (i / 2) + 1; }
        i += 2;
    }
    println!("Sum part 1 {}", sum);

    let mut packets = packets.clone();
    let _2 = serde_json::from_str::<Packet>("[[2]]").unwrap();
    let _6 = serde_json::from_str::<Packet>("[[6]]").unwrap();
    packets.push(_2.clone());
    packets.push(_6.clone());
    packets.sort_unstable();
    let _2_i = packets.binary_search(&(_2.clone())).unwrap() + 1;
    let _6_i = packets.binary_search(&(_6.clone())).unwrap() + 1;
    println!("Sum part 2 {}", _2_i * _6_i);
}