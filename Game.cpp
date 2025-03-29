#include "Game.h"

// Private functions

//intialize variables
void Game::initVariables()
{
    this->window = nullptr;

    //Game logic
    this->Fruitspawn = 1;
    this->points = 0;
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
//Game text's fonts
void Game::initFonts()
{
    if(!this->font.loadFromFile("Fonts/PressStart2P-Regular.ttf"))
    {
        std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << "\n";
    }
}
void Game::initText()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}
//Ends the game
const bool Game::getEndGame() const
{
    return this->endGame;
}
//Updates position of Fruit
void Game::spawnFruits()
{
    //TIMER
    if(this->FruitspawnTimer < this->FruitspawnTimerMax)
        this->FruitspawnTimer += 1.f;
    else
    {
        if(this->fruits.size() < this->Fruitspawn)
        {
            this->fruits.push_back(Fruit(*this->window));
            this->FruitspawnTimer = 0.f;
        }
    }
}
//checks for collision between snake and fruit
void Game::updateCollision()
{
    for(int i = this->fruits.size() -1; i >= 0; i--)
    {
        if(this->snake.snakeShape().getGlobalBounds().intersects(
            this->fruits[i].fruitShape().getGlobalBounds()))
            {
                this->fruits.erase(this->fruits.begin() + i);
                this->points ++;
            }
    }
}
//Game uitext 
void Game::updateText()
{
    std::stringstream ss;

    ss << "Points: "<< this->points<<"\n";
    this->uiText.setString(ss.str());
}
void Game::renderText(sf::RenderTarget& target)
{
    target.draw(this->uiText);
}
//center Snake
void Game::SnakePos(){
    float X = window->getSize().x / 2.f;
    float Y = window->getSize().y / 2.f;

    snake.SnakePos(X,Y); //call's  snake function to update the position
}
// Constructors / Deconstructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
    this->SnakePos();
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
        this->spawnFruits();

        this->updateText();

        this->snake.update(this->window);
        this->updateCollision();
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

   this->renderText(*this->window);

   this->snake.render(this->window);
   for (auto i : this->fruits)
   {
        i.render(*this->window);
   }
   

   this->window->display();
}