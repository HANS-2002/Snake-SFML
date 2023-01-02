#include <SFML/Graphics.hpp>
#include <time.h>
#include <bits/stdc++.h>

using namespace sf;

namespace GameOver
{
    void drawGameOver(RenderWindow *window, int w, int h, int size, Font font, std::string highScore, int score)
    {
        int hs = std::stoi(highScore);
        if (score > hs)
        {
            std::ofstream ofs("./assets/highScore");
            ofs << score;
        }

        std::stringstream ss;
        ss << score;

        std::string scoreStr;
        ss >> scoreStr;
        std::string str = "Game Over!\nScore: " + scoreStr + "\nPress Enter to Continue!";

        Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString(str);
        gameOverText.setCharacterSize(24);
        gameOverText.setFillColor(Color::Red);
        gameOverText.setStyle(Text::Bold);
        gameOverText.setOrigin(gameOverText.getGlobalBounds().width / 2.0f, gameOverText.getGlobalBounds().height / 2.0f);
        gameOverText.setPosition(w / 2.0f, h / 2.0f);
        window->draw(gameOverText);
    }
};