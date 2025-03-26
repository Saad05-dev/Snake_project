#include "Game.h"

// Private functions

//intialize variables
void Game::initVariables()
{
    this->window = nullptr;

    //Game logic
    this->Fruitspawn = 1;
    this->endGame = false;
    this->FruitspawnTimerMax = 10.f;
    this->FruitspawnTimer = this->FruitspawnTimerMax;
}
//Set Game window
void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode,"Snake Game"
        ,sf::Style::Titlebar | sf::Style::Close );
    this->window->setFramerateLimit(60);
}
//initialize Fruit
void Game::initFruits()
{
    this->Fruit.setPosition(10.f,10.f);
    this->Fruit.setSize(sf::Vector2f(50.f,50.f));
    this->Fruit.setScale(sf::Vector2f(0.5f,0.5f));
    this->Fruit.setFillColor(sf::Color::Red);
}
//Ends the game
const bool Game::getEndGame() const
{
    return this->endGame;
}
//Spawn fruit
void Game::spawnFruit()
{
    /*
        return void
        Spawns Fruit 
        -Sets a randow position
    */
   this->Fruit.setPosition(
    static_cast<float>(rand() % static_cast<int>(this->window->getSize().x 
        - this->Fruit.getSize().x)),
    static_cast<float>(rand() % static_cast<int>(this->window->getSize().y
        - this->Fruit.getSize().y))
   );
   // Spawn Fruit
   this->Fruits.push_back(this->Fruit);
}
//Updates position of Fruit
void Game::updateFruits()
{
    /*
        return void
        updates the Fruit spawn 
    */
   //update spawn timer
   if(this->Fruits.size() < 1)
   {
    if(this->FruitspawnTimer >= this->FruitspawnTimerMax)
    {
        this->spawnFruit();
        this->FruitspawnTimer = 0.f;
    }
    else
    {
        this->FruitspawnTimer += 1.f;
    }
   }
}
void Game::renderFruits(sf::RenderTarget& target)
{
    //render fruit
    target.draw(this->Fruit);
}
// Constructors / Deconstructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initFruits();
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
    if(this->endGame == false)
    {
        this->updateFruits();
    }
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

   //Draw game objects
   this->renderFruits(*this->window);

   this->window->display();
}