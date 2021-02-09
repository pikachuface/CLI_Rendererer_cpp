#pragma once
//std libs
#include <map>
#include <vector>
//custom libs
#include "ansi_escapes.h"
#include "renderable_object.h"
namespace ConsoleRenderer
{
    class Renderer
    {
    private:
        const int canvas_width;
        const int canvas_height;
        const int border_thicknes = 1;
        Colors border_color = Colors::WHITE_BKG;
        std::map<const char *, char *> text_boxes;
        std::vector<RenderableObject> render_queue;

    public:
        Renderer(const int &canvas_width, const int &canvas_height);
        Renderer(const int &canvas_width, const int &canvas_height,
                 const int &border_thicknes, const Colors &border_color);
        ~Renderer();
        void AddToRenderQueue(const RenderableObject &to_render);
        bool TryAddToRenderQueue(const RenderableObject &to_render);
        void Show();
        void RenderBorder();
        void ClearCanvas();
    };
} // namespace ConsoleRenderer