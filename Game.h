#pragma once
#include "Snake.h"

//Different Game status
enum class GameState
{
    Start_menu,
    Game,
    Game_Over,
    High_Scores,
    Quit
};
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
        //Game State
        GameState currentState;
        //Score state
        sf::RectangleShape container;
        vector<int> topScores = this->loadTopScore();
        sf::Text scores,titleScore;

        //Game objects
        Snake snake;
        std::vector<Fruit> fruits;

        //resources
        sf::Font font;

        //Text
        sf::Text title;
        sf::Text uiText;
        sf::Text endGameText;

        //Game logic
        bool grew = false;
        unsigned points;
        int Fruitspawn;
        float FruitspawnTimer;
        float FruitspawnTimerMax;
        
        //private functions
        void initVariables();
        void initWindow();
        void initFonts();
        void initText();
        void initStarMenu();
        void initHighScore();
        void initEndGame();
        //center snake Pos
        void SnakePos();

    public:
        //Button structure for navigation between states
        struct Button
        {
                sf::RectangleShape shape;
                sf::Text label;
                bool is_Hovered(const sf::Vector2f& mousePos) const
                {
                    return shape.getGlobalBounds().contains(mousePos);
                }
                void drawButton(sf::RenderWindow& window) const
                {
                    window.draw(shape);
                    window.draw(label);
                }
                function<void()> onClick;
        };
        Button makeButton(const string& text,sf::Vector2f pos)
        {
            Button btn;
            btn.shape.setSize({400,50});
            btn.shape.setPosition(pos);
            btn.shape.setFillColor(sf::Color(41,57,35));
            btn.shape.setOutlineColor(sf::Color::White);
            btn.shape.setOutlineThickness(-3.f);

            btn.label.setFont(this->font);
            btn.label.setString(text);
            btn.label.setCharacterSize(24);
            btn.label.setFillColor(sf::Color::White);
            btn.label.setPosition(pos.x + 20,pos.y + 10);

            return btn;
        }
        //Buttons
        vector<Button> menuButtons;
        vector<Button> highScoreButtons;
        //Constructor / Deconstructor
        Game();
        virtual ~Game();

        // Accessors
        const bool running() const;

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