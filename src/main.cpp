#include <memory_game.h>
#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
    uint size = 0;
    std::string str;
    int opt;

    while ((opt = getopt(argc, argv, "hs:")) != -1) {
        switch (opt) {
            case 'h':
                printHelp();
                return 0;
            case 's':
                str = optarg;
                if (!is_valid_size(str)) {
                    std::cerr << "-s: Wrong argument." << std::endl;
                    return 1;
                }
                size = std::stoi(str);
                break;
            default:
                std::cerr << "Unknown option." << std::endl;
                return 1;
        }
    }
    size = (size == 0) ? (get_board_size()) : (size);
    runGame(size);
}
