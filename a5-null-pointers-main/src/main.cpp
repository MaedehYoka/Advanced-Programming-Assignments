#include "include.hpp"
#include "constance.hpp"
#include "readMapFile.hpp"
#include "menuPage.hpp"
#include "runGame.hpp"

int main()
{
    RenderWindow window(VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "SFML works!");
    window.setFramerateLimit(60);
    menuPage(window,START_BUTTON_FILE,Colors::LIGHT_GREEN,NAMES);

    vector<vector<char>> game_board = readMapFile(MAP_FILE);

    runGame(window,game_board);

    return 0;
}
