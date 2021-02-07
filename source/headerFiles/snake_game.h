#pragma once
#include <vector>
#include "snake_node.h"
#include "food.h"

namespace SnakeGame
{
    class SnakeGame
    {
    public:
        enum Direction
        {
            None,
            Up,
            Down,
            Left,
            Right
        };

    private:
        //Map variables
        int map_height = 10;
        int map_width = 10;
        bool map_loops = true;
        //Snake variables
        std::vector<SnakeNode *> snake_body;
        int snake_length;
        float snake_speed;
        Direction direction = Direction::None;
        //Food
        Food food;
        //Game
        int score = 0;

    public:
        //Getters
        const int GetScore();
        const int GetMapHeight();
        const int GetMapWidth();
        const int GetSnakeLength();
        const float GetSnakeSpeed();
        //Constructors | Destructors
        SnakeGame(const float &speed);
        SnakeGame(const float &speed, const bool &map_loops);
        SnakeGame(const float &speed, const bool &map_loops,
                  const int &map_Height, const int &map_width);
        ~SnakeGame();
        //Game Methods
        void ChangeDirection(const Direction &new_direction);
        const bool Move();
    };
} // namespace SnakeGame