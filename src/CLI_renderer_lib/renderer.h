#pragma once
//custom libs
#include "console.h"
#include "renderable_object.h"
#include "text_box.h"
//std libs
#include <map>
#include <vector>
#include <unordered_set>
#include <string>
#include <array>

namespace ConsoleRenderer
{
    class Renderer
    {

    private:
        uint8_t canvas_width;
        uint8_t canvas_height;
        uint8_t border_thicknes;
        uint8_t text_lines;
        Color border_color;
        std::map<std::string, int> text_box_finder;
        std::vector<TextBox *> text_boxes;
        std::unordered_set<RenderableObject *> all_objects;
        std::map<Position *, RenderableObject *> buffer;

    public:
        Renderer(const uint8_t &canvas_width, const uint8_t &canvas_height,
                 const uint8_t &text_lines);
        Renderer(const uint8_t &canvas_width, const uint8_t &canvas_height,
                 const uint8_t &text_lines,
                 const uint8_t &border_thicknes, const Color &border_color);
        const bool TryRegisterObject(RenderableObject *object);
        const bool TryUnregisterObject(RenderableObject *object);
        const bool IsRegistered(RenderableObject *object);
        const bool TryAddTextBox(const std::string &name,
                                 const std::string &label,
                                 const std::string &text,
                                 const Color &label_color,
                                 const Color &text_color);
        const bool TryAddTextBox(const std::string &name,
                                 const std::string &label,
                                 const std::string &text,
                                 const Color &label_color,
                                 const Color &text_color,
                                 const uint8_t &line);
        const bool TryDeleteTextBox(const std::string &name);
        const bool TryEditTextBox(const std::string &name,
                                  const std::string &text);
        const bool TryEditTextBox(const std::string &name,
                                  const std::string &label,
                                  const std::string &text,
                                  const Color &label_color,
                                  const Color &text_color);
        void Render(void);
        void Show(void);
        void RenderBorder(void);
        void ClearCanvas(void);

    private:
        const bool InsideCanvas(const Position &to_check);
        void ClearPixel(const Position &to_delete);
        void DrawPixel(const RenderableObject &to_render);
        void UpdateTextBox(const std::string &name);
        void RestartRenderer(void);
        void ClearBuffer(void);
    };
} // namespace ConsoleRenderer