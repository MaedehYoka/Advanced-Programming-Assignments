#include "drawGameBoard.hpp"
#include "constance.hpp"


void drawGameBoard(RenderWindow &window, vector<vector<char>> game_board)
{
    RectangleShape road(MAP_TILE_SIZE);
    road.setFillColor(Colors::GRAY);
    RectangleShape base(MAP_TILE_SIZE);
    base.setFillColor(Colors::LIGHT_GREEN);
    base.setOutlineColor(Colors::DARK_GREEN);
     base.setOutlineThickness(5.f);

    for (int i = 0; i < game_board.size(); i++)
    {
        for (int j = 0; j < game_board[i].size(); j++)
        {

            if (game_board[i][j] == '-')
            {
                base.setPosition({j * MAP_TILE_SIZE.x, i * MAP_TILE_SIZE.y});
                window.draw(base);
            }
            else
            {
                road.setPosition({j * MAP_TILE_SIZE.x, i * MAP_TILE_SIZE.y});
                window.draw(road);
            }
        }
    }
}

TowerPanelBounds drawTowersPanel(RenderWindow &window, const vector<vector<char>> &game_board , int money)
{
    RectangleShape sidebar;
    sidebar.setSize(Vector2f(WINDOW_SIZE.x, WINDOW_SIZE.y - game_board.size() * MAP_TILE_SIZE.y));
    sidebar.setFillColor(Color(Colors::PURPLE));
    sidebar.setPosition(0, (game_board.size() * MAP_TILE_SIZE.y));
    window.draw(sidebar);
    Texture arrowTexture, fireTexture, iceTexture;

    arrowTexture.loadFromFile(ARROW_TOWER_FILE);
    iceTexture.loadFromFile(ICE_TOWER_FILE);
    fireTexture.loadFromFile(BOMB_TOWER_FILE);
    Sprite arrowSprite(arrowTexture);
    Sprite fireSprite(fireTexture);
    Sprite iceSprite(iceTexture);
    FloatRect iceBounds = arrowSprite.getLocalBounds();
    arrowSprite.setOrigin(iceBounds.width / 2.f, iceBounds.height / 2.f);
    FloatRect arrowBounds = fireSprite.getLocalBounds();
    fireSprite.setOrigin(arrowBounds.width / 2.f, arrowBounds.height / 2.f);
    FloatRect fireBounds = iceSprite.getLocalBounds();
    iceSprite.setOrigin(fireBounds.width / 2.f, fireBounds.height / 2.f);
    float startX = 180;
    float Y = ((game_board.size() * MAP_TILE_SIZE.y) + (WINDOW_SIZE.y)) / 2;
    Text arrowPrice , firePrice , icePrice;
    Font font;
    font.loadFromFile(PANEL_FONT);
    arrowPrice.setFont(font);
    arrowPrice.setCharacterSize(24);
    arrowPrice.setString(to_string(ARROW_TOWER_COST));
    FloatRect textRect = arrowPrice.getLocalBounds();
    arrowPrice.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    arrowPrice.setPosition(startX, Y + 60);

    firePrice.setFont(font);
    firePrice.setCharacterSize(24);
    firePrice.setString(to_string(BOMB_TOWER_COST));
    FloatRect textRect2 = firePrice.getLocalBounds();
    firePrice.setOrigin(textRect2.left + textRect2.width / 2.0f, textRect2.top + textRect2.height / 2.0f);
    firePrice.setPosition(startX * 3, Y + 60);

    icePrice.setFont(font);
    icePrice.setCharacterSize(24);
    icePrice.setString(to_string(ICE_TOWER_COST));
    FloatRect textRect3 = icePrice.getLocalBounds();
    icePrice.setOrigin(textRect3.left + textRect3.width / 2.0f, textRect3.top + textRect3.height / 2.0f);
    icePrice.setPosition(startX * 5, Y + 60);
    arrowPrice.setFillColor(Color::Red);
    firePrice.setFillColor(Color::Red);
    icePrice.setFillColor(Color::Red);
    if(money >= ARROW_TOWER_COST)
        arrowPrice.setFillColor(Color::Green);
    if(money >= ICE_TOWER_COST)
        icePrice.setFillColor(Color::Green);
    if(money >= BOMB_TOWER_COST)
        firePrice.setFillColor(Color::Green);
    window.draw(arrowPrice);
    window.draw(firePrice);
    window.draw(icePrice);
    arrowSprite.setPosition(startX, Y);
    arrowSprite.scale({1.3, 1.3});
    fireSprite.setPosition(startX * 3, Y);
    fireSprite.scale({1.3, 1.3});
    iceSprite.setPosition(startX * 5, Y);
    iceSprite.scale({1.3, 1.3});
    window.draw(arrowSprite);
    window.draw(fireSprite);
    window.draw(iceSprite);
    TowerPanelBounds bounds;
    bounds.arrowBounds = arrowSprite.getGlobalBounds();
    bounds.fireBounds = fireSprite.getGlobalBounds();
    bounds.iceBounds = iceSprite.getGlobalBounds();
    return bounds;
    
}

void drawScorePanel(RenderWindow &window, const vector<vector<char>> &game_board , scoreSystem sys){
    RectangleShape scorePnael;
    Vector2f panelPos = Vector2f((game_board[0].size()*MAP_TILE_SIZE.x) , 0);
    scorePnael.setSize(Vector2f(WINDOW_SIZE.x - (game_board[0].size()*MAP_TILE_SIZE.x), game_board.size()*MAP_TILE_SIZE.y));
    scorePnael.setFillColor(Color(Colors::LIGHT_BLUE));
    scorePnael.setPosition(panelPos);
    window.draw(scorePnael);
    Font font;
    font.loadFromFile(PANEL_FONT);
    writeRound(window , sys.round , panelPos , font);
    writeMoney(window, sys.money , panelPos ,font);
    writelives(window, sys.lives , panelPos ,font);

}

void writeRound(RenderWindow &window, int roundNum , Vector2f panelPos , Font font){
    Text round , num;
    string numString = to_string(roundNum);
    round.setFont(font);
    num.setFont(font);
    round.setString("Round:");
    num.setString(numString);
    round.setCharacterSize(24);
    num.setCharacterSize(24);
    round.setColor(Color::Black);
    num.setColor(Color::Black);
    round.setPosition(panelPos.x + 10 , panelPos.y + 20);
    num.setPosition(panelPos.x+ 250, panelPos.y+20);
    window.draw(round);
    window.draw(num);
}

void writeMoney(RenderWindow &window, int money , Vector2f panelPos , Font font){
    Text moneyStr , moneyInt;
    string numString = to_string(money);
    moneyStr.setFont(font);
    moneyInt.setFont(font);
    moneyStr.setString("Money:");
    moneyInt.setString(numString);
    moneyStr.setCharacterSize(24);
    moneyInt.setCharacterSize(24);
    moneyStr.setColor(Color::Black);
    moneyInt.setColor(Color::Black);
    moneyStr.setPosition(panelPos.x + 10 , panelPos.y + 80);
    moneyInt.setPosition(panelPos.x+ 250, panelPos.y+ 80);
    window.draw(moneyStr);
    window.draw(moneyInt);
}

void writelives(RenderWindow &window, int lives , Vector2f panelPos , Font font){
    Text liveStr , liveInt;
    string liveString = to_string(lives);
    liveStr.setFont(font);
    liveInt.setFont(font);
    liveStr.setString("lives:");
    liveInt.setString(liveString);
    liveStr.setCharacterSize(24);
    liveInt.setCharacterSize(24);
    liveStr.setColor(Color::Black);
    liveInt.setColor(Color::Black);
    liveStr.setPosition(panelPos.x + 10 , panelPos.y + 140);
    liveInt.setPosition(panelPos.x+ 250, panelPos.y+ 140);
    window.draw(liveStr);
    window.draw(liveInt);
}

void drawWindow(RenderWindow &window , vector<vector<char>> &game_board ,scoreSystem &sys , TowerPanelBounds &panelBounds){
    drawGameBoard(window, game_board);
    panelBounds = drawTowersPanel(window, game_board ,sys.money);
    drawScorePanel(window , game_board, sys);
}