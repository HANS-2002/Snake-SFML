#include <SFML/Graphics.hpp>
#include <time.h>
#include <bits/stdc++.h>

using namespace sf;

namespace GameLevel1
{
    void drawBoard(RenderWindow *window, int N, int M, int size)
    {
        Texture background;
        Sprite backgroundSprite;
        background.loadFromFile("./assets/images/background.png");
        backgroundSprite.setTexture(background);
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                backgroundSprite.setPosition(i * size, j * size);
                window->draw(backgroundSprite);
            }
        }
    }
};