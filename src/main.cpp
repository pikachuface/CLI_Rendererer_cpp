#include "headerFiles/snake_game.h"
#include "headerFiles/text_box.h"
#include <iostream>
int main()
{
    ConsoleRenderer::TextBox txtbox("label", "text");
    ConsoleRenderer::Renderer *rn = new Renderer(10, 20, 2, ConsoleRenderer::Colors::WHITE_BKG);
    rn->RenderBorder();


    return 0;
}