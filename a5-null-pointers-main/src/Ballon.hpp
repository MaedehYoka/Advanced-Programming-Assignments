#ifndef BALLON_HPP
#define BALLON_HPP
#include "constance.hpp"
#include "include.hpp"

class Ballon{
public:
    vector<pair<int,int>> path_;
    int pathIndex_;

    Ballon(const vector<pair<int,int>>& path,int pathIndex=0);
    bool update(float dt);
    void setTexture(Texture tex);
    void setType(string type);
    void draw(RenderWindow& window);
    string getType(){return type;}
    FloatRect getBounds(){return sprite_.getLocalBounds();}
    FloatRect getGlobalBounds(){return sprite_.getGlobalBounds();}
    bool isAlive(){return l;}
    void freezBallon(){freez=true;freezTimer.restart();}
    void deactivate(){l=false;}
    Vector2f getPosition();
    bool isFreez(){return freez;}

private:
    Texture texture_;
    Sprite sprite_;
    string type;
    bool freez=false;
    Clock freezTimer;
    bool l=true;
    float speed = 70.f;
};

#endif //BALLON_HPP