#include <iostream>

void printHelp() {
    std::cout << "USAGE: CPP_Memory [OPTION]..." << std::endl
        << "OPTION:" << std::endl
        << "\t-h\tShow help message and quit." << std::endl
        << "\t-s N\tUse a board of size N directly instead of asking for the board size." << std::endl
        << "Rules:" << std::endl
        << "Select two cells to show their value." << std::endl
        << "If the two cells have the same value, they will remain face-up; "
        << "otherwise, they flip back to being face-down." << std::endl
        << "The goal is to find all the pairs." << std::endl
        << "Controls:" << std::endl
        << "Use z,q,s and d to move the cursor and space to select a cell." << std::endl
        << "Use x to quit the game." << std::endl;
}
