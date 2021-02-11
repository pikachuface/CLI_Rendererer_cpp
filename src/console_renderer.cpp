#include "headerFiles/console_renderer.h"
namespace ConsoleRenderer
{
    //(Con/De)structors
    Renderer::Renderer(const size_t &canvas_width,
                       const size_t &canvas_height,
                       const size_t &text_lines)
        : canvas_height(canvas_height), canvas_width(canvas_width),
          text_lines(text_lines)
    {
        AnsiEscapes::SetupConsole();
        text_boxes.resize(text_lines);
    }

    Renderer::Renderer(const size_t &canvas_width,
                       const size_t &canvas_height,
                       const size_t &text_lines,
                       const size_t &border_thicknes,
                       const Colors &border_color)
        : canvas_height(canvas_height),
          canvas_width(canvas_width),
          text_lines(text_lines),
          border_thicknes(border_thicknes),
          border_color(border_color)
    {
        AnsiEscapes::SetupConsole();
        text_boxes.resize(text_lines);
    }

    Renderer::~Renderer()
    {
        for (size_t i = 0; render_queue.size(); i++)
        {
            delete render_queue[i];
        }
        for (size_t i = 0; delete_queue.size(); i++)
        {
            delete delete_queue[i];
        }
        for (size_t i = 0; text_boxes.size(); i++)
        {
            delete text_boxes[i];
        }
    }

    //Setup
    void Renderer::Init(void)
    {
        ClearCanvas();
        ShowBorder();
        std::map<std::string, int>::iterator it;
        for (it = text_box_finder.begin(); it != text_box_finder.end(); it++)
        {
            TryRenderTextBox(it->first);
        }
        Render();
    }

    //Visual
    void Renderer::ClearCanvas(void)
    {
        size_t offset_y = text_lines + border_thicknes;
        size_t offset_x = (border_thicknes * 2) + 1;
        AnsiEscapes::SetBackgroundColor(Colors::RESET_COLOR);
        for (int y = 1; y <= canvas_height; y++)
        {
            AnsiEscapes::MoveCursorTo(offset_y + y, offset_x);
            for (int x = 1; x <= canvas_width; x++)
            {
                printf("  ");
            }
        }
    }

    void Renderer::ShowBorder(void)
    {
        AnsiEscapes::SetBackgroundColor(border_color);
        size_t offset_y = text_lines + 1;
        for (int y = 0; y < border_thicknes; y++)
        {
            AnsiEscapes::MoveCursorTo(offset_y + y, 1);
            for (int x = 0; x < canvas_width + (2 * border_thicknes); x++)
            {
                printf("  ");
            }
        }
        offset_y += border_thicknes;
        for (int y = 0; y < canvas_height; y++)
        {
            AnsiEscapes::MoveCursorTo(offset_y + y, 1);
            for (int x = 0; x < border_thicknes; x++)
            {
                printf("  ");
            }
            AnsiEscapes::MoveCursorTo(offset_y + y, 1 + (canvas_width + border_thicknes) * 2);
            for (int x = 0; x < border_thicknes; x++)
            {
                printf("  ");
            }
        }
        offset_y += canvas_height;
        for (int y = 0; y < border_thicknes; y++)
        {
            AnsiEscapes::MoveCursorTo(offset_y + y, 1);
            for (int x = 0; x < canvas_width + (2 * border_thicknes); x++)
            {
                printf("%c%c", ' ', ' ');
            }
        }
    }

    void Renderer::Render(void)
    {
        for (int i = 0; i < delete_queue.size(); i++)
        {
            ClearPixel(*delete_queue[i]);
            delete delete_queue[i];
        }
        delete_queue.clear();
        for (int i = 0; i < render_queue.size(); i++)
        {
            DrawPixel(*render_queue[i]);
            //delete render_queue[i];
        }
        render_queue.clear();
    }

    void Renderer::DrawPixel(const RenderableObject &to_render)
    {
        AnsiEscapes::MoveCursorTo(text_lines + border_thicknes + to_render.pos.y, (border_thicknes + to_render.pos.x) * 2 - 1);
        AnsiEscapes::SetBackgroundColorBright(to_render.bkg_color);
        AnsiEscapes::SetTextColor(to_render.txt_color);
        printf("%c%c", to_render.block_texture[0], to_render.block_texture[1]);
    }

    void Renderer::ClearPixel(const Position &to_delete)
    {
        AnsiEscapes::SetBackgroundColor(Colors::RESET_COLOR);
        AnsiEscapes::MoveCursorTo(text_lines + border_thicknes + to_delete.y, (border_thicknes + to_delete.y) * 2 - 1);
        printf("  ");
    }

    const bool Renderer::TryRenderTextBox(const std::string &name)
    {
        if (text_box_finder.count(name) > 0)
        {
            TextBox *txt_box = text_boxes[text_box_finder[name]];
            AnsiEscapes::SetBackgroundColor(Colors::RESET_COLOR);
            int white_spaces = (border_thicknes * 2 + canvas_width) * 2 - (txt_box->label.length() + txt_box->text.length());
            if (white_spaces > 0)
                AnsiEscapes::MoveCursorTo(text_box_finder[name], white_spaces / 2 + 1);
            else
                AnsiEscapes::MoveCursorTo(text_box_finder[name], 1);

            AnsiEscapes::SetTextColor(txt_box->label_color);
            printf("%s", txt_box->label.c_str());
            AnsiEscapes::SetTextColor(txt_box->text_color);
            printf("%s", txt_box->text.c_str());
            return true;
        }
        return false;
    }

    //Queues
    void Renderer::AddToRenderQueue(const RenderableObject &to_render)
    {
        render_queue.push_back(&to_render);
    }

    const bool Renderer::TryAddToRenderQueue(const RenderableObject &to_render)
    {
        if (InsideCanvas(to_render.pos))
            render_queue.push_back(&to_render);
        return true;
    }

    void Renderer::AddToDeleteQueue(const int &pos_x, const int &pos_y)
    {
        Position *to_delete = new Position(pos_x, pos_y);
        if (InsideCanvas(*to_delete))
        {
            delete_queue.push_back(to_delete);
        }
        else
            delete to_delete;
    }

    const bool Renderer::TryAddToDeleteQueue(const int &pos_x, const int &pos_y)
    {
        Position *to_delete = new Position(pos_x, pos_y);
        if (InsideCanvas(*to_delete))
        {
            delete_queue.push_back(to_delete);
            return true;
        }
        else
        {
            delete to_delete;
            return false;
        }
    }

    //TextBoxes
    TextBox *const Renderer::GetTextBox(const std::string &name)
    {
        if (text_box_finder.count(name) > 0)
        {
            return text_boxes[text_box_finder[name]];
        }
        return nullptr;
    }

    const bool Renderer::TryAddTextBox(const std::string &name, const std::string &label,
                                       const std::string &text, const Colors &label_color,
                                       const Colors &text_color)
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
                                       const std::string &text, const Colors &label_color,
                                       const Colors &text_color, const size_t &line)
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