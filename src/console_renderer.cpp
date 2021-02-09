#include "headerFiles/console_renderer.h"
namespace ConsoleRenderer
{
    Renderer::Renderer(const int &canvas_width, const int &canvas_height)
        : canvas_height(canvas_height), canvas_width(canvas_width)
    {
        setupConsole();
    }

    Renderer::Renderer(const int &canvas_width, const int &canvas_height,
                       const int &border_thicknes, const Colors &border_color)
        : canvas_height(canvas_height), canvas_width(canvas_width),
          border_thicknes(border_thicknes), border_color(border_color)
    {
        setupConsole();
    }
    Renderer::~Renderer()
    {
    }

    void Renderer::Show()
    {
    }

    void Renderer::ClearCanvas()
    {
    }

    void Renderer::RenderBorder()
    {
        setBackgroundColor(border_color);
        int offset = text_boxes.size() + 1;
        for (int y = 0; y < border_thicknes; y++)
        {
            moveCursorTo(offset + y, 1);
            for (int x = 0; x < canvas_width + (2 * border_thicknes); x++)
            {
                printf("%c%c", ' ', ' ');
            }
        }
        offset += border_thicknes;
        for (int y = 0; y < canvas_height; y++)
        {
            moveCursorTo(offset + y, 1);
            for (int x = 0; x < border_thicknes; x++)
            {
                printf("%c%c", ' ', ' ');
            }
            moveCursorTo(offset + y, 1 + (canvas_width + border_thicknes) * 2);
            for (int x = 0; x < border_thicknes; x++)
            {
                printf("%c%c", ' ', ' ');
            }
        }
        offset += canvas_height;
        for (int y = 0; y < border_thicknes; y++)
        {
            moveCursorTo(offset + y, 1);
            for (int x = 0; x < canvas_width + (2 * border_thicknes); x++)
            {
                printf("%c%c", ' ', ' ');
            }
        }
    } // namespace ConsoleRenderer

    void Renderer::AddToRenderQueue(const RenderableObject &to_render)
    {
    }

} // namespace ConsoleRenderer