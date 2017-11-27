#include "j1App.h"
#include "GUITEXT.h"
#include "SDL\include\SDL_timer.h"
#include "p2Log.h"
#include "j1GUI.h"

GUI_Text::GUI_Text(int x, int y, SDL_Rect anim) : GUI(x, y)
{
	idle.PushBack(anim);
	
	animation = &idle;
}
