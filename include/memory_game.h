#ifndef MEMORY_GAME_H_
    #define MEMORY_GAME_H_
    #include <ftxui/dom/elements.hpp>
    #include <random>

namespace mg {

struct Coords {
    uint x;
    uint y;
};

struct Tile {
    size_t value;
    bool isMatched;
    bool isFlipped;
    Coords coords;
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

    void flipTile(Coords &a) {
        if (!board.at(a.x).at(a.y).isMatched)
            board.at(a.x).at(a.y).isFlipped = !board.at(a.x).at(a.y).isFlipped;
    }

    bool matchTiles(Coords &a, Coords &b) {
        if (board.at(a.x).at(a.y).value == board.at(b.x).at(b.y).value) {
            board.at(a.x).at(a.y).isMatched = true;
            board.at(b.x).at(b.y).isMatched = true;
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
