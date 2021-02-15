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
        this->snake_body.push_front(new SnakeNode(round(map_width / 2), round(map_height / 2)));
        food = new Food(this->map_height, this->map_width);
        this->food->Respawn();
        renderer = new Renderer(this->map_width, this->map_height, 3,
                                1, ConsoleRenderer::Colors::YELLOW_BKG);
        renderer->TryAddTextBox("score", "Score: ", std::to_string(score),
                                Colors::WHITE_TXT, Colors::YELLOW_TXT);
        renderer->TryAddTextBox("speed", "Speed: ", std::to_string(snake_speed),
                                Colors::WHITE_TXT, Colors::BLUE_TXT);
        renderer->TryAddTextBox("length", "Snake length: ", std::to_string(this->snake_length),
                                Colors::WHITE_TXT, Colors::YELLOW_TXT);
        renderer->TryAddToRenderQueue(snake_body[0]);
        renderer->TryAddToRenderQueue(food);
        renderer->Init();
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
        bool outside_map = false;
        bool dead = false;

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
            outside_map = true;
            newPosX = 1;
        }
        else if (newPosX < 1)
        {
            outside_map = true;
            newPosX = map_width;
        }
        else if (newPosY > map_height)
        {
            outside_map = true;
            newPosY = 1;
        }
        else if (newPosY < 1)
        {
            outside_map = true;
            newPosY = map_height;
        }

        if (outside_map && !map_loops)
            dead = true;

        SnakeNode *tempNode = snake_body.back();
        if (tempNode->filled)
        {
            tempNode->filled = false;
            tempNode->block_texture[0] = ' ';
            tempNode->block_texture[1] = ' ';
            renderer->TryAddToRenderQueue(tempNode);
            tempNode = new SnakeNode(newPosX, newPosY);
        }
        else
        {
            renderer->TryAddToDeleteQueue(tempNode->pos.x, tempNode->pos.y);
            snake_body.pop_back();
            tempNode->pos.x = newPosX;
            tempNode->pos.y = newPosY;
        }
        tempNode->bkg_color = Colors::YELLOW_BKG;
        renderer->TryAddToRenderQueue(tempNode);
        snake_body.push_front(tempNode);

        for (int i = 1; i < snake_body.size(); i++)
        {
            if (&snake_body[0] == &snake_body[i])
                dead = true;
        }

        if (food->pos.x == snake_body.front()->pos.x && food->pos.y == snake_body.front()->pos.y)
        {
            snake_body.front()->filled = true;
            score += food->GetValue();
            food->Respawn();

            renderer->GetTextBox("score")->text = std::to_string(score);
            renderer->TryRenderTextBox("score");
        }

        if (snake_body.size() > 1)
        {
            SnakeNode *p_second_node = snake_body[1];
            if (snake_body[1]->filled)
            {
                p_second_node->block_texture[0] = '[';
                p_second_node->block_texture[1] = ']';
            }
            p_second_node->bkg_color = Colors::GREEN_BKG;
            renderer->TryAddToRenderQueue(p_second_node);
        }

        renderer->TryAddToRenderQueue(food);
        renderer->Render();
        return dead;
    }

} // namespace SnakeGame