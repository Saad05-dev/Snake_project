#include "Fruit.h"

//initialize Fruit 
void Fruit::initFruit(sf::RenderTarget& window)
{
    /*
        return void
        Spawns Fruit 
        -Sets a randow position
    */
   this->fruit.setPosition(10.f,10.f);
    this->fruit.setSize(sf::Vector2f(50.f,50.f));
    this->fruit.setScale(sf::Vector2f(0.5f,0.5f));
    this->fruit.setFillColor(sf::Color::Red);

   this->fruit.setPosition(
    static_cast<float>(rand() % window.getSize().x 
        - this->fruit.getSize().x),
    static_cast<float>(rand() % window.getSize().y
        - this->fruit.getSize().y)
   );
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
void Fruit::update()
{

}
void Fruit::render(sf::RenderTarget& target)
{
    target.draw(this->fruit);
}
