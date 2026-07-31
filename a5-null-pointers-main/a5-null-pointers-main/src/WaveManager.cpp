#include "include.hpp"
#include "waveConfigs.hpp"
#include "WaveManager.hpp"
#include "Ballon.hpp"

void WaveManager::startNextWave() {
    if (currentWave >= attackPlan.size()) return;
    if (!waveStarted){
        remainingBallons = attackPlan[currentWave].enemiesCount;
        bllonType = remainingBallons.begin()->first;
        waveStarted = true;
        nextSpawnTime = WAVE_LAUNCH_GAP_SECS;
    }
}

shared_ptr<Ballon> WaveManager::spawnBallon(const vector<pair<int,int>>& path,int pathIndex,bool mustMake){
    if (mustMake){
        shared_ptr<Ballon> newB=make_shared<Ballon>(Ballon(path,pathIndex));
        newB->setTexture(*textures[Ballons::NORMAL_STR]);
        newB->setType(Ballons::NORMAL_STR);
        return newB;
    }
    
    else if (waveStarted && spawnClock.getElapsedTime().asMilliseconds() >= nextSpawnTime) {
        shared_ptr<Ballon> newB=make_shared<Ballon>(Ballon(path));
        while (true){
            ballonType = getRandomType(Ballons::BALLONS_TYPE_COUNT);
            if (remainingBallons[ballonType]>0){
                remainingBallons[ballonType]--;
                newB->setTexture(*textures[ballonType]);
                newB->setType(ballonType);
                nextSpawnTime = getRandomDelay(attackPlan[currentWave].enemyLaunchGapMs);
                spawnClock.restart();   
                break;
            }
        }
        return newB;
    }
    return nullptr;
}

bool WaveManager::update() {
    if (!waveStarted) return false;
    if (currentWave >= attackPlan.size()) return false;

    for(auto b:remainingBallons){
        if (b.second != 0){
            return false;
        }
    }
    waveStarted=false;
    currentWave++;
    return true;
}

void WaveManager::addBallonType(string name,string filePath){
    auto tex = make_shared<Texture>();
    if (!(tex->loadFromFile(filePath))){
        cout << name ;
    }
    textures[name]=tex;
}

string WaveManager::getRandomType(int typeCount){
    uniform_int_distribution<> dist(1,typeCount);
    int chois = dist(rng);
    switch (chois)
    {
    case Ballons::NORMAL:
        return Ballons::NORMAL_STR;
    case Ballons::PREGNANT:
        return Ballons::PREGNANT_STR;
    default:
        break;
    }
}

int WaveManager::getRandomDelay(pair<int, int> range) {
    uniform_int_distribution<> dist(range.first, range.second);
    return dist(rng);
}