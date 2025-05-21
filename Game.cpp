#include "Game.h"

// Private functions

//intialize variables
void Game::initVariables()
{
    this->window = nullptr;
    //Game State
    this->currentState = GameState::Start_menu;
    //Game logic
    this->Fruitspawn = 1;
    this->points = 0;
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
    //Game Title
    this->title.setFont(this->font);
    this->title.setString("SNAKE GAME");
    this->title.setCharacterSize(50);
    this->title.setFillColor(sf::Color::Yellow);
    this->title.setPosition(150,100);
    //Gui text init
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::White);

    //End game text

    this->endGameText.setFont(this->font);
    this->endGameText.setFillColor(sf::Color::Black);
    this->endGameText.setCharacterSize(55);
    this->endGameText.setPosition(sf::Vector2f(20,200));
}
void Game::initStarMenu()
{
    Button Play_Game = makeButton("Play",{200,200});
    Button high_Score_Btn = makeButton("High_Scores",{200,270});
    Button quitBtn = makeButton("Quit",{200,340});

    //Add onclick functionnality
        Play_Game.onClick = [this]()
        {
            this->currentState = GameState::Game;
        };
        high_Score_Btn.onClick = [this]()
        {
            this->currentState = GameState::High_Scores;
        };
        quitBtn.onClick = [this]()
        {
            this->currentState = GameState::Quit;
        };
        //Add buttons
        this->menuButtons.push_back(Play_Game);
        this->menuButtons.push_back(high_Score_Btn);
        this->menuButtons.push_back(quitBtn);
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
            // Create a new fruit
            Fruit newFruit(*this->window);
            
            // Set its position avoiding the snake
            newFruit.setRandomPosition(*this->window, this->snake.getBody());
            
            // Add it to the fruits vector
            this->fruits.push_back(newFruit);
            this->FruitspawnTimer = 0.f;
        }
    }
}
//checks for collision between snake and fruit
void Game::updateCollision()
{
    for (int i = this->fruits.size() - 1; i >= 0; i--)
    {
        if (this->snake.getBody()[0].getGlobalBounds().intersects(
            this->fruits[i].fruitShape().getGlobalBounds()))
        {
            this->points++;
            this->fruits.erase(this->fruits.begin() + i);
            this->snake.grow();
            grew = true;
            spawnFruits();
        }
    }
}

//Game uitext 
void Game::updateText()
{
    //points Text
    std::stringstream ss;
    ss << "Points: "<< this->points<<"\n";
    this->uiText.setString(ss.str());
    //End game Text
    std::stringstream sd;
    sd << " Game over!\nyour score: " << this->points;
    this->endGameText.setString(sd.str());
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
    this->initStarMenu();
    this->SnakePos();
}
Game::~Game()
{
    delete this->window;
}
//Accessors
const bool Game::running() const
{
    return this->window->isOpen() ;
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
void Game::saveScore(int score) 
{
    ofstream outFile(SCORE_FILE, ios::app);
    if (outFile.is_open()) {
        outFile << score << '\n';
        outFile.close();
    }
}

std::vector<int> Game::loadTopScore(int high) 
{
    vector<int> scores;
    ifstream inFile(SCORE_FILE);
    int score;

    while (inFile >> score) {
        scores.push_back(score);
    }

    std::sort(scores.begin(), scores.end(), greater<int>());
    if (scores.size() > high) {
        scores.resize(high);
    }

    return scores;
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
   switch (this->currentState)
   {
    //Draw start menu
   case GameState::Start_menu:
        this->window->draw(this->title);
        // Draw menu buttons
        for (auto& btn : this->menuButtons)
        {
                btn.drawButton(*this->window);
        }
    break;
    case GameState::Game:
        //Draw game objects

        this->renderText(*this->window);

        //render snake
            this->snake.render(this->window);
        //render Fruits
        for (auto i : this->fruits)
        {
                i.render(*this->window);
        }
    break;
    case GameState::Game_Over:
        this->window->clear(sf::Color(141, 161, 89));
        this->window->draw(this->endGameText);
    break;
    case GameState::High_Scores:
    break;
    case GameState::Quit:
   default:
    break;
   }
   
   this->window->display();
}   