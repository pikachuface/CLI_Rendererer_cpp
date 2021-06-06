#pragma once
#include <stdlib.h>
#include <time.h>
#include "../CLI_renderer_lib/renderable_object.h"
namespace SnakeGame
{
    class Food : public ConsoleRenderer::RenderableObject
    {
    public:
        const int map_width;
        const int map_height;

    private:
        int value;

    public:
        const int &GetValue();

        Food(const int &map_width, const int &map_height);
        void Respawn();
    }; // namespace SnakeGame
} // namespace SnakeGame