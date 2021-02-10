/*You can find this code at: 
  https://github.com/sol-prog/ansi-escape-codes-windows-posix-terminals-c-programming-examples
*/
#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS 1
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "headerFiles/ansi_escapes.h"

namespace ConsoleRenderer
{


#ifdef _WIN32
// Some old MinGW/CYGWIN distributions don't define this:
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

    static HANDLE stdoutHandle, stdinHandle;
    static DWORD outModeInit, inModeInit;

    void AnsiEscapes::SetupConsole(void)
    {
        DWORD outMode = 0, inMode = 0;
        stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        stdinHandle = GetStdHandle(STD_INPUT_HANDLE);

        if (stdoutHandle == INVALID_HANDLE_VALUE || stdinHandle == INVALID_HANDLE_VALUE)
        {
            exit(GetLastError());
        }

        if (!GetConsoleMode(stdoutHandle, &outMode) || !GetConsoleMode(stdinHandle, &inMode))
        {
            exit(GetLastError());
        }

        outModeInit = outMode;
        inModeInit = inMode;

        // Enable ANSI escape codes
        outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

        // Set stdin as no echo and unbuffered
        inMode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);

        if (!SetConsoleMode(stdoutHandle, outMode) || !SetConsoleMode(stdinHandle, inMode))
        {
            exit(GetLastError());
        }
    }

    void AnsiEscapes::RestoreConsole(void)
    {
        // Reset colors
        printf("\x1b[0m");

        // Reset console mode
        if (!SetConsoleMode(stdoutHandle, outModeInit) || !SetConsoleMode(stdinHandle, inModeInit))
        {
            exit(GetLastError());
        }
    }
#else

    static struct termios orig_term;
    static struct termios new_term;

    void AnsiEscapes::SetupConsole(void)
    {
        tcgetattr(STDIN_FILENO, &orig_term);
        new_term = orig_term;

        new_term.c_lflag &= ~(ICANON | ECHO);

        tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
    }

    void AnsiEscapes::RestoreConsole(void)
    {
        // Reset colors
        printf("\x1b[0m");

        // Reset console mode
        tcsetattr(STDIN_FILENO, TCSANOW, &orig_term);
    }
#endif

    void AnsiEscapes::GetCursorPosition(int *row, int *col)
    {
        printf("\x1b[6n");
        char buff[128];
        int indx = 0;
        for (;;)
        {
            int cc = getchar();
            buff[indx] = (char)cc;
            indx++;
            if (cc == 'R')
            {
                buff[indx + 1] = '\0';
                break;
            }
        }
        sscanf(buff, "\x1b[%d;%dR", row, col);
        fseek(stdin, 0, SEEK_END);
    }
}