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

        //resources
        sf::Font font;

        //Text
        sf::Text uiText;

        //Game logic
        bool endGame;
        unsigned points;
        int Fruitspawn;
        float FruitspawnTimer;
        float FruitspawnTimerMax;

        //private functions
        void initVariables();
        void initWindow();
        void initFruits();
        void initFonts();
        void initText();

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
        void updateText();
        void update();

        void renderFruits(sf::RenderTarget& target);
        void renderText(sf::RenderTarget& target);
        void render();
};