#include "tower.hpp"

Tower::Tower()
{
    rangeIndicator.setRadius(range);
    rangeIndicator.setFillColor(Color(255, 255, 255, 40));
    rangeIndicator.setOutlineColor(Color::White);
    rangeIndicator.setOutlineThickness(2.f);
    rangeIndicator.setOrigin(range, range);
}

Tower *createTowerIfClicked(RenderWindow &window, TowerPanelBounds bounds, scoreSystem &sys)
{
    Vector2i mousePos = Mouse::getPosition(window);
    if (bounds.arrowBounds.contains(mousePos.x, mousePos.y) && sys.money >= ARROW_TOWER_COST)
    {
        sys.money -= ARROW_TOWER_COST;
        return new ArrowTower(ARROW_TOWER_FILE);
    }
    else if (bounds.fireBounds.contains(mousePos.x, mousePos.y) && sys.money >= BOMB_TOWER_COST)
    {
        sys.money -= BOMB_TOWER_COST;
        return new FireTower(BOMB_TOWER_FILE);
    }
    else if (bounds.iceBounds.contains(mousePos.x, mousePos.y) && sys.money >= ICE_TOWER_COST)
    {
        sys.money -= ICE_TOWER_COST;
        return new IceTower(ICE_TOWER_FILE);
    }
    return nullptr;
}

void handleTowerMovement(RenderWindow &window, Tower *tower, vector<vector<char>> &gameBoard, RectangleShape &indicator)
{
    if (tower != nullptr)
    {
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        clampTowers(mousePos, gameBoard);
        putTowerInGridPos(mousePos, tower, indicator);
        if (tower->isValidPosition(gameBoard, tower->getPosition()))
        {
            indicator.setFillColor(Color(0, 255, 0, 150));
        }
        else
        {
            indicator.setFillColor(Color(255, 0, 0, 150));
        }
    }
}

void clampTowers(Vector2f &mousePos, vector<vector<char>> &gameBoard)
{
    float maxX = gameBoard[0].size() * MAP_TILE_SIZE.x;
    float maxY = gameBoard.size() * MAP_TILE_SIZE.y;
    mousePos.x = clamp(mousePos.x, 0.f, maxX - 1);
    mousePos.y = clamp(mousePos.y, 0.f, maxY - 1);
}

void putTowerInGridPos(Vector2f &mousePos, Tower *tower, RectangleShape &indicator)
{
    int gridX = static_cast<int>(mousePos.x / MAP_TILE_SIZE.x);
    int gridY = static_cast<int>(mousePos.y / MAP_TILE_SIZE.y);
    Vector2f gridPos(
        gridX * MAP_TILE_SIZE.x + MAP_TILE_SIZE.x / 2,
        gridY * MAP_TILE_SIZE.y + MAP_TILE_SIZE.y / 2);
    tower->setPosition(gridPos);
    indicator.setPosition(gridPos);
}

void Tower::shoot(Vector2f targetPos,vector<shared_ptr<Bullet>>& bullets){
    bullets.push_back(make_shared<NormalBullet>(getPosition(), targetPos));
}

void Tower::drawRange(RenderWindow &window)
{
    if (isPlaced)
    {
        window.draw(rangeIndicator);
    }
}

void Tower::update(const vector<shared_ptr<Ballon>>& ballons, vector<shared_ptr<Bullet>>& bullets) {
    if (!isPlaced) return;
    
    Vector2f targetPos = findTheBestPlace(ballons, this);
    if (targetPos.x >= 0 && targetPos.y >= 0) {  
        if (shootClock.getElapsedTime().asSeconds() >= shootInterval) {
            shoot(targetPos, bullets);
            shootClock.restart();
        }
    }
}

bool Tower::isInRange(const Vector2f &position) const
{
    float dx = sprite.getPosition().x - position.x;
    float dy = sprite.getPosition().y - position.y;
    float distanceSquared = dx * dx + dy * dy;
    return distanceSquared <= (range * range);
}

void Tower::draw(RenderWindow &window)
{
    window.draw(sprite);
}

Vector2f Tower::getPosition() const
{
    return sprite.getPosition();
}

void Tower::setPosition(Vector2f position)
{
    sprite.setPosition(position);
    rangeIndicator.setPosition(position);
}

Vector2f Tower::getSize() const
{
    return Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height);
}

bool Tower::isValidPosition(const vector<vector<char>> &gameBoard, Vector2f position) const
{
    int gridX = static_cast<int>(position.x / MAP_TILE_SIZE.x);
    int gridY = static_cast<int>(position.y / MAP_TILE_SIZE.y);

    if (gridX < 0 || gridY < 0 ||
        gridY >= gameBoard.size() ||
        gridX >= gameBoard[0].size())
    {
        return false;
    }
    return gameBoard[gridY][gridX] == '-';
}

Vector2f Tower::findTheBestPlace(const vector<shared_ptr<Ballon>> &ballons, const Tower *tower)
{
    shared_ptr<Ballon> closestballon = nullptr;
    float minDistance = numeric_limits<float>::max();
    Vector2f towerPos = tower->getPosition();

    for (const auto &ballon : ballons)
    {
        
        Vector2f ballonPos = ballon->getPosition();
        if (tower->isInRange(ballonPos))
        {
            float dx = ballonPos.x - towerPos.x;
            float dy = ballonPos.y - towerPos.y;
            float distance = sqrt(dx * dx + dy * dy);

            if (distance < minDistance)
            {
                minDistance = distance;
                closestballon = ballon;
            }
        }
    }
    if (closestballon)
    {
        return closestballon->getPosition();
    }
    return Vector2f(-1, -1);
}

Vector2f IceTower::findTheBestPlace(const vector<shared_ptr<Ballon>> &ballons, const Tower *tower)
{
    shared_ptr<Ballon> closestBallon = nullptr;
    float minDistance = numeric_limits<float>::max();
    Vector2f towerPos = tower->getPosition();

    for (const auto &ballon : ballons)
    {
        
        Vector2f ballonPos = ballon->getPosition();
        if (tower->isInRange(ballonPos) && !ballon->isFreez())
        {
            float dx = ballonPos.x - towerPos.x;
            float dy = ballonPos.y - towerPos.y;
            float distance = sqrt(dx * dx + dy * dy);

            if (distance < minDistance)
            {
                minDistance = distance;
                closestBallon = ballon;
            }
        }
    }
    if (closestBallon)
    {
        return closestBallon->getPosition();
    }
    return Vector2f(-1, -1);
}

void Tower::rotateTower(Vector2f target, float dt)
{
    float currentAngle = sprite.getRotation();
    float dx = target.x - sprite.getPosition().x;
    float dy = target.y - sprite.getPosition().y;
    float targetAngle = atan2(dy, dx) * 180 / M_PI + 70;
    if (targetAngle < 0) targetAngle += 360;
    if (currentAngle < 0) currentAngle += 360;
    float deltaAngle = targetAngle - currentAngle;
    if (deltaAngle > 180)
        deltaAngle -= 360;
    else if (deltaAngle < -180)
        deltaAngle += 360;
    float rotationSpeed = 500.0f;

    float maxRotationThisFrame = rotationSpeed * dt;

    if (abs(deltaAngle) < maxRotationThisFrame)
        sprite.setRotation(targetAngle);
    else
        sprite.setRotation(currentAngle + (deltaAngle > 0 ? maxRotationThisFrame : -maxRotationThisFrame));
}