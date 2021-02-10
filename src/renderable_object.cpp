#include "headerFiles/renderable_object.h"
namespace ConsoleRenderer
{
    RenderableObject::RenderableObject(const int &pos_x, const int &pos_y,
                                       const Colors &bkg_color,
                                       const Colors &txt_color,
                                       const char &left_char, const char &right_char)
        : pos(pos_x,pos_y), bkg_color(bkg_color), txt_color(txt_color)
    {
        this->block_texture[0] = left_char;
        this->block_texture[1] = right_char;
    }
    RenderableObject::RenderableObject(const int &pos_x,
                                       const int &pos_y,
                                       const Colors &bkg_color)
        : pos(pos_x,pos_y), bkg_color(bkg_color) {}
} // namespace ConsoleRenderer