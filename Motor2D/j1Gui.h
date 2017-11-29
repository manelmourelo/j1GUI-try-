#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "SDL_TTF\include\SDL_ttf.h"

#define CURSOR_WIDTH 2
#define MAX_UI_ELEMENTS 100

// TODO 1: Create your structure of classes
enum GUI_Types {
	NO_TYPE,
	BUTTON,
	LABEL,
	TEXT,
	CHECKBOX
};

class GUI;

struct GUIinfo {
	GUI_Types type = GUI_Types::NO_TYPE;
	int x, y, h, w;
	SDL_Rect anim;
	SDL_Texture* texture;
	int state;
	int num;
};
// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions
	bool AddLabel(int x, int y, SDL_Rect anim);
	bool AddText(int x, int y, p2SString text, SDL_Color color, _TTF_Font* font);
	bool AddButton(int x, int y, SDL_Rect anim, p2SString text, SDL_Color color, _TTF_Font* font);
	bool AddcheckBox();
	void buttonClicked(int button);

	const SDL_Texture* GetAtlas() const;

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;
	GUIinfo queue[MAX_UI_ELEMENTS];
	GUI* GUI_Elements[MAX_UI_ELEMENTS];
	SDL_Texture* texture_text;
	iPoint mousePosition;
	int numButtons = 0;
	int numLabels = 0;
	int numTexts = 0;

	void CreateGUI(const GUIinfo& info);
};

#endif // __j1GUI_H__