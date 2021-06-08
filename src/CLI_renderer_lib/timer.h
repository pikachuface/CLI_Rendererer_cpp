#pragma once
#include <chrono>
namespace ConsoleRenderer
{

    class Timer
    {
    private:
        std::chrono::high_resolution_clock::time_point p1;
        std::chrono::high_resolution_clock::time_point p2;
        double delay;
        double timer;

    public:
        Timer(const double &delay) : delay(delay)
        {
            p1 = std::chrono::high_resolution_clock::now();
        }

        const bool IsDone()
        {
            timer -= TimeDelta();
            if (timer <= 0)
            {
                timer = delay;
                return true;
            }
            return false;
        }

    private:
        const double TimeDelta()
        {
            p2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> timeDelta = std::chrono::duration_cast<std::chrono::duration<double>>(p2 - p1);
            p1 = std::chrono::high_resolution_clock::now();
            return timeDelta.count();
        }
    };
}