#ifndef TOWER_HPP
#define TOWER_HPP
#include "include.hpp"
#include "drawGameBoard.hpp"
#include "constance.hpp"
#include "Ballon.hpp"
#include "bullet.hpp"
#include "score.hpp"

class Tower{
public:
    Tower();
    void changeTowerPlaced() { isPlaced = true; }
    void drawRange(RenderWindow &window);
    bool isInRange(const Vector2f &position) const;
    void draw(RenderWindow &window);
    Vector2f getPosition() const;
    Sprite &getSprite() { return sprite; }
    void setPosition(Vector2f position);
    Vector2f getSize() const;
    void rotateTower(Vector2f target , float dt);
    bool isValidPosition(const vector<vector<char>> &gameBoard, Vector2f position) const;
    virtual Vector2f findTheBestPlace(const vector<shared_ptr<Ballon>> &ballons, const Tower *tower);
    virtual void update(const vector<shared_ptr<Ballon>>& ballons, vector<shared_ptr<Bullet>>& bullets);
    virtual void shoot(Vector2f targetPos,vector<shared_ptr<Bullet>>& bullets);

protected:
    Texture texture;
    Sprite sprite;
    bool isPlaced = false;
    float range=115;
    CircleShape rangeIndicator;
    Clock shootClock;
    float shootInterval = 1.5f;
};

class ArrowTower : public Tower{
public:
    ArrowTower(string texture_file)
    {
        texture.loadFromFile(texture_file);
        sprite.setTexture(texture);
        FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2, bounds.height / 2);
    }
};

class FireTower : public Tower{
public:
    FireTower(string texture_file)
    {
        texture.loadFromFile(texture_file);
        sprite.setTexture(texture);
        FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2, bounds.height / 2);
    }
    void shoot(Vector2f targetPos,vector<shared_ptr<Bullet>>& bullets) override {
        bullets.push_back(make_shared<BombBullet>(getPosition(), targetPos));
    }    
};

class IceTower : public Tower{
public:
    IceTower(string texture_file)
    {
        texture.loadFromFile(texture_file);
        sprite.setTexture(texture);
        FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2, bounds.height / 2);
    }
    void shoot(Vector2f targetPos,vector<shared_ptr<Bullet>>& bullets) override {
        bullets.push_back(make_shared<IceBullet>(getPosition(), targetPos));
    }
    Vector2f findTheBestPlace(const vector<shared_ptr<Ballon>> &ballons, const Tower *tower)override;
};

Tower *createTowerIfClicked(RenderWindow &window, TowerPanelBounds bounds,scoreSystem& sys);
void handleTowerMovement(RenderWindow &window, Tower *tower, vector<vector<char>> &gameBoard, RectangleShape &indicator);
void clampTowers(Vector2f &mousePos, vector<vector<char>> &gameBoard);
void putTowerInGridPos(Vector2f &mousePos, Tower *tower, RectangleShape &indicator);
#endif