#pragma once
//std libs
#include <map>
#include <vector>
#include <unordered_set>
#include <string>
#include <array>

//custom libs
#include "console.h"
#include "renderable_object.h"
#include "text_box.h"
namespace ConsoleRenderer
{
    class Renderer
    {
        friend class RenderableObject;

    private:
        static uint8_t canvas_width;
        static uint8_t canvas_height;
        static uint8_t border_thicknes;
        static uint8_t text_lines;
        static Color border_color;
        static std::map<std::string, int> text_box_finder;
        static std::vector<TextBox *> text_boxes;
        static std::unordered_set<RenderableObject *> all_objects;
        static std::map<Position, RenderableObject *> buffer;

    public:
        static void Init(const uint8_t &canvas_width, const uint8_t &canvas_height,
                         const uint8_t &text_lines);
        static void Init(const uint8_t &canvas_width, const uint8_t &canvas_height,
                         const uint8_t &text_lines,
                         const uint8_t &border_thicknes, const Color &border_color);
        static const bool TryAddTextBox(const std::string &name,
                                        const std::string &label,
                                        const std::string &text,
                                        const Color &label_color,
                                        const Color &text_color);
        static const bool TryAddTextBox(const std::string &name,
                                        const std::string &label,
                                        const std::string &text,
                                        const Color &label_color,
                                        const Color &text_color,
                                        const uint8_t &line);
        static const bool TryDeleteTextBox(const std::string &name);
        static const bool TryEditTextBox(const std::string &name,
                                         const std::string &text);
        static const bool TryEditTextBox(const std::string &name,
                                         const std::string &label,
                                         const std::string &text,
                                         const Color &label_color,
                                         const Color &text_color);
        static void Render(void);
        static void Show(void);
        static void RenderBorder(void);
        static void ClearCanvas(void);

    private:
        static const bool InsideCanvas(const Position &to_check);
        static void ClearPixel(const Position &to_delete);
        static void DrawPixel(const RenderableObject &to_render);
        static void UpdateTextBox(const std::string &name);
        static void RestartRenderer(void);
        static void ClearBuffer(void);
    };
} // namespace ConsoleRenderer