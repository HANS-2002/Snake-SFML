#include <SFML/Graphics.hpp>
#include <time.h>
#include <bits/stdc++.h>
#include "./assets/pages/levels/level1.hpp"
#include "./assets/pages/gameOver.hpp"

using namespace sf;

int N = 30, M = 20;
int size = 16;
int w = size * N;
int h = size * (M + 1);

std::string highScore;
Texture snakeBody, snakeHeadLeft, snakeHeadRight, snakeHeadUp, snakeHeadDown, food;
Sprite snakeBodySprite, snakeHeadLeftSprite, snakeHeadRightSprite, snakeHeadUpSprite, snakeHeadDownSprite, foodSprite;

RenderWindow window(VideoMode(w, h), "Snake!");

Font font;

int dir, snakeLength = 2, score = 0;
bool gameOver = false;

struct Snake
{
    int x, y;
} s[1000];

struct Fruit
{
    int x, y;
} f;

bool isInsideSnake(int x, int y)
{
    for (int i = 1; i < snakeLength; i++)
        if (s[i].x == x && s[i].y == y)
            return true;
    return false;
}

void init()
{
    font.loadFromFile("./assets/font.ttf");

    snakeHeadDown.loadFromFile("./assets/images/snakeHead/snakeHeadDown.png");
    snakeHeadUp.loadFromFile("./assets/images/snakeHead/snakeHeadUp.png");
    snakeHeadLeft.loadFromFile("./assets/images/snakeHead/snakeHeadLeft.png");
    snakeHeadRight.loadFromFile("./assets/images/snakeHead/snakeHeadRight.png");
    snakeBody.loadFromFile("./assets/images/snakeBody.png");
    food.loadFromFile("./assets/images/food.png");

    snakeBodySprite.setTexture(snakeBody);
    snakeHeadLeftSprite.setTexture(snakeHeadLeft);
    snakeHeadRightSprite.setTexture(snakeHeadRight);
    snakeHeadUpSprite.setTexture(snakeHeadUp);
    snakeHeadDownSprite.setTexture(snakeHeadDown);
    foodSprite.setTexture(food);

    f.x = rand() % N;
    f.y = rand() % M;
    while (isInsideSnake(f.x, f.y))
    {
        f.x = rand() % N;
        f.y = rand() % M;
    }

    highScore = "";
}

void refresh()
{
    if ((s[0].x == f.x) && (s[0].y == f.y))
    {
        score++;
        snakeLength++;
        f.x = rand() % N;
        f.y = rand() % M;
        while (isInsideSnake(f.x, f.y))
        {
            f.x = rand() % N;
            f.y = rand() % M;
        }
    }

    for (int i = snakeLength; i > 0; i--)
    {
        s[i].x = s[i - 1].x;
        s[i].y = s[i - 1].y;
    }

    if (dir == 0) // up
        s[0].y += 1;
    if (dir == 1) // left
        s[0].x -= 1;
    if (dir == 2) // right
        s[0].x += 1;
    if (dir == 3) // down
        s[0].y -= 1;

    if (s[0].x > N - 1)
        s[0].x = 0;
    if (s[0].x < 0)
        s[0].x = N - 1;
    if (s[0].y > M - 1)
        s[0].y = 0;
    if (s[0].y < 0)
        s[0].y = M - 1;

    std::vector<int> barriers;
    if (snakeLength > 4)
        for (int i = 4; i < snakeLength; i++)
            if (s[0].x == s[i].x && s[0].y == s[i].y)
                snakeLength = 2, gameOver = true;
}

void drawSnake()
{
    for (int i = 0; i < snakeLength; i++)
    {
        if (i == 0)
        {
            if (dir == 0)
            {
                snakeHeadUpSprite.setPosition(s[i].x * size, s[i].y * size);
                window.draw(snakeHeadUpSprite);
            }
            else if (dir == 1)
            {
                snakeHeadRightSprite.setPosition(s[i].x * size, s[i].y * size);
                window.draw(snakeHeadRightSprite);
            }
            else if (dir == 2)
            {
                snakeHeadLeftSprite.setPosition(s[i].x * size, s[i].y * size);
                window.draw(snakeHeadLeftSprite);
            }
            else if (dir == 3)
            {
                snakeHeadDownSprite.setPosition(s[i].x * size, s[i].y * size);
                window.draw(snakeHeadDownSprite);
            }
        }
        else
        {
            snakeBodySprite.setPosition(s[i].x * size, s[i].y * size);
            window.draw(snakeBodySprite);
        }
    }
}

void drawFood()
{
    foodSprite.setPosition(f.x * size, f.y * size);
    window.draw(foodSprite);
}

int main()
{
    srand(time(0));
    init();

    Clock clock;
    float speed = 12;
    float timer = 0, delay = 1 / speed;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        std::ifstream ifs("./assets/highScore");
        ifs >> highScore;
        ifs.close();

        Event e;
        while (window.pollEvent(e))
            if (e.type == Event::Closed)
                window.close();

        // Input
        if (Keyboard::isKeyPressed(Keyboard::Left) && dir != 2)
            dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::Right) && dir != 1)
            dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::Up) && dir != 0)
            dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::Down) && dir != 3)
            dir = 0;
        if (gameOver && Keyboard::isKeyPressed(Keyboard::Enter))
            gameOver = false, score = 0;

        // Game Speed
        if (timer > delay)
        {
            timer = 0;
            refresh();
        }

        // Drawing
        window.clear();
        if (!gameOver)
        {
            if (highScore == "")
                highScore = "0";

            std::stringstream ss;
            ss << score;

            std::string scoreStr;
            ss >> scoreStr;

            std::string score = "Score: " + scoreStr;
            std::string highScoreStr = "High Score: " + highScore;

            Text highScoreText;
            highScoreText.setFont(font);
            highScoreText.setString(highScoreStr);
            highScoreText.setCharacterSize(16);
            highScoreText.setFillColor(Color::Red);
            highScoreText.setStyle(Text::Bold);
            highScoreText.setPosition(w - highScoreText.getGlobalBounds().width, h - size);

            Text scoreText;
            scoreText.setString(score);
            scoreText.setFont(font);
            scoreText.setCharacterSize(16);
            scoreText.setFillColor(Color::Red);
            scoreText.setStyle(Text::Bold);
            scoreText.setPosition(0, h - size);

            GameLevel1::drawBoard(&window, N, M, size);
            drawFood();
            drawSnake();
            window.draw(highScoreText);
            window.draw(scoreText);
        }
        else
            GameOver::drawGameOver(&window, w, h, size, font, highScore, score);
        window.display();
    }

    return 0;
}
