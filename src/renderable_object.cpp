#include "headerFiles/renderable_object.h"
namespace ConsoleRenderer
{
    RenderableObject::RenderableObject(const int &pos_x, const int &pos_y,
                                       const Color &bkg_color,
                                       const Color &txt_color,
                                       const char &left_char, const char &right_char)
        : pos(pos_x, pos_y), bkg_color(bkg_color), txt_color(txt_color)
    {
        this->block_texture[0] = left_char;
        this->block_texture[1] = right_char;
        renderer->all_objects.insert(this);
    }
    RenderableObject::RenderableObject(const int &pos_x,
                                       const int &pos_y,
                                       const Color &bkg_color)
        : pos(pos_x, pos_y), bkg_color(bkg_color)
    {
        bool *out;
        renderer->all_objects.insert(this);
    }

    RenderableObject::~RenderableObject(void)
    {
        renderer->all_objects.erase(this);
    }

    const bool RenderableObject::MoveTo(const int &x, const int &y)
    {
        this->pos.x = x;
        this->pos.y = y;
    }
    const bool RenderableObject::MoveBy(const int &x, const int &y)
    {
        this->pos.x += x;
        this->pos.y += y;
    }

    void RenderableObject::SetTexture(const char &left, const char &right)
    {
        this->block_texture[0] = left;
        this->block_texture[1] = right;
    }

} // namespace ConsoleRenderer
