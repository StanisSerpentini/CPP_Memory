#include <memory_game.h>
#include <fmt/core.h>
#include <iostream>

using namespace std;

using fmt::println, fmt::print;

uint get_board_size() {
    uint size;
    bool good_size = false;
    string linebuff;

    println("Enter the this of the board:");
    while (!good_size) {
        getline(cin, linebuff);
        try {
            size = stoi(linebuff);
        } catch (const invalid_argument & e) {
            println("Wrong argument. Please enter an even number.");
            continue;
        } catch (const out_of_range & e) {
            println("Number too large. Please enter a smaller number.");
            continue;
        }
        good_size = (size % 2 == 0 && size < 9) ? true : false;
        if (!good_size)
            println("Please enter an even number smaller than 10.");
    }
    return size;
}

mg::MemoryGame init_board() {
    uint board_size = get_board_size();
    mg::MemoryGame board{board_size};

    return board;
}
