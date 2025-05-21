#pragma once
#include "Snake.h"


//Game file that stores score
const string SCORE_FILE = "HighScore.txt";
// start of Game class

class Game
{
    private:
        //variables
        //Window
        sf::RenderWindow *window;
        sf::VideoMode videoMode;
        sf::Event ev;

        //Game objects
        Snake snake;
        std::vector<Fruit> fruits;

        //resources
        sf::Font font;

        //Text
        sf::Text uiText;
        sf::Text endGameText;

        //Game logic
        bool grew = false;
        bool endGame;
        unsigned points;
        int Fruitspawn;
        float FruitspawnTimer;
        float FruitspawnTimerMax;
        
        //private functions
        void initVariables();
        void initWindow();
        void initFonts();
        void initText();
        //center snake Pos
        void SnakePos();

    public:

        //Constructor / Deconstructor
        Game();
        virtual ~Game();

        // Accessors
        const bool running() const;
        const bool getEndGame() const;

        //functions

        void pollEvents();
        void spawnFruits();
        void updateText();
        void updateCollision();
        void update();
        //Score
        void saveScore(int score);
        vector<int> loadTopScore(int high = 3);

        void renderText(sf::RenderTarget& target);
        void render();
};