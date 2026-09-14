#include <memory_game.h>
#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch (opt) {
            case 'h':
                printHelp();
                return 0;
            default:
                std::cerr << "Unknown option." << std::endl;
                return 1;
        }
    }
    runGame();
}
