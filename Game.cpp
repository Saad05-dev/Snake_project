#include "Game.h"

// Private functions

//intialize variables
void Game::initVariables()
{
    this->window = nullptr;

    //Game logic
}
//Set Game window
void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode,"Snake Game",sf::Style::Titlebar | sf::Style::Close );
    this->window->setFramerateLimit(60);
}
// Constructors / Deconstructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
}
Game::~Game()
{
    delete this->window;
}
//Accessors
const bool Game::running() const
{
    return this->window->isOpen();
}
// Functions
void Game::pollEvents()
{
    //event polling
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if(this->ev.key.code == sf::Keyboard::Escape)
                this->window->close();
        default:
            break;
        }
    } 
}
void Game::update()
{
    /*
        return void
        updates variables
        updates text
        update fruit
    */
    this->pollEvents();
}
void Game::render()
{
    /*
        return void

        clear old frame render all objects
        display frame in window
        render the game objects
    */
   this->window->clear(sf::Color(141,161,89));

   this->window->display();
}