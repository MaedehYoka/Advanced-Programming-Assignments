#ifndef WAVE_CONFIGS_HPP_INCLUDE
#define WAVE_CONFIGS_HPP_INCLUDE
#include "include.hpp"

struct AttackWave {
    map<string, int> enemiesCount;
    pair<int, int> enemyLaunchGapMs;
};

const vector<AttackWave> ATTACKING_PLAN = {
    {{{"Normal", 5}}, {2000, 3000}},
    {{{"Normal", 10},{"Pregnant", 5}}, {500, 600}},
    {{{"Normal", 15},{"Pregnant", 10}}, {200, 500}},
    {{{"Normal", 20},{"Pregnant", 15}}, {200, 400}}
};

const int WAVE_LAUNCH_GAP_SECS = 10000;

#endif // WAVE_CONFIGS_HPP_INCLUDE  