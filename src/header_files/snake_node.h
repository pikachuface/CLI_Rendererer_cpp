#pragma once
#include "../CLI_renderer_lib/renderable_object.h"
using namespace ConsoleRenderer;
namespace SnakeGame
{
    class SnakeNode : public RenderableObject
    {
    public:
        bool filled = false;
        SnakeNode(const int &pos_x, const int &pos_y)
            : RenderableObject(pos_x, pos_y, Color::YELLOW_BKG,Color::BLACK_TXT, ' ', ' ') 
            {
                this->layer = Layer::Two;
            }

        bool operator==(const SnakeNode &second)
        {
            if (this->pos.x == second.pos.x && this->pos.y == second.pos.y)
                return true;
            else
                return false;
        }
    };
} // namespace SnakeGame