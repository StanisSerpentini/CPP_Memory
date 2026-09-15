#include <memory_game.h>
#include <ftxui/ftxui.hpp>
#include <utility>

ftxui::Element createElementBoard(const mg::Board &board) {
    using namespace std;
    using namespace mg;
    using namespace ftxui;

    auto make_tile = [](Board::value_type::value_type tile) {
        string label = tile.isFlipped ? to_string(tile.value) : "";
        auto element_tile = text(label)
                            | center
                            | border
                            | size(WIDTH, EQUAL, 9)
                            | size(HEIGHT, EQUAL, 5);
        
        element_tile |= tile.isMatched ? color(Color::Green):color(Color::Blue);
        return element_tile;
    };
    auto make_row = [&](const Board::value_type &values) {
        vector<Element> tiles{};
        for (auto &value : values) {
            tiles.push_back(make_tile(value));
        }
        return hbox(tiles);
    };
    auto make_board = [&](const Board &board) {
        vector<Element> rows{};
        for (auto &row : board) {
            rows.push_back(make_row(row));
        }

        return vbox(rows) | center | border;
    };

    return make_board(board);
}

void runGame(uint size) {
    using namespace ftxui;

    mg::MemoryGame board{size};
    auto screen = ScreenInteractive::Fullscreen();
    auto renderer = Renderer([&] {
        return createElementBoard(board.getBoard());
    });
    auto component = CatchEvent(renderer, [&](Event event) {
        if (event == Event::Character('q')) {
            screen.ExitLoopClosure()();
            return true;
        }
        return false;
    });

    screen.Loop(component);
}
