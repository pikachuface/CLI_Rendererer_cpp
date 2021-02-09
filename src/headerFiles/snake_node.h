#pragma once
#include "renderable_object.h"
using namespace ConsoleRenderer;
namespace SnakeGame
{
    class SnakeNode : public RenderableObject
    {
    public:
        bool filled = false;
        SnakeNode(const int &pos_x, const int &pos_y)
            : RenderableObject(pos_x, pos_x, Colors::YELLOW_BKG) {}

        bool operator==(const SnakeNode &second)
        {
            if (this->pos_x == second.pos_x && this->pos_y == second.pos_y)
                return true;
            else
                return false;
        }
    };
} // namespace SnakeGame