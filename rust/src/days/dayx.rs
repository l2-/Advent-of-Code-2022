pub fn print_day(day_number:i32) -> () {
    println!("Day {}", day_number);
}
pub fn input_path(day_number:i32) -> String {
    return format!("src/days/day{}.txt", day_number);
}