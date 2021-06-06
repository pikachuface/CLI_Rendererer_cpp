#include <assert.h>
#include <cmath>
#include <cstring>
#include "headerFiles/renderer.h"

namespace ConsoleRenderer
{
    //(Con/De)structors
    void Renderer::Init(const uint8_t &p_canvas_width,
                        const uint8_t &p_canvas_height,
                        const uint8_t &p_text_lines)
    {
        RestartRenderer();
        canvas_width = p_canvas_width;
        canvas_height = p_canvas_height;
        text_lines = p_text_lines;
        text_boxes.resize(text_lines);
        Console::SetupConsole();
    }

    void Renderer::Init(const uint8_t &p_canvas_width,
                        const uint8_t &p_canvas_height,
                        const uint8_t &p_text_lines,
                        const uint8_t &p_border_thicknes,
                        const Color &p_border_color)
    {
        RestartRenderer();
        canvas_width = p_canvas_width;
        canvas_height = p_canvas_height;
        text_lines = p_text_lines;
        border_thicknes = border_thicknes;
        border_color = border_color;
        text_boxes.resize(text_lines);
        Console::SetupConsole();
    }

    void Renderer::RestartRenderer(void)
    {
        for (auto ptr_obj : all_objects)
            delete ptr_obj;
        for (auto ptr_txt_box : text_boxes)
            delete ptr_txt_box;
        text_boxes.clear();
        all_objects.clear();
        buffer.clear();
        text_box_finder.clear();
        border_color = WHITE_BKG;
        border_thicknes = 1;
    }

    //Setup
    void Renderer::Show(void)
    {
        ConsoleRenderer::Console::ClearScreen();
        ClearCanvas();
        RenderBorder();
        std::map<std::string, int>::iterator it;
        for (it = text_box_finder.begin(); it != text_box_finder.end(); it++)
        {
            UpdateTextBox(it->first);
        }
        Render();
    }

    //Visual
    void Renderer::ClearCanvas(void)
    {
        size_t offset_y = text_lines + border_thicknes;
        size_t offset_x = (border_thicknes * 2) + 1;
        Console::SetBackgroundColor(Color::RESET_COLOR);
        for (int y = 1; y <= canvas_height; y++)
        {
            Console::MoveCursorTo(offset_y + y, offset_x);
            for (int x = 1; x <= canvas_width; x++)
            {
                printf("  ");
            }
        }
        Console::MoveCursorTo(text_lines + border_thicknes * 2 + canvas_height + 1, 0);
    }

    void Renderer::RenderBorder(void)
    {
        Console::SetBackgroundColor(border_color);
        size_t offset_y = text_lines + 1;
        for (int y = 0; y < border_thicknes; y++)
        {
            Console::MoveCursorTo(offset_y + y, 1);
            for (int x = 0; x < canvas_width + (2 * border_thicknes); x++)
            {
                printf("  ");
            }
        }
        offset_y += border_thicknes;
        for (int y = 0; y <= canvas_height; y++)
        {
            Console::MoveCursorTo(offset_y + y, 1);
            for (int x = 0; x < border_thicknes; x++)
            {
                printf("  ");
            }
            Console::MoveCursorTo(offset_y + y, 1 + (canvas_width + border_thicknes) * 2);
            for (int x = 0; x < border_thicknes; x++)
            {
                printf("  ");
            }
        }
        offset_y += canvas_height;
        for (int y = 0; y < border_thicknes; y++)
        {
            Console::MoveCursorTo(offset_y + y, 1);
            for (int x = 0; x < canvas_width + (2 * border_thicknes); x++)
            {
                printf("%c%c", ' ', ' ');
            }
        }
        Console::MoveCursorTo(text_lines + border_thicknes * 2 + canvas_height + 1, 0);
    }

    void Renderer::Render(void)
    {
        for (auto object : all_objects)
        {
            if (InsideCanvas(object->pos))
                continue;
            if (buffer.count(object->pos) != 0)
            {
                if (buffer[object->pos]->layer >= object->layer)
                    buffer[object->pos] = object;
            }
            buffer[object->pos] = object;
        }
        ClearCanvas();
        for (auto to_render : buffer)
            DrawPixel(*to_render.second);
    }

    void Renderer::DrawPixel(const RenderableObject &to_render)
    {
        Console::MoveCursorTo(text_lines + border_thicknes + to_render.pos.y, (border_thicknes + to_render.pos.x) * 2 - 1);
        Console::SetBackgroundColorBright(to_render.bkg_color);
        Console::SetTextColor(to_render.txt_color);
        printf("%c%c", to_render.block_texture[0], to_render.block_texture[1]);
        Console::MoveCursorTo(text_lines + border_thicknes * 2 + canvas_height + 1, 0);
    }

    void Renderer::ClearPixel(const Position &to_delete)
    {
        Console::SetBackgroundColor(Color::BLACK_BKG);
        Console::MoveCursorTo(text_lines + border_thicknes + to_delete.y, (border_thicknes + to_delete.x) * 2 - 1);
        printf("  ");
        Console::MoveCursorTo(text_lines + border_thicknes * 2 + canvas_height + 1, 0);
    }

    void Renderer::UpdateTextBox(const std::string &name)
    {
        Console::SetBackgroundColor(Color::RESET_COLOR);
        Console::MoveCursorTo(text_box_finder[name] + 1, 1);
        Console::ClearLineToRight();

        TextBox *txt_box = text_boxes[text_box_finder[name]];

        int white_spaces = (border_thicknes * 2 + canvas_width) * 2 - (txt_box->label.length() + txt_box->text.length());
        if (white_spaces > 0 && txt_box->conetered)
            Console::MoveCursorTo(text_box_finder[name] + 1, white_spaces / 2 + 1);
        else
            Console::MoveCursorTo(text_box_finder[name] + 1, 1);

        Console::SetTextColor(txt_box->label_color);
        printf("%s", txt_box->label.c_str());
        Console::SetTextColor(txt_box->text_color);
        printf("%s", txt_box->text.c_str());
    }

    //TextBoxes
    const bool Renderer::TryEditTextBox(const std::string &name,
                                        const std::string &text)
    {
        if (text_box_finder.count(name) > 0)
        {
            text_boxes[text_box_finder[name]]->text = text;
            return true;
        }
        return false;
    }

    const bool Renderer::TryEditTextBox(const std::string &name,
                                        const std::string &label,
                                        const std::string &text,
                                        const Color &label_color,
                                        const Color &text_color)
    {
        if (text_box_finder.count(name) > 0)
        {
            TextBox *tmp_txt_box = text_boxes[text_box_finder[name]];
            tmp_txt_box->label = label;
            tmp_txt_box->text = text;
            tmp_txt_box->label_color = label_color;
            tmp_txt_box->text_color = text_color;
            UpdateTextBox(name);
            return true;
        }
        return false;
    }

    const bool Renderer::TryAddTextBox(const std::string &name,
                                       const std::string &label,
                                       const std::string &text,
                                       const Color &label_color,
                                       const Color &text_color)
    {
        if (text_box_finder.count(name) == 0)
        {
            for (size_t i = 0; i < text_lines; i++)
            {
                if (text_boxes[i] == nullptr)
                {
                    text_box_finder[name] = i;
                    text_boxes[i] = new TextBox(label, text, label_color, text_color);
                    return true;
                }
            }
        }
        return false;
    }

    const bool Renderer::TryAddTextBox(const std::string &name, const std::string &label,
                                       const std::string &text, const Color &label_color,
                                       const Color &text_color, const uint8_t &line)
    {
        if (text_box_finder.count(name) == 0)
        {
            text_box_finder[name] = line;
            text_boxes[line] = new TextBox(label, text, label_color, text_color);
        }
        return false;
    }

    const bool Renderer::TryDeleteTextBox(const std::string &name)
    {
        if (text_box_finder.count(name) > 0)
        {
            delete text_boxes[text_box_finder[name]];
            text_box_finder.erase(name);
            return true;
        }
        return false;
    }

    //Logic
    const bool Renderer::InsideCanvas(const Position &to_check)
    {
        if (to_check.x > canvas_width)
            return false;
        else if (to_check.y > canvas_height)
            return false;
        else if (to_check.x < 0 || to_check.y < 0)
            return false;

        return true;
    }

} // namespace ConsoleRenderer