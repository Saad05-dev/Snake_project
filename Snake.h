#pragma once 
#include "Fruit.h"

// class Snake
class Snake
{
private:
    
    sf::RectangleShape snake;

    //Snake Movement speed
    float movementSpeed;

    void initVariables();
    void initShape();

public:
    Snake(float x = 0.f,float y = 0.f);
    ~Snake();

    const sf::RectangleShape& snakeShape() const;

    void updateInput();
    void SnakePos(float x = 0.f,float y = 0.f);
    void updateWindowBoundsCoollision(const sf::RenderTarget* target);
    void update(const sf::RenderTarget* target);
    void render(sf::RenderTarget* target);
};


