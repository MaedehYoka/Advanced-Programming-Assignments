#ifndef WAVEMANAGER_HPP
#define WAVEMANAGER_HPP
#include "include.hpp"
#include "waveConfigs.hpp"
#include "Ballon.hpp"

class WaveManager {
    const vector<AttackWave>& attackPlan;
    int currentWave = 0;
    map<string, int> remainingBallons;
    map<string,shared_ptr<Texture>> textures;
    string ballonType;
    Clock spawnClock;
    int nextSpawnTime = 0;
    string bllonType;
    bool waveStarted = false;
    mt19937 rng;

public:
    WaveManager(const vector<AttackWave>& plan)
        : attackPlan(plan), rng(random_device{}()) {}

    void startNextWave();
    int getWaveRound(){return currentWave+1;}
    int numberOfWaves(){return attackPlan.size();}
    shared_ptr<Ballon> spawnBallon(const vector<pair<int,int>>& path, int pathIndex=0,bool mustMake=false);
    bool update();
    void addBallonType(string name,string filePath);

private:
    int getRandomDelay(pair<int, int> range);
    string getRandomType(int typeCount);
};
#endif