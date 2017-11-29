#ifndef _GUIBUTTON_H__ 
#define _GUIBUTTON_H__

#include "GUI.h"


class GUI_Button : public GUI
{
private:
	Animation idle;
	Animation ButtonClicked;
	Animation Mouse_on_Button;

public:
	GUI_Button(int x, int y, SDL_Rect anim);
	void Interact(int state);
};
#endif //_GUIBUTTON_H__