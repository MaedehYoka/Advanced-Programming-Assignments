#ifndef CONSTANCE_HPP
#define CONSTANCE_HPP
#include "include.hpp"

const string MAP_FILE = "map.txt";
const string MUSIC_FILE = "assets/music/ActionTrailer.wav";
const string START_BUTTON_FILE = "assets/sprites/start-button_5115424.png";
const string EXIT_BUTTON_FILE = "assets/sprites/exit.png";
const string ARROW_TOWER_FILE = "assets/sprites/normal_shooter.png";
const string ICE_TOWER_FILE = "assets/sprites/ice_shooter.png";
const string BOMB_TOWER_FILE = "assets/sprites/cannon.png";
const string NORMAL_BULLET = "assets/sprites/normal_bullet.png";
const string ICE_BULLET_FILE = "assets/sprites/ice_bullet.png";
const string ICE_BULLET = "ice_bullet";
const string BOMB_BULLET_FILE = "assets/sprites/bombb.png";
const string BOMB_BULLET = "bomb_bullet";
const string NAMES = "fereshte kambarani and maede yosefi";
const string GAME_OVER = "GAME OVER!  ";
const string WIN = "YOU WON!";
const string BESTIME_FONT_FILE = "assets/fonts/Bestime.ttf";
const string PANEL_FONT = "assets/fonts/DreamLife-V1.0.0_by_MaxiGamer.ttf";
const Vector2f MAP_TILE_SIZE(70.f,70.f);
const Vector2i WINDOW_SIZE(1080 , 720);
const float AOE_RADIUS = 70.f;

const int NORMAL_BALLON_POINT = 40;
const int PRAGNENET_BALLON_POINT = 60;
const int ARROW_TOWER_COST = 400;
const int ICE_TOWER_COST = 550;
const int BOMB_TOWER_COST = 900;

namespace Colors
{
    const Color DARK_GREEN (114, 209, 94);
    const Color GRAY (128, 128, 128); 
    const Color DARK_GRAY(30, 30, 30);
    const Color LIGHT_GREEN(172, 246, 148); 
    const Color LIGHT_BLUE(137, 240, 225);
    const Color LIGHT_RED (220, 130, 160);
    const Color PURPLE(169, 137, 240);
}

namespace Ballons
{
    const int BALLONS_TYPE_COUNT = 2;
    const int NORMAL = 1;
    const int PREGNANT = 2;
    const string NORMAL_STR = "Normal";
    const string NORMAL_FILE_PATH = "assets/sprites/normal.png";
    const string PREGNANT_STR = "Pregnant";
    const string PREGNANT_FILE_PATH = "assets/sprites/bardar.png";
    const Vector2f BALLON_SCALE = {0.25,0.25};
}
#endif //CONSTANCE_HPP