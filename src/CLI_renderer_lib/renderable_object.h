#pragma once
#include "console.h"
#include "position.h"
#include "layers.h"
namespace ConsoleRenderer
{
    
    class RenderableObject
    {
    public:
        bool visible = true;
        Layer layer = Layer::One;
        Position pos;
        Color bkg_color;
        Color txt_color = Color::WHITE_TXT;
        char block_texture[2] = {' ', ' '};

        //Constructors
        RenderableObject(const int &pos_x, const int &pos_y,
                         const Color &bkg_color);
        RenderableObject(const int &pos_x, const int &pos_y,
                         const Color &bkg_color, const Color &txt_color,
                         const char &left_char, const char &right_char);
        //Setters
        void MoveBy(const int &x, const int &y);
        void MoveTo(const int &x, const int &y);
        void SetTexture(const char &left, const char &right);
    };

} // namespace ConsoleRenderer