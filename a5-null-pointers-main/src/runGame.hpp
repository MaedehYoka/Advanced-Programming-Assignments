#ifndef RUN_GAME_HPP
#define RUN_GAME_HPP

#include "include.hpp"
#include "Ballon.hpp"
#include "tower.hpp"
#include "score.hpp"

void runGame(RenderWindow& window, vector<vector<char>>& game_board);
void initialize(WaveManager& wm, scoreSystem& sys);
void checkTowerPlace(RectangleShape &indicator);
void update(vector<shared_ptr<Bullet>>& bullets, vector<shared_ptr<Ballon>>& ballons, scoreSystem &sys, float dt);
void drawInWindow(RenderWindow &window ,vector<shared_ptr<Ballon>> &ballons ,vector<shared_ptr<Bullet>>&bullets,vector<Tower *> placedTowers,float dt);
void manageWave(WaveManager &wm, vector<pair<int, int>> path, vector<shared_ptr<Ballon>> &ballons);

#endif //RUN_GAME_HPP