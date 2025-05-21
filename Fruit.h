#pragma once

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <functional>
//Sfml
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;

class Fruit
{
private:
    sf::RectangleShape fruit;

    void initFruit(sf::RenderTarget& window);
public:
    //constructors / deconstructors
    Fruit(sf::RenderWindow& window);
    virtual ~Fruit();

    //Functions
    const sf::RectangleShape fruitShape() const;
    void setRandomPosition(sf::RenderTarget& window, const std::vector<sf::RectangleShape>& snakeBody);
    void render(sf::RenderTarget& target);
};

