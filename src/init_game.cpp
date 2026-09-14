#include <fmt/core.h>
#include <iostream>

using namespace std;

using fmt::println, fmt::print;

bool is_valid_size(string &s) {
    uint size;

    try {
        size = stoi(s);
    } catch (const invalid_argument & e) {
        println("Wrong argument. Please enter an even number.");
        return false;
    } catch (const out_of_range & e) {
        println("Number too large. Please enter a smaller number.");
        return false;
    }
    if (!(size % 2 == 0 && size < 9)) {
        println("Please enter an even number smaller than 10.");
        return false;
    }
    return true;
}

uint get_board_size() {
    uint size;
    bool good_size = false;
    string linebuff;

    println("Enter the this of the board:");
    while (!good_size) {
        getline(cin, linebuff);
        if (is_valid_size(linebuff)) {
            size = stoi(linebuff);
            good_size = true;
        }
    }
    return size;
}
