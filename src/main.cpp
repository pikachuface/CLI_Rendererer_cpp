#include "headerFiles/snake_game.h"
#include "headerFiles/text_box.h"
#include <iostream>
int main()
{
    ConsoleRenderer::AnsiEscapes::ClearScreen();
    ConsoleRenderer::Renderer *rn = new Renderer(10, 20, 2, ConsoleRenderer::Colors::WHITE_BKG);
    ConsoleRenderer::RenderableObject object(1, 1, ConsoleRenderer::Colors::RED_BKG);
    rn->TryAddToRenderQueue(object);
    rn->Init();
    object.pos.x += 4;
    rn->AddToRenderQueue(object);
    rn->Render();
    object.pos.y += 4;
    rn->AddToRenderQueue(object);
    rn->AddToDeleteQueue(1,1);
    rn->Render();
    ConsoleRenderer::AnsiEscapes::MoveCursorTo(25, 5);

    return 0;
}