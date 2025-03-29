#include "Snake.h"

//Initialize variables
void Snake::initVariables()
{
    this->movementSpeed = 10.f;
}
//Initialize Snake's shape
void Snake::initShape()
{
    this->snake.setFillColor(sf::Color::Blue);
    this->snake.setSize(sf::Vector2f(50.f,50.f));
    this->snake.setScale(sf::Vector2f(0.5f,0.5f));
}
//function to center the snake in window
void Snake::SnakePos(float x,float y)
{
    //spawn Snake
    this->snake.setPosition(x,y);
}
Snake::Snake(float x,float y)
{
    this->SnakePos();

    this->initVariables();
    this->initShape();
}

Snake::~Snake()
{
}
//Gets Snake shape
const sf::RectangleShape&  Snake::snakeShape() const
{
    return this->snake;
}
//Snake input control
void Snake::updateInput()
{
    //Keyboard input
    //left
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        this->snake.move(-this->movementSpeed,0.f);
    }
    //right
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->snake.move(this->movementSpeed,0.f);
    }
    //up
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        this->snake.move(0.f,-this->movementSpeed);
    }
    //down
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->snake.move(0.f,this->movementSpeed);
    }
    //window bound
}
//Snake map bounds
void Snake::updateWindowBoundsCoollision(const sf::RenderTarget* target)
{
    //Left bound
    if(this->snake.getGlobalBounds().left <= 0.f)
        this->snake.setPosition(0.f,this->snake.getGlobalBounds().top);
    //Right bound
    if(this->snake.getGlobalBounds().left + this->snake.getGlobalBounds().width >= target->getSize().x)
        this->snake.setPosition(target->getSize().x - this->snake.getGlobalBounds().width,this->snake.getGlobalBounds().top);
    //Top bound
    if(this->snake.getGlobalBounds().top <= 0.f)
        this->snake.setPosition(this->snake.getGlobalBounds().left,0.f);
    //Bottom bound
    if(this->snake.getGlobalBounds().top + this->snake.getGlobalBounds().height >= target->getSize().y)
        this->snake.setPosition(this->snake.getGlobalBounds().left,target->getSize().y - this->snake.getGlobalBounds().height);
}
void Snake::update(const sf::RenderTarget* target)
{
    this->updateInput();

    //Window bounds
    this->updateWindowBoundsCoollision(target);
}
void Snake::render(sf::RenderTarget* target)
{
    target->draw(this->snake);
}