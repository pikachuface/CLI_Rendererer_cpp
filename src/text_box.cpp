#include "headerFiles/text_box.h"
namespace ConsoleRenderer
{
    //Set & Get
    const std::string& TextBox::GetText() { return this->text; }
    const std::string& TextBox::GetLabel() { return this->label; }
    void TextBox::SetText(const std::string &new_text) { this->text = new_text; }

    TextBox::TextBox(const std::string &label, const std::string &text)
    {
        this->label = label;
        this->text = text;
    }
    TextBox::TextBox(const std::string &label, const std::string &text,
                     const Colors &text_color, const Colors &label_color)
    {
        this->label = label;
        this->text = text;
        this->lable_color = label_color;
        this->text_color = text_color;
    }

} // namespace ConsoleRenderer
