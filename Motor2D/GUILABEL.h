#ifndef _GUILABEL_H__ 
#define _GUILABEL_H__

#include "GUI.h"


class GUI_Label : public GUI
{
private:
	Animation idle;

public:
	GUI_Label(int x, int y, SDL_Rect anim);
};
#endif //_GUILABEL_H__