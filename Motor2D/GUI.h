#ifndef __GUI_H__
#define __GUI_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class GUI
{
protected:
	Animation* animation = nullptr;

public:
	iPoint position;
	int type;
	int id;

public:
	GUI(int x, int y);
	virtual ~GUI();

	virtual void Draw(SDL_Texture* sprites);
};

#endif // __GUI_H__