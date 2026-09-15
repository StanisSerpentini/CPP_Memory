#ifndef MEMORY_GAME_H_
    #define MEMORY_GAME_H_
    #include <ftxui/dom/elements.hpp>
    #include <random>

namespace mg {

struct Tile {
    size_t value;
    bool isMatched;
    bool isFlipped;
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
                row.push_back(Tile{ memory_list[index++], false, false });
            }
            board.push_back(row);
        }
    }

    const Board &getBoard() { return board; }

    const Tile &getTile(uint x, uint y) { return board.at(x).at(y); }

    void flipTile(uint x, uint y) {
        if (!board.at(x).at(y).isMatched)
            board.at(x).at(y).isFlipped = !board.at(x).at(y).isFlipped;
    }

    bool matchTiles(uint x1, uint y1, uint x2, uint y2) {
        if (board.at(x1).at(y1).value == board.at(x2).at(y2).value) {
            board.at(x1).at(y1).isMatched = true;
            board.at(x2).at(y2).isMatched = true;
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
