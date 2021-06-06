#pragma once

#include <stdio.h>

namespace ConsoleRenderer
{
#ifdef _WIN32
//TODO: Windows implementation
#else
    enum Color
    {
        RESET_COLOR,
        BLACK_TXT = 30,
        RED_TXT,
        GREEN_TXT,
        YELLOW_TXT,
        BLUE_TXT,
        MAGENTA_TXT,
        CYAN_TXT,
        WHITE_TXT,

        BLACK_BKG = 40,
        RED_BKG,
        GREEN_BKG,
        YELLOW_BKG,
        BLUE_BKG,
        MAGENTA_BKG,
        CYAN_BKG,
        WHITE_BKG
    };

    enum ClearCodes
    {
        CLEAR_FROM_CURSOR_TO_END,
        CLEAR_FROM_CURSOR_TO_BEGIN,
        CLEAR_ALL
    };
    
    class Console
    {
    public:
        static void SetupConsole(void);
        static void RestoreConsole(void);
        static void GetCursorPosition(int *row, int *col);

        static inline void SetTextColor(int code)
        {
            printf("\x1b[%dm", code);
        }

        static inline void SetTextColorBright(int code)
        {
            printf("\x1b[%d;1m", code);
        }

        static inline void SetBackgroundColor(int code)
        {
            printf("\x1b[%dm", code);
        }

        static inline void SetBackgroundColorBright(int code)
        {
            printf("\x1b[%d;1m", code);
        }

        static inline void ResetColor(void)
        {
            printf("\x1b[%dm", RESET_COLOR);
        }

        static inline void ClearScreen(void)
        {
            printf("\x1b[%dJ", CLEAR_ALL);
        }

        static inline void ClearScreenToBottom(void)
        {
            printf("\x1b[%dJ", CLEAR_FROM_CURSOR_TO_END);
        }

        static inline void ClearScreenToTop(void)
        {
            printf("\x1b[%dJ", CLEAR_FROM_CURSOR_TO_BEGIN);
        }

        static inline void ClearLine(void)
        {
            printf("\x1b[%dK", CLEAR_ALL);
        }

        static inline void ClearLineToRight(void)
        {
            printf("\x1b[%dK", CLEAR_FROM_CURSOR_TO_END);
        }

        static inline void ClearLineToLeft(void)
        {
            printf("\x1b[%dK", CLEAR_FROM_CURSOR_TO_BEGIN);
        }

        static inline void MoveUp(int positions)
        {
            printf("\x1b[%dA", positions);
        }

        static inline void MoveDown(int positions)
        {
            printf("\x1b[%dB", positions);
        }

        static inline void MoveRight(int positions)
        {
            printf("\x1b[%dC", positions);
        }

        static inline void MoveLeft(int positions)
        {
            printf("\x1b[%dD", positions);
        }

        static inline void MoveCursorTo(int row, int col)
        {
            printf("\x1b[%d;%df", row, col);
        }

        static inline void SaveCursorPosition(void)
        {
            printf("\x1b%d", 7);
        }

        static inline void RestoreCursorPosition(void)
        {
            printf("\x1b%d", 8);
        }
    };

#endif
} // namespace ConsoleRenderer