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

        bool operator<(const Position &B)
        {
            int a = this->x + this->y;
            int b = B.x + B.y;
            if (a < b)
                return true;
            return false;
        }
        
        bool operator>(const Position &B)
        {
            int a = this->x + this->y;
            int b = B.x + B.y;
            if (a > b)
                return true;
            return false;
        }
        
    };

} // namespace ConsoleRender