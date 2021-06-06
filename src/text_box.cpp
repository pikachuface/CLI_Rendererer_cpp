#include "headerFiles/text_box.h"
namespace ConsoleRenderer
{
    TextBox::TextBox(const std::string &label, const std::string &text)
        : label(label), text(text) {}
    TextBox::TextBox(const std::string &label, const std::string &text,
                     const Color &label_color, const Color &text_color)
        : label(label), text(text), label_color(label_color), text_color(text_color) {}



} // namespace ConsoleRenderer
