#pragma once
namespace SnakeGame
{
    struct SnakeNode
    {
        int pos_x;
        int pos_y;
        bool filled;

        SnakeNode(int pos_x, int pos_y)
        {
            this->pos_x = pos_x;
            this->pos_y = pos_y;
        }

        bool operator==(const SnakeNode &second)
        {
            if (this->pos_x == second.pos_x && this->pos_y == second.pos_y) return true;
            return false;
        }
    };
} // namespace SnakeGame