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

    void update();
    void render(sf::RenderTarget& target);
};

