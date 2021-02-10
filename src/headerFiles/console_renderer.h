#pragma once
//std libs
#include <map>
#include <vector>
//custom libs
#include "renderable_object.h"
#include "text_box.h"
namespace ConsoleRenderer
{
    class Renderer
    {
    private:
        const size_t canvas_width;
        const size_t canvas_height;
        const size_t border_thicknes = 1;
        Colors border_color = Colors::WHITE_BKG;
        std::map<const char *, TextBox> text_boxes;
        std::vector<const RenderableObject *> render_queue;
        std::vector<const Position *> delete_queue;

    public:
        Renderer(const size_t &canvas_width, const size_t &canvas_height);
        Renderer(const size_t &canvas_width, const size_t &canvas_height,
                 const size_t &border_thicknes, const Colors &border_color);
        ~Renderer();
        void AddToRenderQueue(const RenderableObject &to_render);
        const bool TryAddToRenderQueue(const RenderableObject &to_render);
        void AddToDeleteQueue(const int &pos_x, const int &pos_y);
        const bool TryAddToDeleteQueue(const int &pos_x, const int &pos_y);
        void Render(void);
        void Init(void);
        void ShowBorder(void);
        void ClearCanvas(void);

    private:
        const bool InsideCanvas(const Position &to_check);
        void ClearPixel(const Position &to_delete);
        void DrawPixel(const RenderableObject &to_render);
    };
} // namespace ConsoleRenderer