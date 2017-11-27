#ifndef _GUITEXT_H__ 
#define _GUITEXT_H__

#include "GUI.h"


class GUI_Text : public GUI
{
private:
	Animation idle;

public:
	GUI_Text(int x, int y, SDL_Rect anim);
};
#endif //_GUITEXT_H__