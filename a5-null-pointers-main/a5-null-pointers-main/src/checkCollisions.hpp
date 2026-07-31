#ifndef CHECK_COLLISIONS_HPP
#define CHECK_COLLISIONS_HPP
#include "include.hpp"
#include "WaveManager.hpp"
#include "bullet.hpp"
#include "Ballon.hpp"
#include "score.hpp"
    
void checkCollisions(scoreSystem& sys,vector<shared_ptr<Bullet>>& bullets, vector<shared_ptr<Ballon>>& ballons, vector<pair<int, int>> path, WaveManager &wm);
shared_ptr<Ballon> findTheBestPlaceForBomb(vector<shared_ptr<Ballon>> ballons , vector<shared_ptr<Ballon>> &dead);
void killPragnent(WaveManager& wm ,vector<shared_ptr<Ballon>>& toAdd , shared_ptr<Ballon> ballon, scoreSystem& sys, vector<pair<int, int>>& path);

#endif //CHECK_COLLISIONS_HPP