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

        //private functions
        void initVariables();
        void initWindow();

    public:

        //Constructor / Deconstructor
        Game();
        virtual ~Game();

        // Accessors
        const bool running() const;

        //functions
        void pollEvents();
        void update();
        void render();
};