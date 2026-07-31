#ifndef SCORE_HPP
#define SCORE_HPP
#include "include.hpp"

struct scoreSystem{
    int round;
    int money;
    int lives;
};

void initializeSystem(scoreSystem &sys);
#endif //SCORE_HPP