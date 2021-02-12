#include <termios.h>
#include <unistd.h>
#include <stdio.h>

class Input
{
public:
    static inline char Get()
    {
        struct termios oldattr, newattr;
        int ch;
        tcgetattr(STDIN_FILENO, &oldattr);
        newattr = oldattr;
        newattr.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
        char input = static_cast<char>(ch);
        return input;
    }
};
