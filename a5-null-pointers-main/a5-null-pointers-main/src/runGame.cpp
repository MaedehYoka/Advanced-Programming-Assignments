#include "runGame.hpp"
#include "menuPage.hpp"
#include "constance.hpp"
#include "readMapFile.hpp"
#include "drawGameBoard.hpp"
#include "getPath.hpp"
#include "waveConfigs.hpp"
#include "checkCollisions.hpp"
#include "WaveManager.hpp"


void checkTowerPlace(RectangleShape &indicator){
    indicator.setSize(Vector2f(MAP_TILE_SIZE.x, MAP_TILE_SIZE.y));
    indicator.setFillColor(Color::Transparent);
    indicator.setOutlineThickness(2.f);
    indicator.setOutlineColor(Color::Green);                   
    indicator.setOrigin(MAP_TILE_SIZE.x / 2, MAP_TILE_SIZE.y / 2);
}
    
void update(vector<shared_ptr<Bullet>>& bullets, vector<shared_ptr<Ballon>>& ballons, scoreSystem &sys, float dt){
    for (auto it = bullets.begin(); it != bullets.end();) {
        (*it)->update(dt);
        auto pos = (*it)->getPosition();
        if (pos.x < 0 || pos.x > WINDOW_SIZE.x || pos.y < 0 || pos.y > WINDOW_SIZE.y) {
            it = bullets.erase(it);
        } else {
            ++it;
        }
    }
    for (auto it = ballons.begin(); it != ballons.end();)
    {
        bool reachedEnd = (*it)->update(dt);
        if (reachedEnd)
        {
            sys.lives--;
            it = ballons.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void drawInWindow(RenderWindow &window ,vector<shared_ptr<Ballon>> &ballons ,vector<shared_ptr<Bullet>>&bullets,vector<Tower *> placedTowers,float dt){
    for (auto &ballon : ballons)
    {
        ballon->draw(window);
    }
    for (auto& bullet : bullets) {
        bullet->draw(window);
    }
    for (auto &tower : placedTowers)
    {
        tower->rotateTower(tower->findTheBestPlace(ballons , tower) , dt);
        tower->draw(window);
        tower->drawRange(window);
        tower->update(ballons,bullets);
    }
}

void manageWave(WaveManager &wm, vector<pair<int, int>> path, vector<shared_ptr<Ballon>> &ballons){
    wm.startNextWave();
    wm.update();
    auto new_b = wm.spawnBallon(path);
    if (new_b != nullptr)
        ballons.push_back(new_b);
}

void initialize(WaveManager& wm, scoreSystem& sys){
    wm.addBallonType(Ballons::NORMAL_STR,Ballons::NORMAL_FILE_PATH);
    wm.addBallonType(Ballons::PREGNANT_STR,Ballons::PREGNANT_FILE_PATH);
    initializeSystem(sys);
}

void addMusic(Music& music){
    music.openFromFile(MUSIC_FILE);
    music.setLoop(true);
    music.play();
}

void runGame(RenderWindow& window, vector<vector<char>>& game_board){
    vector<pair<int, int>> path = getPath(game_board);
    vector<shared_ptr<Ballon>> ballons;
    vector<Tower *> placedTowers;
    vector<shared_ptr<Bullet>> bullets;
    WaveManager wm(ATTACKING_PLAN);
    Clock clockBallon;
    Tower *selectedTower = nullptr;
    bool isTowerSelected = false;
    bool placingTower = true;
    TowerPanelBounds panelBounds;
    RectangleShape indicator;
    scoreSystem sys;
    Music music;
    addMusic(music);
    checkTowerPlace(indicator);
    initialize(wm,sys);
    
    while (window.isOpen())
    {
        
        float dt = clockBallon.restart().asSeconds();
        window.clear();
        TowerPanelBounds panelBounds;
        sys.round = wm.getWaveRound();
        drawWindow(window , game_board , sys , panelBounds);
        update(bullets,ballons,sys,dt);
        checkCollisions(sys,bullets, ballons,path,wm);
        if (selectedTower)
        {
            window.draw(indicator);
            selectedTower->draw(window);
        }
        manageWave(wm,path,ballons);
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left){
                if (!isTowerSelected){
                    selectedTower = createTowerIfClicked(window, panelBounds,sys);
                    if (selectedTower){
                        isTowerSelected = true;
                    }
                }
                else{
                    Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (selectedTower->isValidPosition(game_board, mousePos)){
                        placedTowers.push_back(selectedTower);
                        selectedTower->changeTowerPlaced();
                        selectedTower = nullptr;
                        isTowerSelected = false;
                    }
                }
            }
        }
        if (isTowerSelected && selectedTower)
            handleTowerMovement(window, selectedTower, game_board, indicator);
        
        drawInWindow(window, ballons,bullets,placedTowers , dt);
        if (sys.lives <= 0){
            menuPage(window,EXIT_BUTTON_FILE,Colors::LIGHT_RED,GAME_OVER);
            return ;
        }
        if (wm.getWaveRound()>=wm.numberOfWaves() && ballons.empty()){
           menuPage(window,EXIT_BUTTON_FILE,Colors::LIGHT_GREEN,WIN);
           return ;
        }
        window.display();
    }
}