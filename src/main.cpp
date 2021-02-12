#include "headerFiles/snake_game.h"
#include "headerFiles/text_box.h"
#include "headerFiles/input_manager.h"
#include <iostream>
#include <limits>
#include <termios.h>

const bool TryGetInput(int &saved_input, const int &min_value, const int &max_value = INT32_MAX);
const bool checkInput();
void Setup(void);

int width = 0;
int height = 0;
int speed = 0;
bool map_loops = true;

int main()
{
    Setup();
    SnakeGame::SnakeGame game(speed, map_loops, height, width);
    AnsiEscapes::MoveCursorTo(40,5);
    return 0;
}

void Setup(void)
{

    while (true)
    {
        ConsoleRenderer::AnsiEscapes::ClearScreen();
        ConsoleRenderer::AnsiEscapes::MoveCursorTo(1, 1);

        std::cout << "Snake Game" << std::endl;
        if (width < 5)
        {
            std::cout << "Map width [min 5]: ";
            if (!TryGetInput(width, 5))
            {
                continue;
            }
        }
        if (height < 5)
        {
            std::cout << "Map height [min 5]: ";
            if (!TryGetInput(height, 5))
            {
                continue;
            }
        }
        if (speed < 1)
        {
            std::cout << "Speed [min 1][max 10] : ";
            if (!TryGetInput(speed, 1, 10))
            {
                continue;
            }
        }
        char input;
        while (true)
        {
            ConsoleRenderer::AnsiEscapes::ClearScreen();
            ConsoleRenderer::AnsiEscapes::MoveCursorTo(1, 1);
            std::cout << "Should snake loop:\nY) Yes\nN) No" << std::endl;
            input = toupper(Input::Get());
            if (input == 'Y')
            {
                map_loops = true;
                break;
            }
            else if (input == 'N')
            {
                map_loops = false;
                break;
            }
        }
        break;
    }
}

const bool checkInput(void)
{
    if (!std::cin.good())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}

const bool TryGetInput(int &saved_input, const int &min_value, const int &max_value)
{
    std::cin >> saved_input;
    std::cin.clear();
    if (!checkInput || saved_input < min_value)
    {
        saved_input = 0;
        std::cout << "Input must be a number. It's value needs to be between: "
                  << min_value << "-" << max_value << std::endl;
        Input::Get();
        return false;
    }
    return true;
}