#pragma once
//std libs
#include <map>
#include <vector>
#include <string>
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
        const size_t text_lines;
        Colors border_color = Colors::WHITE_BKG;
        std::map<std::string, int> text_box_finder;
        std::vector<TextBox *> text_boxes;
        std::vector<const RenderableObject *> render_queue;
        std::vector<const Position *> delete_queue;

    public:
        Renderer(const size_t &canvas_width, const size_t &canvas_height,
                 const size_t &text_lines);
        Renderer(const size_t &canvas_width, const size_t &canvas_height,
                 const size_t &text_lines,
                 const size_t &border_thicknes, const Colors &border_color);
        ~Renderer();
        void AddToRenderQueue(const RenderableObject &to_render);
        const bool TryAddToRenderQueue(const RenderableObject &to_render);
        void AddToDeleteQueue(const int &pos_x, const int &pos_y);
        const bool TryAddToDeleteQueue(const int &pos_x, const int &pos_y);
        const bool TryAddTextBox(const std::string &name,
                                 const std::string &label,
                                 const std::string &text,
                                 const Colors &label_color,
                                 const Colors &text_color);
        const bool TryDeleteTextBox(const std::string &name);                                 
        TextBox *const GetTextBox(const std::string &name);
        void UpdateTextBox(const std::string &name);
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