#include "menuPage.hpp"
#include "constance.hpp"

void menuPage(RenderWindow& window, string ButtonFile, Color bg, string massege){
    Sprite butten;
    RectangleShape rect;
    Texture buttonTexture;
    rect.setSize((Vector2f)WINDOW_SIZE);
    rect.setFillColor(bg);
    buttonTexture.loadFromFile(ButtonFile);
    butten.setTexture(buttonTexture);
    butten.setScale({0.5,0.5});
    FloatRect bounds = butten.getLocalBounds();
    butten.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    butten.setPosition((Vector2f)(WINDOW_SIZE/2));

    Font font;
    font.loadFromFile (BESTIME_FONT_FILE);
    Text text;
    text.setString(massege);
    text.setFont(font);
    text.setOrigin(text.getGlobalBounds().width / 2.f, text.getGlobalBounds().height / 2.f);
    text.scale({1.2f,1.2f});
    text.setPosition({WINDOW_SIZE.x/2.f +20,WINDOW_SIZE.y/5.f});
    text.setColor(Colors::DARK_GRAY);
    while(window.isOpen()){
        window.draw(rect);
        window.draw(text);
        window.draw(butten);
        window.display();
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                    window.close();
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left){
                Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                if (butten.getGlobalBounds().contains(mousePos)) {
                    return;
                }
            }
        }
    }
}