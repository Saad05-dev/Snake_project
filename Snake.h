#pragma once 

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <sstream>

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

    void updateInput();
    void SnakePos(float x = 0.f,float y = 0.f);
    void updateWindowBoundsCoollision(const sf::RenderTarget* target);
    void update(const sf::RenderTarget* target);
    void render(sf::RenderTarget* target);
};


