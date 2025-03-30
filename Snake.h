#pragma once 
#include "Fruit.h"

//Enum represents snake movement
enum class Direction {UP, DOWN, LEFT, RIGHT};

// class Snake
class Snake
{
private:
    
    std::vector<sf::RectangleShape> snake; //holds the snake's whole segment

    //Snake Movement speed
    float movementSpeed;
    Direction direction;

    void initVariables();
    void initShape();

public:
    Snake(float x = 0.f,float y = 0.f);
    ~Snake();

    //accessors
    const std::vector<sf::RectangleShape>& getBody() const;

    //functions
    void updateInput();
    void SnakePos(float x = 0.f,float y = 0.f);
    void snakeShape();
    void updateWindowBoundsCoollision(const sf::RenderTarget* target);
    void update(const sf::RenderTarget* target);
    void grow();
    void move();
    bool snakeCollision();
    void render(sf::RenderTarget* target);
};


