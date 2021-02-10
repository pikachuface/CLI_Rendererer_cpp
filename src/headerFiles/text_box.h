#pragma once
#include <string>
#include "ansi_escapes.h"
namespace ConsoleRenderer
{
    class TextBox
    {

    public:
        Colors label_color = Colors::WHITE_TXT;
        Colors text_color = Colors::WHITE_TXT;
        std::string label;
        std::string text;

    public:
        TextBox(const std::string &label, const std::string &text);

        TextBox(const std::string &label, const std::string &text,
                const Colors &label_color, const Colors &text_color);
    };

} // namespace ConsoleRenderer