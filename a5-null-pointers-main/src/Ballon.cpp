#include "Ballon.hpp"
#include "constance.hpp"

Ballon::Ballon(const vector<pair<int,int>>& path,int pathIndex) {
    path_= path;
    sprite_.setPosition({(path_[pathIndex].second)*MAP_TILE_SIZE.y,(path_[pathIndex].first)*MAP_TILE_SIZE.x});
    pathIndex_=pathIndex;
}

bool Ballon::update(float dt) {
    if (pathIndex_ + 1 >= path_.size()) return true;
    if (freez && freezTimer.getElapsedTime().asSeconds()<5) return false;
    if (freez && freezTimer.getElapsedTime().asSeconds()>5) freez=false;
    Vector2f current = sprite_.getPosition();
    Vector2f target ={path_[pathIndex_ + 1].second*MAP_TILE_SIZE.y,path_[pathIndex_ + 1].first*MAP_TILE_SIZE.x};
    Vector2f direction = target - current;
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distance < 1.0f) {
        pathIndex_++;
    } else {
        direction /= distance;
        sprite_.setPosition(current+(speed*dt*direction));
    } 
    return false;
    
}

void Ballon::setTexture(Texture tex){
    texture_=tex;
    sprite_.setTexture(texture_);
    sprite_.setScale(Ballons::BALLON_SCALE);
}

void Ballon::setType(string type_){
    type=type_;
}

void Ballon::draw(RenderWindow& window) {
    window.draw(sprite_);
} 

Vector2f Ballon::getPosition(){
    return sprite_.getPosition();
}