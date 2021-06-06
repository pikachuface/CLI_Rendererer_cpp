#pragma once
#include <string>
#include "console.h"
namespace ConsoleRenderer
{
    class TextBox
    {

    public:
        Color label_color = Color::WHITE_TXT;
        Color text_color = Color::WHITE_TXT;
        std::string label;
        std::string text;
        bool conetered = false;

    public:
        TextBox(const std::string &label, const std::string &text);

        TextBox(const std::string &label, const std::string &text,
                const Color &label_color, const Color &text_color);
    };

} // namespace ConsoleRenderer