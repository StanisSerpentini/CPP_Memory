#ifndef MEMORY_GAME_H_
    #define MEMORY_GAME_H_
    #include <ftxui/dom/elements.hpp>
    #include <random>

namespace mg {

struct Tile {
    size_t value;
    bool isMatched;
    bool isFlipped;
    std::pair<uint, uint> coords;
};

using Board = std::vector<std::vector<Tile>>;

class MemoryGame {
public:
    MemoryGame(uint size) {
        if (size == 0)
            throw std::invalid_argument{"invalid size"};
        if (size % 2 != 0)
            throw std::invalid_argument{"board must be even to form pairs"};

        size_t area = size * size;
        std::vector<size_t> memory_list(area);
        for (size_t i = 0; i < area; i++)
            memory_list[i] = i / 2 + 1;

        static std::mt19937 engine(std::random_device{}());
        std::shuffle(memory_list.begin(), memory_list.end(), engine);

        size_t index = 0;
        for (uint i = 0; i < size; i++) {
            Board::value_type row;
            for (uint j = 0; j < size; j++) {
                row.push_back(Tile{ memory_list[index++], false, false, {i, j} });
            }
            board.push_back(row);
        }
    }

    const Board &getBoard() { return board; }

    const Tile &getTile(uint x, uint y) { return board.at(x).at(y); }

    void flipTile(std::pair<uint, uint> &a) {
        if (!board.at(a.first).at(a.second).isMatched)
            board.at(a.first).at(a.second).isFlipped = !board.at(a.first).at(a.second).isFlipped;
    }

    bool matchTiles(std::pair<uint, uint> &a, std::pair<uint, uint> &b) {
        if (board.at(a.first).at(a.second).value == board.at(b.first).at(b.second).value) {
            board.at(a.first).at(a.second).isMatched = true;
            board.at(b.first).at(b.second).isMatched = true;
            return true;
        }
        return false;
    }

    bool isSolved() {
        for (const auto& row : board) {
            for (const auto& tile : row) {
                if (!tile.isMatched)
                    return false;
            }
        }
        return true;
    }

private:
  Board board{};
};
} // namespace mg


// Initialization:

bool is_valid_size(std::string &s);
uint get_board_size();

// Game loop:

void runGame(uint size);

// Help:

void printHelp();

#endif
