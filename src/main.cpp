#include <ftxui/ftxui.hpp>

using namespace std;
using namespace ftxui;

int main() {
    auto screen = Screen::Create(Dimension::Full());
    string message = "Hello Wolrd";
    auto message_box = text(message) | center | border;

    Render(screen, message_box);
    screen.Print();
}
