#include "headerFiles/console_renderer.h"
namespace ConsoleRenderer
{
    //(Con/De)structors
    Renderer::Renderer(const size_t &canvas_width, const size_t &canvas_height)
        : canvas_height(canvas_height), canvas_width(canvas_width)
    {
        setupConsole();
    }

    Renderer::Renderer(const size_t &canvas_width, const size_t &canvas_height,
                       const size_t &border_thicknes, const Colors &border_color)
        : canvas_height(canvas_height), canvas_width(canvas_width),
          border_thicknes(border_thicknes), border_color(border_color)
    {
        setupConsole();
    }

    Renderer::~Renderer()
    {
        for (size_t i = 0; render_queue.size(); i++)
        {
            delete render_queue[i];
        }
    }

    //Setup
    void Renderer::Init(void)
    {
        ClearCanvas();
        ShowBorder();
        Render();
    }

    void Renderer::ClearCanvas(void)
    {
        size_t offset_y = text_boxes.size() + border_thicknes;
        size_t offset_x = (border_thicknes * 2) + 1;
        setBackgroundColor(Colors::RESET_COLOR);
        for (int y = 1; y <= canvas_height; y++)
        {
            moveCursorTo(offset_y + y, offset_x);
            for (int x = 1; x <= canvas_width; x++)
            {
                printf("##");
            }
        }
    }

    void Renderer::ShowBorder(void)
    {
        setBackgroundColor(border_color);
        size_t offset_y = text_boxes.size() + 1;
        for (int y = 0; y < border_thicknes; y++)
        {
            moveCursorTo(offset_y + y, 1);
            for (int x = 0; x < canvas_width + (2 * border_thicknes); x++)
            {
                printf("  ");
            }
        }
        offset_y += border_thicknes;
        for (int y = 0; y < canvas_height; y++)
        {
            moveCursorTo(offset_y + y, 1);
            for (int x = 0; x < border_thicknes; x++)
            {
                printf("  ");
            }
            moveCursorTo(offset_y + y, 1 + (canvas_width + border_thicknes) * 2);
            for (int x = 0; x < border_thicknes; x++)
            {
                printf("  ");
            }
        }
        offset_y += canvas_height;
        for (int y = 0; y < border_thicknes; y++)
        {
            moveCursorTo(offset_y + y, 1);
            for (int x = 0; x < canvas_width + (2 * border_thicknes); x++)
            {
                printf("%c%c", ' ', ' ');
            }
        }
    }

    void Renderer::Render()
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

    //Drawing Pixel
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

    void Renderer::DrawPixel(const RenderableObject &to_render)
    {
        moveCursorTo(text_boxes.size()+border_thicknes+to_render.pos.y, (border_thicknes+to_render.pos.x)*2-1);
        setBackgroundColorBright(to_render.bkg_color);
        setTextColor(to_render.txt_color);
        printf("%c%c",to_render.block_texture[0],to_render.block_texture[1]);
    }

    //Deleteting Pixel
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
    void Renderer::ClearPixel(const Position &to_delete)
    {
        setBackgroundColor(Colors::RESET_COLOR);
        moveCursorTo(text_boxes.size() + border_thicknes + to_delete.y, (border_thicknes + to_delete.y * 2) + 1);
        printf("  ");
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