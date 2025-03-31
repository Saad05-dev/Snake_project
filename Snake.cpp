#include "Snake.h"

//Initialize variables
void Snake::initVariables()
{
    this->movementSpeed = 5.f;  // Reduced from 5.0f to 2.0f for slower movement
    this->direction = {movementSpeed, 0};
    this->segmentSize = 25.f;
    this->segmentSpacing = 0.f; // Added spacing between segments to prevent overlap
}
//initialize snake's segments
void Snake::initSnake()
{
     // Clear previous segments (if any)
     snake.clear();

     // Create the head
     sf::RectangleShape head(sf::Vector2f(segmentSize, segmentSize));
     head.setFillColor(sf::Color::Cyan);
     head.setOutlineColor(sf::Color::Black);
     head.setOutlineThickness(-2.f);
     head.setPosition(300.f, 300.f); // Initial head position
 
     // Create first body part - positioned exactly one unit left of the head
     sf::RectangleShape body1(sf::Vector2f(segmentSize, segmentSize));
     body1.setFillColor(sf::Color::Blue);
     body1.setOutlineColor(sf::Color::Black);
     body1.setOutlineThickness(-2.f);
     body1.setPosition(300.f - (segmentSize + segmentSpacing), 300.f); 
 
     // Create second body part - positioned exactly one unit left of body1
     sf::RectangleShape body2(sf::Vector2f(segmentSize, segmentSize));
     body2.setFillColor(sf::Color::Blue);
     body2.setOutlineColor(sf::Color::Black);
     body2.setOutlineThickness(-2.f);
     body2.setPosition(300.f - 2 * (segmentSize + segmentSpacing), 300.f);
 
     // Add them to the snake vector
     snake.push_back(head);
     snake.push_back(body1);
     snake.push_back(body2);
}

// Snake movement with body
void Snake::movement()
{
    if (snake.empty()) return;

    // Control snake movement speed by implementing a frame counter
    static int frameCounter = 0;
    frameCounter++;
    
    // Only move the snake every N frames to slow it down
    // Lower number = faster movement, higher number = slower movement
    const int moveEveryNFrames = 10;  // Adjust this value to control speed
    
    if (frameCounter % moveEveryNFrames != 0) {
        return;  // Skip movement this frame
    }

    // Store the previous positions of each segment
    std::vector<sf::Vector2f> prevPositions(snake.size());
    for (size_t i = 0; i < snake.size(); ++i)
    {
        prevPositions[i] = snake[i].getPosition();
    }

    // Move the head first based on the current direction
    // Use exact movement to maintain grid alignment
    float moveAmount = segmentSize + segmentSpacing;
    
    sf::Vector2f normalizedDir = direction;
    float length = std::sqrt(normalizedDir.x * normalizedDir.x + normalizedDir.y * normalizedDir.y);
    if (length > 0) {
        normalizedDir.x /= length;
        normalizedDir.y /= length;
    }
    
    // Move the head by exactly one grid unit in the current direction
    snake[0].move(normalizedDir.x * moveAmount, normalizedDir.y * moveAmount);

    // Move the body segments to previous positions
    for (size_t i = 1; i < snake.size(); ++i)
    {
        snake[i].setPosition(prevPositions[i-1]);
    }
}

//add new segment at snake tail
void Snake::grow()
{
    if (snake.empty()) return;
    
    sf::RectangleShape newSegment(sf::Vector2f(segmentSize, segmentSize));
    newSegment.setFillColor(sf::Color::Blue);
    newSegment.setOutlineColor(sf::Color::Black);
    newSegment.setOutlineThickness(-2.f);

    // Position new segment based on the last two segments
    if (snake.size() >= 2) {
        // Get the last two positions
        sf::Vector2f tailPos = snake.back().getPosition();
        sf::Vector2f beforeTailPos = snake[snake.size() - 2].getPosition();
        
        // Calculate direction vector from second-to-last to last segment
        sf::Vector2f direction = tailPos - beforeTailPos;
        
        // Position the new segment continuing in that same direction
        newSegment.setPosition(
            tailPos.x + direction.x,
            tailPos.y + direction.y
        );
    } else {
        // If there's only one segment, place it opposite to movement direction
        sf::Vector2f tailPos = snake.back().getPosition();
        sf::Vector2f oppositeDir(-direction.x, -direction.y);
        
        float length = std::sqrt(oppositeDir.x * oppositeDir.x + oppositeDir.y * oppositeDir.y);
        if (length > 0) {
            oppositeDir.x /= length;
            oppositeDir.y /= length;
        }
        
        newSegment.setPosition(
            tailPos.x + oppositeDir.x * (segmentSize + segmentSpacing),
            tailPos.y + oppositeDir.y * (segmentSize + segmentSpacing)
        );
    }

    // Add new segment to the snake
    snake.push_back(newSegment);

    std::cout << "snake grew! new size: " << snake.size() << "\n";
}

//check if snake collides with it's tail
bool Snake::snakeCollision() 
{
    if (snake.size() < 4) return false; // Need at least 4 segments for self-collision
    
    // Check if head collides with any body segment (starting from 4th segment to avoid false positives)
    for (size_t i = 3; i < snake.size(); ++i)
    {
        if(snake[0].getGlobalBounds().intersects(snake[i].getGlobalBounds()))
        {
            std::cout << "head position: (" 
            << snake[0].getPosition().x << ", " 
            << snake[0].getPosition().y << ")\n";
            std::cout << "colliding segment position: (" 
            << snake[i].getPosition().x << ", " 
            << snake[i].getPosition().y << ")\n";
  
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
void Snake::SnakePos(float x, float y)
{
    // This should be called after snake is initialized
    if(snake.empty()) return;
    
    // Position head
    snake[0].setPosition(x, y);

    // Position segments to the left of the head with proper spacing
    for (size_t i = 1; i < snake.size(); ++i)
    {
        snake[i].setPosition(x - i * (segmentSize + segmentSpacing), y);
    }
}

Snake::Snake(float x, float y)
{
    this->initVariables();
    this->initSnake();
    if (x > 0.f || y > 0.f) { // Only reposition if coordinates are provided
        this->SnakePos(x, y);
    }
}

Snake::~Snake()
{
}

//Gets Snake shape
void Snake::snakeShape()
{
    for(auto& segment : snake)
    {
        segment.setSize(sf::Vector2f(segmentSize, segmentSize));
        segment.setFillColor(sf::Color::Blue);
    }
}

//Snake input control
void Snake::updateInput()
{
    // Store previous keystroke for debouncing
    static sf::Vector2f lastDir = direction;
    static bool inputProcessed = false;
    
    // Only process new input if we've moved since the last keystroke
    if (inputProcessed) {
        // Check if the head has moved to a new grid position
        static sf::Vector2f lastHeadPos = snake[0].getPosition();
        sf::Vector2f currentHeadPos = snake[0].getPosition();
        
        // If the head has moved, we can process new input
        if (lastHeadPos != currentHeadPos) {
            inputProcessed = false;
            lastHeadPos = currentHeadPos;
        } else {
            // Head hasn't moved yet, don't process new input
            return;
        }
    }
    
    // Keyboard input with direction checks to prevent 180° turns
    
    // Left
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        && direction.x == 0) // Only allow turning left if not moving horizontally
    {
        direction = {-this->movementSpeed, 0.f};
        inputProcessed = true;
    }
    // Right
    else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        && direction.x == 0) // Only allow turning right if not moving horizontally
    {
        direction = {this->movementSpeed, 0.f};
        inputProcessed = true;
    }
    // Up
    else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        && direction.y == 0) // Only allow turning up if not moving vertically
    {
        direction = {0.f, -this->movementSpeed};
        inputProcessed = true;
    }
    // Down
    else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        && direction.y == 0) // Only allow turning down if not moving vertically
    {
        direction = {0.f, this->movementSpeed};
        inputProcessed = true;
    }
}

//Snake map bounds
//if snake reaches any bounds gets out from the opposite direction of the bound
void Snake::updateWindowBoundsCoollision(const sf::RenderTarget* target)
{
    if (snake.empty()) return;
    
    // Handle head first
    //Left bound
    if(snake[0].getGlobalBounds().left < 0.f)
        snake[0].setPosition(target->getSize().x - segmentSize, snake[0].getPosition().y);
    //Right bound
    if(snake[0].getGlobalBounds().left + snake[0].getGlobalBounds().width > target->getSize().x)
        snake[0].setPosition(0.f, snake[0].getPosition().y);
    //Top bound
    if(snake[0].getGlobalBounds().top < 0.f)
        snake[0].setPosition(snake[0].getPosition().x, target->getSize().y - segmentSize);
    //Bottom bound
    if(snake[0].getGlobalBounds().top + snake[0].getGlobalBounds().height > target->getSize().y)
        snake[0].setPosition(snake[0].getPosition().x, 0.f);
    
    // Handle other segments - this is needed less frequently but handles edge cases
    for (size_t i = 1; i < snake.size(); ++i)
    {
        //Left bound
        if(snake[i].getGlobalBounds().left < 0.f)
            snake[i].setPosition(target->getSize().x - segmentSize, snake[i].getPosition().y);
        //Right bound
        if(snake[i].getGlobalBounds().left + snake[i].getGlobalBounds().width > target->getSize().x)
            snake[i].setPosition(0.f, snake[i].getPosition().y);
        //Top bound
        if(snake[i].getGlobalBounds().top < 0.f)
            snake[i].setPosition(snake[i].getPosition().x, target->getSize().y - segmentSize);
        //Bottom bound
        if(snake[i].getGlobalBounds().top + snake[i].getGlobalBounds().height > target->getSize().y)
            snake[i].setPosition(snake[i].getPosition().x, 0.f);
    }
}

void Snake::update(const sf::RenderTarget* target)
{
    this->updateInput();
    this->movement();
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