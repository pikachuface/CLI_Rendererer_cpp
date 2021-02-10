#include "headerFiles/food.h"

namespace SnakeGame
{
    Food::Food(const int &map_width, const int &map_height)
        : map_width(map_width), map_height(map_height),
          ConsoleRenderer::RenderableObject(0, 0,
                                            ConsoleRenderer::Colors::RED_BKG,
                                            ConsoleRenderer::Colors::BLACK_TXT,
                                            '[', ']')
    {
        srand(time(NULL));
        this->Respawn();
    }

    void Food::Respawn()
    {
        this->value = rand() % 10 + 1;
        this->pos.x = rand() % this->map_width + 1;
        this->pos.y = rand() % this->map_height + 1;
    }

    const int &Food::GetValue()
    {
        return this->value;
    }

} // namespace SnakeGame