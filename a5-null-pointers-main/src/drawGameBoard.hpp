#ifndef DRAW_GAME_BOARD_HPP
#define DRAW_GAME_BOARD_HPP
#include "include.hpp"
#include "WaveManager.hpp"
#include "score.hpp"

void drawGameBoard(sf::RenderWindow& window ,vector<vector<char>> game_board);
struct TowerPanelBounds {
    FloatRect arrowBounds;
    FloatRect fireBounds;
    FloatRect iceBounds;
};

void addMusic(Music&);
TowerPanelBounds drawTowersPanel(RenderWindow &window,const vector<vector<char>> &game_board , int money);
void drawScorePanel(RenderWindow &window, const vector<vector<char>> &game_board , scoreSystem sys);
void writeRound(RenderWindow &window, int roundNum , Vector2f panelPos , Font font);
void writeMoney(RenderWindow &window, int money , Vector2f panelPos , Font font);
void writelives(RenderWindow &window, int live , Vector2f panelPos , Font font);
void drawWindow(RenderWindow &window , vector<vector<char>> &game_board ,scoreSystem &sys , TowerPanelBounds &panelBounds);
#endif //DRAW_GAME_BOARD_HPP
