#pragma once 
#include "Fruit.h"
#include <cmath> // For sqrt in calculating normalized vectors

// class Snake
class Snake
{
private:
    
    std::vector<sf::RectangleShape> snake; //holds the snake's whole segment

    //Snake Movement speed and direction
    float movementSpeed;
    sf::Vector2f direction;
    float segmentSize;     // Size of each snake segment
    float segmentSpacing;  // Space between segments (can be 0)

    void initVariables();
    void initShape();
    void initSnake();
public:
    Snake(float x = 0.f, float y = 0.f);
    ~Snake();

    //accessors
    const std::vector<sf::RectangleShape>& getBody() const;

    //functions
    void updateInput();
    void SnakePos(float x = 0.f, float y = 0.f);
    void snakeShape();
    void updateWindowBoundsCoollision(const sf::RenderTarget* target);
    void update(const sf::RenderTarget* target);
    void grow();
    void movement();
    bool snakeCollision();
    void render(sf::RenderTarget* target);
};