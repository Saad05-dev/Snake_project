#include "Fruit.h"

//initialize Fruit 
void Fruit::initFruit(sf::RenderTarget& window)
{
    /*
        return void
        Spawns Fruit 
    */
    this->fruit.setSize(sf::Vector2f(50.f,50.f));
    this->fruit.setScale(sf::Vector2f(0.5f,0.5f));
    this->fruit.setFillColor(sf::Color::Red);
}
Fruit::Fruit(sf::RenderWindow& window)
{
    this->initFruit(window);
}
Fruit::~Fruit()
{
}
//gets Fruits shape
const sf::RectangleShape Fruit::fruitShape() const
{
    return this->fruit;
}
//Randomize Spawn of Fruit
void Fruit::setRandomPosition(sf::RenderTarget& window, const std::vector<sf::RectangleShape>& snakeBody)
{
    // Get window bounds
    int maxX = static_cast<int>(window.getSize().x - this->fruit.getGlobalBounds().width);
    int maxY = static_cast<int>(window.getSize().y - this->fruit.getGlobalBounds().height);
    
    bool validPosition = false;

    float posX = std::max(0.f, static_cast<float>(rand() % maxX));
    float posY = std::max(0.f, static_cast<float>(rand() % maxY));
    
    while (!validPosition)
    {       
        // Check against all snake segments
        validPosition = true;
        for (const auto& segment : snakeBody)
        {
            if (this->fruitShape().getGlobalBounds().intersects(segment.getGlobalBounds()))
            {
                validPosition = false;
                break;
            }
        } 
        if (validPosition)
        {
            // We found a good position!
            this->fruit.setPosition(posX, posY);
            return;
        }
    }
    // If we couldn't find a valid position, just place it randomly
    this->fruit.setPosition(posX,posY);
}
void Fruit::render(sf::RenderTarget& target)
{
    target.draw(this->fruit);
}
