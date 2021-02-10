#include "headerFiles/snake_game.h"

namespace SnakeGame
{
    const int SnakeGame::GetScore() { return this->score; }
    const int SnakeGame::GetMapHeight() { return this->map_height; }
    const int SnakeGame::GetMapWidth() { return this->map_width; }
    const int SnakeGame::GetSnakeLength() { return this->snake_body.size(); }
    const float SnakeGame::GetSnakeSpeed() { return this->snake_speed; }

    SnakeGame::SnakeGame(const float &snake_speed, const bool &map_loops,
                         const int &map_height, const int &map_width)
        : map_height(map_height), map_width(map_width),
          map_loops(map_loops), snake_speed(snake_speed)
    {
        this->snake_body.push_back(new SnakeNode(map_height / 2, map_width / 2));
        snake_body[0]->bkg_color = Colors::GREEN_BKG;
        food = new Food(this->map_height, this->map_width);
        this->food->Respawn();
        renderer = new Renderer(this->map_width, this->map_height, 2,
                                1, ConsoleRenderer::Colors::YELLOW_BKG);
    }

    SnakeGame::~SnakeGame()
    {
        for (int i = 0; i < snake_body.size(); i++)
            delete snake_body[i];
        delete food;
        delete renderer;
    }

    void SnakeGame::ChangeDirection(const Direction &new_direction)
    {
        if (new_direction + direction != 0)
            this->direction = new_direction;
    }

    const bool SnakeGame::Move()
    {
        bool outsideMap = false;

        int newPosX = snake_body[0]->pos.x;
        int newPosY = snake_body[0]->pos.y;

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
        if (!&tempNode->filled)
        {
            snake_body.pop_back();
            tempNode->pos.x = newPosX;
            tempNode->pos.y = newPosY;
        }
        else
        {
            tempNode->filled = false;
            tempNode = new SnakeNode(newPosX, newPosY);
        }
        snake_body.push_back(tempNode);

        for (int i = 1; i < snake_body.size(); i++)
        {
            if (&snake_body[0] == &snake_body[i])
                return false;
        }

        if (food->pos.x == snake_body.front()->pos.x && food->pos.y == snake_body.front()->pos.y)
        {
            snake_body.front()->filled = true;
            food->Respawn();
        }

        return true;
    }

} // namespace SnakeGame