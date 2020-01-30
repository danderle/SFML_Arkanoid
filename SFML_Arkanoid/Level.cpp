#include "Level.h"

std::vector<Brick> Level::Create(int level)
{
    std::vector<Brick> bricks;

    switch (level)
    {
    case 1:
    {
        int yStep = -1;
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

    }
    return bricks;
}
