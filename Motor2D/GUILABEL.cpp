#include "j1App.h"
#include "GUILABEL.h"
#include "SDL\include\SDL_timer.h"
#include "p2Log.h"
#include "j1GUI.h"

GUI_Label::GUI_Label(int x, int y, SDL_Rect anim) : GUI(x, y)
{
	idle.PushBack(anim);

	animation = &idle;
}
