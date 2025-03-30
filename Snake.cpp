#include "Snake.h"

//Initialize variables
void Snake::initVariables()
{
    this->movementSpeed = 10.f;
}
//Initialize Snake's shape
void Snake::initShape()
{
    /*
    this->snake.setFillColor(sf::Color::Blue);
    this->snake.setSize(sf::Vector2f(50.f,50.f));
    this->snake.setScale(sf::Vector2f(0.5f,0.5f));
    */
   sf::RectangleShape segment(sf::Vector2f(25.f,25.f));
   segment.setFillColor(sf::Color::Blue);
   snake.push_back(segment);
}
// Snake movement with body
void Snake::move()
{
    //moves body segment starting from last except the head
    for (size_t i = this->snake.size() -1; i > 0; --i)
    {
        snake[i].setPosition(snake[i-1].getPosition());
    }
    
    //move head
    sf::Vector2f headPos = snake[0].getPosition();
    if(direction == Direction::UP) headPos.y -= movementSpeed;
    else if (direction == Direction::DOWN) headPos.y += movementSpeed;
    else if(direction == Direction::LEFT) headPos.x -= movementSpeed;
    else if(direction == Direction::RIGHT) headPos.x += movementSpeed;

    snake[0].setPosition(headPos);
}
//add new segement at snake tail
void Snake::grow()
{
    sf::RectangleShape newSegment(sf::Vector2f(25.f,25.f));
    newSegment.setFillColor(sf::Color::Blue);
    newSegment.setPosition(snake.back().getPosition());
    snake.push_back(newSegment);
}
//check if snake collides with it's tail
bool Snake::snakeCollision() 
{
    for (size_t i = 1; i < snake.size(); ++i)
    {
        if(snake[0].getGlobalBounds().intersects(snake[i].getGlobalBounds()))
        {
            return true; //snake collision
        }
    }
    return false;
}
//Get the full body of snake
const std::vector<sf::RectangleShape>& Snake::getBody() const
{
    return this->snake;
}
//function to center the snake in window
void Snake::SnakePos(float x,float y)
{
    //spawn Snake
    if(!snake.empty())
    {
        snake[0].setPosition(x,y);
    }
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
void Snake::snakeShape()
{
    for(auto& segement : snake)
    {
        segement.setSize(sf::Vector2f(25.f,25.f));
        segement.setFillColor(sf::Color::Blue);
    }
}
//Snake input control
void Snake::updateInput()
{
    //Keyboard input
    //left
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        //this->snake.move(-this->movementSpeed,0.f);
        direction = Direction::LEFT;
    }
    //right
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        //this->snake.move(this->movementSpeed,0.f);
        direction = Direction::RIGHT;
    }
    //up
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        //this->snake.move(0.f,-this->movementSpeed);
        direction = Direction::UP;
    }
    //down
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        //this->snake.move(0.f,this->movementSpeed);
        direction = Direction::DOWN;
    }
    //window bound
}
//Snake map bounds
//if snake reachs any bounds gets out from the opposite direction of the bound
void Snake::updateWindowBoundsCoollision(const sf::RenderTarget* target)
{
    //Left bound
    if(snake[0].getGlobalBounds().left <= 0.f)
        snake[0].setPosition(target->getSize().x - snake[0].getGlobalBounds().width,
            snake[0].getPosition().y);
    //Right bound
    if(snake[0].getGlobalBounds().left + snake[0].getGlobalBounds().width >= target->getSize().x)
        snake[0].setPosition(0.f,snake[0].getPosition().y);
    //Top bound
    if(snake[0].getGlobalBounds().top <= 0.f)
        snake[0].setPosition(snake[0].getPosition().x,
            target->getSize().y - snake[0].getGlobalBounds().height);
    //Bottom bound
    if(snake[0].getGlobalBounds().top + snake[0].getGlobalBounds().height >= target->getSize().y)
        snake[0].setPosition(snake[0].getPosition().x,0.f);
        
}
void Snake::update(const sf::RenderTarget* target)
{
    this->updateInput();

    //Window bounds
    this->updateWindowBoundsCoollision(target);
}
void Snake::render(sf::RenderTarget* target)
{
    //renders the whole snake
    for(const auto& segment : this->snake)
    {
        target->draw(segment);
    }
}