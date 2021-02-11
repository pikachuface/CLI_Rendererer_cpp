#include "headerFiles/snake_game.h"
#include "headerFiles/text_box.h"
#include <iostream>
int main()
{
    ConsoleRenderer::AnsiEscapes::ClearScreen();
    ConsoleRenderer::Renderer *rn = new Renderer(10, 20, 2, 3, ConsoleRenderer::Colors::WHITE_BKG);
    ConsoleRenderer::RenderableObject object(1, 1, ConsoleRenderer::Colors::RED_BKG);
    rn->TryAddToRenderQueue(object);
    rn->TryAddTextBox("msg", "Ahoj ", "jak se vede?", Colors::CYAN_TXT, Colors::RED_TXT, 2);
    rn->Init();
    object.pos.x += 4;
    rn->AddToRenderQueue(object);
    rn->Render();
    object.pos.y += 4;
    rn->AddToRenderQueue(object);
    rn->AddToDeleteQueue(1, 1);
    rn->Render();
    rn->TryRenderTextBox("karel");
    rn->TryRenderTextBox("msg");
    ConsoleRenderer::AnsiEscapes::MoveCursorTo(0, 0);
    printf("\r\n");
    ConsoleRenderer::AnsiEscapes::MoveCursorTo(35, 5);

    return 0;
}