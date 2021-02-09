#pragma once
#include <string>
#include "ansi_escapes.h"
namespace ConsoleRenderer
{
    class TextBox
    {

    public:
        Colors lable_color = Colors::WHITE_TXT;
        Colors text_color = Colors::WHITE_TXT;

    private:
        std::string label;
        std::string text;

    public:
        const std::string &GetText();
        const std::string &GetLabel();
        void SetText(const std::string &new_text);
        TextBox(const std::string &label, const std::string &text);

        TextBox(const std::string &label, const std::string &text,
                const Colors &text_color, const Colors &label_color);
    };

} // namespace ConsoleRenderer