#pragma once

namespace ConsoleRenderer
{
    class Position
    {
    public:
        int x;
        int y;

        Position(const int &pos_x, const int &pos_y)
            : x(pos_x), y(pos_y) {}
    };

} // namespace ConsoleRender