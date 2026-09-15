#include <memory_game.h>
#include <ftxui/ftxui.hpp>

ftxui::Element createElementBoard
(const mg::Board &board, const mg::Coords &cursor) {
    using namespace std;
    using namespace mg;
    using namespace ftxui;

    auto make_tile = [cursor](Board::value_type::value_type tile) {
        string label = (tile.isFlipped || tile.isMatched) ? to_string(tile.value) : "";
        auto element_tile = text(label)
                            | center
                            | border
                            | size(WIDTH, EQUAL, 9)
                            | size(HEIGHT, EQUAL, 5);
        
        if (tile.coords.x == cursor.x && tile.coords.y == cursor.y)
            element_tile |= tile.isMatched ? color(Color::Magenta):color(Color::Purple);
        else
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
    using namespace mg;

    MemoryGame game{size};
    auto screen = ScreenInteractive::Fullscreen();
    auto renderer = Renderer([&] {
        return createElementBoard(game.getBoard(), game.getCursor());
    });

    auto component = CatchEvent(renderer, [&](Event event) {
        if (event == Event::Character('z'))
            game.moveUp();
        if (event == Event::Character('s'))
            game.moveDown();
        if (event == Event::Character('q'))
            game.moveLeft();
        if (event == Event::Character('d'))
            game.moveRight();
        if (event == Event::Character(' '))
            game.selectTile();
        if (event == Event::Character('x') || game.isSolved()) {
            screen.ExitLoopClosure()();
            return true;
        }
        return false;
    });

    screen.Loop(component);
}
