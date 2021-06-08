#include "header_files/snake_game.h"

namespace SnakeGame
{
    const bool SnakeGame::IsGameOver() { return this->game_over; }
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
        SnakeNode *head = new SnakeNode(round(map_width / 2), round(map_height / 2));
        this->snake_body.push_front(head);
        food = new Food(this->map_height, this->map_width);
        this->food->Respawn();
        renderer = new Renderer(this->map_width, this->map_height, 3,
                                1, ConsoleRenderer::Color::YELLOW_BKG);
        renderer->TryAddTextBox("score", "Score: ", std::to_string(score),
                                Color::WHITE_TXT, Color::YELLOW_TXT);
        renderer->TryAddTextBox("speed", "Speed: ", std::to_string(snake_speed),
                                Color::WHITE_TXT, Color::BLUE_TXT);
        renderer->TryAddTextBox("length", "Snake length: ", std::to_string(this->snake_length),
                                Color::WHITE_TXT, Color::YELLOW_TXT);
        renderer->TryRegisterObject(head);
        renderer->TryRegisterObject(food);
        renderer->Show();
    }

    SnakeGame::~SnakeGame()
    {
        for (int i = 0; i < snake_body.size(); i++)
            delete snake_body[i];
        delete food;
    }

    void SnakeGame::ChangeDirection(const Direction &new_direction)
    {
        if (new_direction + direction != 0)
            this->direction = new_direction;
    }

    void SnakeGame::Move()
    {
        if(game_over)
            return;

        bool outside_map = false;

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
            game_over = true;

        SnakeNode *tempNode = snake_body.back();
        if (tempNode->filled)
        {
            tempNode->filled = false;
            tempNode->block_texture[0] = ' ';
            tempNode->block_texture[1] = ' ';
            tempNode = new SnakeNode(newPosX, newPosY);
            renderer->TryRegisterObject(tempNode);
        }
        else
        {
            snake_body.pop_back();
            tempNode->pos.x = newPosX;
            tempNode->pos.y = newPosY;
        }
        tempNode->bkg_color = Color::YELLOW_BKG;
        snake_body.push_front(tempNode);

        for (int i = 1; i < snake_body.size(); i++)
        {
            if (&snake_body[0] == &snake_body[i])
                game_over = true;
        }

        if (food->pos.x == snake_body.front()->pos.x && food->pos.y == snake_body.front()->pos.y)
        {
            snake_body.front()->filled = true;
            score += food->GetValue();
            food->Respawn();

            renderer->TryEditTextBox("score", std::to_string(score));
        }

        if (snake_body.size() > 1)
        {
            SnakeNode *p_second_node = snake_body[1];
            if (snake_body[1]->filled)
            {
                p_second_node->block_texture[0] = '[';
                p_second_node->block_texture[1] = ']';
            }
            p_second_node->bkg_color = Color::GREEN_BKG;
            renderer->TryRegisterObject(p_second_node);
        }

       renderer->Render();
    }

} // namespace SnakeGame