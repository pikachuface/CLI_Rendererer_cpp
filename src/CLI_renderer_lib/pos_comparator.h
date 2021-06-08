#include "position.h"
#include <functional>

namespace ConsoleRenderer
{
    class PosComparator
    {
    public:
        bool operator()(const ConsoleRenderer::Position &A, const ConsoleRenderer::Position &B) const
        {
            if (A.x < B.x)
                return true;
            else if (A.x == B.x && A.y < B.y)
                return true;
            return false;
        }
    };
}