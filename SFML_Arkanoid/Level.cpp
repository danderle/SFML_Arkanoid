#include "Level.h"

std::vector<Brick> Level::Create(int level)
{
    std::vector<Brick> bricks;

    int yStep = -1;
    switch (level)
    {
    case 1:
    {
        sf::Color color(255, 0, 0);
        for (int i = 0; i < 66; i++)
        {
            float x = (i * (int)Brick::Width) % 990 + Board::Padding;
            if (x == Board::Padding)
            {
                yStep++;
                if (yStep == 1)
                {
                    color = sf::Color::Green;
                }
                else if (yStep == 2)
                {
                    color = sf::Color::Yellow;
                }
            }
            float y = yStep * Brick::Height + 60;
            bricks.push_back({ {x,y}, color });
        }
    }
    break;
    case 2:
    {
        sf::Color color(255, 0, 0);
        for (int i = 0; i < 60; i++)
        {
            float x = (i * (int)Brick::Width) % 900 + Board::Padding + 45;
            if (x == Board::Padding + 45)
            {
                yStep++;
                if (yStep == 1)
                {
                    color = sf::Color::Green;
                }
                else if (yStep == 2)
                {
                    color = sf::Color::Yellow;
                }
            }
            float y = yStep * Brick::Height + 60;
            bricks.push_back({ {x,y}, color });
        }
    }
    break;
    }
    return bricks;
}
