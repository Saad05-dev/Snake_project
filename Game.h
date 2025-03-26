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

// start of Game class

class Game
{
    private:
        //variables

        //Window
        sf::RenderWindow *window;
        sf::VideoMode videoMode;
        sf::Event ev;

        //Game objects
        std::vector<sf::RectangleShape> Fruits;
        sf::RectangleShape Fruit;

        //Game logic
        bool endGame;
        int Fruitspawn;
        float FruitspawnTimer;
        float FruitspawnTimerMax;

        //private functions
        void initVariables();
        void initWindow();
        void initFruits();

    public:

        //Constructor / Deconstructor
        Game();
        virtual ~Game();

        // Accessors
        const bool running() const;
        const bool getEndGame() const;

        //functions
        void spawnFruit();

        void pollEvents();
        void updateFruits();
        void update();

        void renderFruits(sf::RenderTarget& target);
        void render();
};