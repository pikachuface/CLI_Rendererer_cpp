#include "snake_game.h"

namespace SnakeGame
{

    const int SnakeGame::GetMapHeight() { return this->map_height; }
    const int SnakeGame::GetMapWidth() { return this->map_width; }
    const int SnakeGame::GetSnakeLength() { return this->snake_body.size(); }
    const float SnakeGame::GetSnakeSpeed() { return this->snake_speed; }

    SnakeGame::SnakeGame(const float &snake_speed, const bool &map_loops,
                         const int &map_height, const int &map_width)
    {
        this->map_loops = map_loops;
        this->map_height = map_height;
        this->map_width = map_width;
        this->snake_speed = snake_speed;
        this->snake_body.push_back(&SnakeNode(map_height / 2, map_width / 2));
    }

    SnakeGame::SnakeGame(const float &snake_speed, const bool &map_loops)
    {
        this->map_loops = map_loops;
        this->snake_speed = snake_speed;
        this->snake_body.push_back(&SnakeNode(map_height / 2, map_width / 2));
    }

    SnakeGame::SnakeGame(const float &snake_speed)
    {
        this->snake_speed = snake_speed;
        this->snake_body.push_back(&SnakeNode(map_height / 2, map_width / 2));
    }

    SnakeGame::~SnakeGame()
    {
        for(int i = 0; i < snake_body.size(); i++)
            delete snake_body[i];
    }

    void SnakeGame::ChangeDirection(const Direction &newDirection)
    {
        this->direction = newDirection;
    }

    const bool SnakeGame::Move()
    {
        bool outsideMap = false;

        int newPosX = snake_body[0]->pos_x;
        int newPosY = snake_body[0]->pos_y;

        if (this->direction == Direction::Left)
            newPosX--;
        else if (this->direction == Direction::Right)
            newPosX++;
        else if (this->direction == Direction::Up)
            newPosY--;
        else if (this->direction == Direction::Down)
            newPosY++;

        if (newPosX > map_width)
        {
            outsideMap = true;
            newPosX = 1;
        }
        else if (newPosX < 1)
        {
            outsideMap = true;
            newPosX = map_width;
        }
        else if (newPosY > map_height)
        {
            outsideMap = true;
            newPosY = 1;
        }
        else if (newPosY < 1)
        {
            outsideMap = true;
            newPosY = map_height;
        }

        if (outsideMap && !map_loops)
            return false;

        SnakeNode *tempNode = snake_body.back();
        if (&tempNode->filled)
        {
            snake_body.pop_back();
            tempNode->pos_x = newPosX;
            tempNode->pos_y = newPosY;
        }
        else
            tempNode->filled = false;

        tempNode = new SnakeNode(newPosX, newPosY);
        snake_body.push_back(tempNode);

        for (int i = 1; i < snake_body.size(); i++)
        {
            if (&snake_body[0] == &snake_body[i])
                return false;
        }

        if (food.pos_x == snake_body.front()->pos_x && food.pos_y == snake_body.front()->pos_y)
        {
            snake_body.front()->filled = true;
        }

        return true;
    }

} // namespace SnakeGame