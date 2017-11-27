#include "j1App.h"
#include "j1Render.h"
#include "GUI.h"

GUI::GUI(int x, int y) : position(x, y)
{
}

GUI::~GUI()
{
}



void GUI::Draw(SDL_Texture* sprites)
{
	App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
}