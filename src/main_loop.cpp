#include <memory_game.h>
#include <ftxui/ftxui.hpp>

ftxui::Element createElementBoard
(const mg::Board &board, mg::Coords &cursor) {
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
            element_tile |= tile.isMatched ? color(Color::Green1):color(Color::Blue1);
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

int getSelectAction
(mg::MemoryGame &game, mg::Coords &cursor, bool &has_selected) {
    auto tile = game.getBoard()[cursor.x][cursor.y];

    if (tile.isMatched || tile.isFlipped)
        return 0;
    if (has_selected == false) {
        has_selected = true;
        return 1;
    } else {
        has_selected = false;
        return 2;
    }
}

void runGame(uint size) {
    using namespace ftxui;
    using namespace mg;

    MemoryGame game{size};
    Coords cursor{0, 0};
    Coords selected{0, 0};
    Coords tmp{0, 0};
    bool has_selected = false;
    bool wait = false;
    auto screen = ScreenInteractive::Fullscreen();
    auto renderer = Renderer([&] {
        return createElementBoard(game.getBoard(), cursor);
    });

    auto process_cursor_control = [&](Event event) {
        if (event == Event::Character('z')) {
            cursor.x -= 1;
            cursor.x %= size;
        }
        if (event == Event::Character('s')) {
            cursor.x += 1;
            cursor.x %= size;
        }
        if (event == Event::Character('q')) {
            cursor.y -= 1;
            cursor.y %= size;
        }
        if (event == Event::Character('d')) {
            cursor.y += 1;
            cursor.y %= size;
        }
    };

    auto process_selection = [&](Event event) {
        if (event == Event::Character(' ')) {
            switch (getSelectAction(game, cursor, has_selected)) {
                case 1:
                    selected = cursor;
                    game.flipTile(selected);
                    break;
                case 2:
                    game.flipTile(cursor);
                    if (!game.matchTiles(selected, cursor)) {
                        tmp = cursor;
                        wait = true;
                    }
                default:
                    break;
            }
        }
    };

    auto component = CatchEvent(renderer, [&](Event event) {
        if (wait) {
            game.flipTile(selected);
            game.flipTile(tmp);
            wait = false;
        }
        process_cursor_control(event);
        process_selection(event);
        if (event == Event::Character('x') || game.isSolved()) {
            screen.ExitLoopClosure()();
            return true;
        }
        return false;
    });

    screen.Loop(component);
}
