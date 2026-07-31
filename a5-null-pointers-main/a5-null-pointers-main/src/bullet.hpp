#ifndef BULLET_HPP
#define BULLET_HPP
#include "include.hpp"
class Bullet
{

public:
    Bullet(Vector2f startPos, Vector2f targetPos, float spd = 300.f);

    void update(float deltaTime)
    {
        position += (direction * speed * deltaTime);
    }
    FloatRect getBounds() { return sprite.getLocalBounds(); }
    FloatRect getGlobalBounds() { return sprite.getGlobalBounds(); }
    Vector2f getPosition() const { return position; }
    virtual string getType() {};
    bool isActive() { return l; }
    void deactivate() { l = false; }
    virtual void draw(RenderWindow &window);
protected:
    Vector2f position;
    Vector2f direction;
    float speed;
    float damage = 10.f;
    Sprite sprite;
    bool l = true;
    Texture tex;
    CircleShape shape;
};

class NormalBullet : public Bullet
{
public:
    NormalBullet(Vector2f startPos, Vector2f targetPos);
    string getType() { return "normal_bullet"; }
};

class BombBullet : public Bullet
{
public:
    BombBullet(Vector2f startPos, Vector2f targetPos);
    string getType() { return "bomb_bullet"; }
};
class IceBullet : public Bullet
{
public:
    IceBullet(Vector2f startPos, Vector2f targetPos);
    string getType() { return "ice_bullet"; }
};
class BulletSystem
{
    std::vector<std::unique_ptr<Bullet>> bullets;

public:
    void addBullet(std::unique_ptr<Bullet> bullet)
    {
        bullets.push_back(std::move(bullet));
    }

    void update(float deltaTime)
    {
        for (auto &bullet : bullets)
        {
            bullet->update(deltaTime);
        }
    }

    void draw(RenderWindow &window)
    {
        for (auto &bullet : bullets)
        {
            bullet->draw(window);
        }
    }
};
#endif