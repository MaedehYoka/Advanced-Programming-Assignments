#include "bullet.hpp"
#include "constance.hpp"

Bullet::Bullet(sf::Vector2f startPos, sf::Vector2f targetPos, float spd ) : position(startPos), speed(spd)
{
    direction = targetPos - startPos;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
    {
        direction /= length;
    }
    shape.setFillColor(Color::Black);
}

void Bullet::draw(RenderWindow& window) {
    sprite.setPosition(position);
    window.draw(sprite);
}

NormalBullet::NormalBullet(Vector2f startPos, Vector2f targetPos) : Bullet(startPos, targetPos) {
    tex.loadFromFile(NORMAL_BULLET);
    sprite.setTexture(tex);
    sprite.scale({.3,.3});
}

IceBullet::IceBullet(Vector2f startPos, Vector2f targetPos) : Bullet(startPos, targetPos) {
    tex.loadFromFile(ICE_BULLET_FILE);
    sprite.setTexture(tex);
    sprite.scale({.3,.3});
}

BombBullet::BombBullet(Vector2f startPos, Vector2f targetPos) : Bullet(startPos, targetPos) {
    tex.loadFromFile(BOMB_BULLET_FILE);
    sprite.setTexture(tex);
    sprite.scale({.4,.4});
}
