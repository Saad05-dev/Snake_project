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
}

Snake::Snake(float x,float y)
{
    //spawn Snake
    this->snake.setPosition(x,y);

    this->initVariables();
    this->initShape();
}

Snake::~Snake()
{
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
void Snake::update()
{
    this->updateInput();
}
void Snake::render(sf::RenderTarget* target)
{
    target->draw(this->snake);
}