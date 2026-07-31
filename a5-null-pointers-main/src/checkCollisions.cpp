#include "checkCollisions.hpp"
#include "constance.hpp"

void checkCollisions(scoreSystem &sys, vector<shared_ptr<Bullet>> &bullets, vector<shared_ptr<Ballon>> &ballons, vector<pair<int, int>> path, WaveManager &wm)
{
    vector<shared_ptr<Ballon>> toAdd;
    for (auto &bullet : bullets)
    {
        for (auto &ballon : ballons)
        {
            if (bullet->getGlobalBounds().intersects(ballon->getGlobalBounds()))
            {
                if (bullet->getType() == ICE_BULLET)
                {
                    if (ballon->isAlive())
                        ballon->freezBallon();
                }
                else if (bullet->getType() == BOMB_BULLET)
                {
                    vector<shared_ptr<Ballon>> dead;
                    auto target = findTheBestPlaceForBomb(ballons, dead);
                    bool hitBalloonInList = false;
                    for (auto &b : dead)
                    {
                        if (b == ballon)
                        {
                            hitBalloonInList = true;
                            break;
                        }
                    }
                    if (!hitBalloonInList && ballon->isAlive())
                    {
                        dead.push_back(ballon);
                    }

                    if (!dead.empty())
                    {
                        for (auto &it : dead)
                        {
                            if (it->isAlive())
                            {
                                if (it->getType() == Ballons::PREGNANT_STR)
                                    killPragnent(wm,toAdd,ballon,sys,path);
                                else
                                {
                                    sys.money += NORMAL_BALLON_POINT;
                                    it->deactivate();
                                }
                            }
                        }
                    }
                }
                else
                {
                    if (ballon->isAlive())
                    {

                        if (ballon->getType() == Ballons::PREGNANT_STR)
                            killPragnent(wm,toAdd,ballon,sys,path);
                        else
                        {
                            sys.money += NORMAL_BALLON_POINT;
                            ballon->deactivate();
                        }
                    }
                }

                bullet->deactivate();
                break;
            }
        }
    }
    for (auto &b : toAdd)
    {
        ballons.push_back(b);
    }
    ballons.erase(
        remove_if(ballons.begin(), ballons.end(),
                  [](const shared_ptr<Ballon> &b)
                  { return !b->isAlive(); }),
        ballons.end());

    bullets.erase(
        remove_if(bullets.begin(), bullets.end(),
                  [](const shared_ptr<Bullet> &b)
                  { return !b->isActive(); }),
        bullets.end());
}

void killPragnent(WaveManager& wm ,vector<shared_ptr<Ballon>>& toAdd , shared_ptr<Ballon> ballon, scoreSystem& sys, vector<pair<int, int>>& path){
    toAdd.push_back(wm.spawnBallon(path, ballon->pathIndex_, true));
    toAdd.push_back(wm.spawnBallon(path, ballon->pathIndex_ - 1, true));
    ballon->deactivate();
    sys.money += PRAGNENET_BALLON_POINT;
}

shared_ptr<Ballon> findTheBestPlaceForBomb(vector<shared_ptr<Ballon>> ballons, vector<shared_ptr<Ballon>> &dead)
{
    shared_ptr<Ballon> bestTarget = nullptr;
    int maxClusterCount = 0;
    vector<shared_ptr<Ballon>> tmp;
    for (const auto &candidate : ballons)
    {
        if (!candidate->isAlive())
            continue;
        tmp.clear();
        int count = 0;
        Vector2f center = candidate->getPosition();
        tmp.push_back(candidate);
        for (const auto &other : ballons)
        {
            if (!other->isAlive())
                continue;
            if (other == candidate)
                continue;
            float dist = std::hypot(center.x - other->getPosition().x, center.y - other->getPosition().y);
            if (dist <= AOE_RADIUS)
            {
                count++;
                tmp.push_back(other);
            }
        }

        if (count > maxClusterCount)
        {
            maxClusterCount = count;
            bestTarget = candidate;
            dead = tmp;
        }
    }

    return bestTarget;
}