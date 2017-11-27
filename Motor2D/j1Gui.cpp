#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "GUI.h"
#include "GUILABEL.h"
#include "GUITEXT.h"



j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i)
	{
		if (queue[i].type != GUI_Types::NO_TYPE)
		{
			CreateGUI(queue[i]);
			queue[i].type = GUI_Types::NO_TYPE;
		}
	}
	return true;
}

bool j1Gui::Update(float dt)
{
	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i) {
		if (GUI_Elements[i] != nullptr) {
			GUI_Elements[i]->Draw(queue[i].texture);
		}
	}
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i)
	{
		if (GUI_Elements[i] != nullptr)
		{
			delete GUI_Elements[i];
			GUI_Elements[i] = nullptr;
		}
		queue[i].type = NO_TYPE;
	}

	return true;
}

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

void j1Gui::CreateGUI(const GUIinfo& info) {
	uint i = 0;
	for (; GUI_Elements[i] != nullptr && i < MAX_UI_ELEMENTS; ++i);

	if (i != MAX_UI_ELEMENTS)
	{
		switch (info.type)
		{
		case GUI_Types::BUTTON:
			//GUI_Elements[i] = new Enemy_gargoyle(info.x, info.y);
			break;
		case GUI_Types::LABEL:
			GUI_Elements[i] = new GUI_Label(info.x, info.y, info.anim);
			break;
		case GUI_Types::TEXT:
			GUI_Elements[i] = new GUI_Text(info.x, info.y, info.anim);
			break;
		case GUI_Types::CHECKBOX:
			//GUI_Elements[i] = new Enemy_Boss(info.x, info.y);
			break;
		}
	}
}

bool j1Gui::AddLabel(int x, int y, SDL_Rect anim) {
	bool ret = false;

	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i)
	{
		if (queue[i].type == GUI_Types::NO_TYPE)
		{
			queue[i].type = LABEL;
			queue[i].x = x;
			queue[i].y = y;
			queue[i].anim = anim;
			queue[i].texture = atlas;
			ret = true;
			break;
		}
	}
	return ret;
}

bool j1Gui::AddText(int x, int y, p2SString text, SDL_Color color, _TTF_Font* font) {
	bool ret = true;
	int w=0, h=0;
	App->font->CalcSize(text.GetString(), w, h, App->font->default);
	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i)
	{
		if (queue[i].type == GUI_Types::NO_TYPE)
		{
			queue[i].type = TEXT;
			queue[i].x = x;
			queue[i].y = y;
			queue[i].anim = {0,0,w,h};
			queue[i].texture = App->font->Print(text.GetString(), color, font);
			ret = true;
			break;
		}
	}

	return ret;
}
bool j1Gui::AddButton() {
	return true;
}
bool j1Gui::AddcheckBox() {
	return true;
}

