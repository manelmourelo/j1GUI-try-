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
#include "GUIBUTTON.h"
#include "j1Scene.h"



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

	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i) {
		if (GUI_Elements[i] != nullptr) {
			GUI_Elements[i]->Interact(queue[i].state);
		}
	}

	return true;
}

bool j1Gui::Update(float dt)
{
	App->input->GetMousePosition(mousePosition.x, mousePosition.y);

	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i) {
		if (GUI_Elements[i] != nullptr) {
			GUI_Elements[i]->Draw(queue[i].texture);
		}
	}

	//if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN) {
	//	if (buttonsIterator == 0) {
	//		queue[buttons[buttonsIterator]].state = 1;
	//		buttonsIterator++;
	//	}
	//	else {
	//		queue[buttons[buttonsIterator]].state = 0;
	//		queue[buttons[buttonsIterator]].state = 1;
	//		buttonsIterator++;
	//		if (buttonsIterator == numButtons) {
	//			buttonsIterator = 0;
	//		}
	//	}
	//}

	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i) {
		if (GUI_Elements[i] != nullptr) {
			if (mousePosition.x>queue[i].x && mousePosition.x<queue[i].x+ queue[i].w && mousePosition.y>queue[i].y && mousePosition.y<queue[i].y + queue[i].h) {
				LOG("MouseIsOnButton %i", queue[i].num);
				if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
					queue[i].state = 2;
					buttonClicked(queue[i].num);
				}
				else {
					queue[i].state = 1;
				}
			}
			else {
				queue[i].state = 0;
			}
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
			GUI_Elements[i] = new GUI_Button(info.x, info.y, info.anim);
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

GUI* j1Gui::AddLabel(int x, int y, SDL_Rect anim, GUI* father) {
	GUI* ret = nullptr;

	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i)
	{
		if (queue[i].type == GUI_Types::NO_TYPE)
		{
			queue[i].type = LABEL;
			if (father != NULL) {
				queue[i].x = father->position.x + x;
				queue[i].y = father->position.y + y;
			}
			else {
				queue[i].x = x;
				queue[i].y = y;
			}
			queue[i].w = anim.w;
			queue[i].h = anim.h;
			queue[i].num = numLabels;
			queue[i].anim = anim;
			queue[i].texture = atlas;
			queue[i].father = father;
			numLabels++;
			ret = GUI_Elements[i];
			break;
		}
	}
	return ret;
}

GUI* j1Gui::AddText(int x, int y, p2SString text, SDL_Color color, _TTF_Font* font, GUI* father) {
	GUI* ret = nullptr;
	int w=0, h=0;
	App->font->CalcSize(text.GetString(), w, h, App->font->default);
	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i)
	{
		if (queue[i].type == GUI_Types::NO_TYPE)
		{
			queue[i].type = TEXT;
			if (father != NULL) {
				queue[i].x = father->position.x + x;
				queue[i].y = father->position.y + y;
			}
			else {
				queue[i].x = x;
				queue[i].y = y;
			}
			queue[i].w = w;
			queue[i].h = h;
			queue[i].num = numTexts;
			queue[i].anim = {0,0,w,h};
			queue[i].texture = App->font->Print(text.GetString(), color, font);
			queue[i].father = father;
			numTexts++;
			ret = GUI_Elements[i];
			break;
		}
	}

	return ret;
}
GUI* j1Gui::AddButton(int x, int y, SDL_Rect anim, p2SString text, SDL_Color color, _TTF_Font* font, GUI* father) {
	GUI* ret = nullptr;
	int text_w = 0, text_h = 0;
	App->font->CalcSize(text.GetString(), text_w, text_h, App->font->default);
	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i)
	{
		if (queue[i].type == GUI_Types::NO_TYPE)
		{
			queue[i].type = BUTTON;
			if (father != NULL) {
				queue[i].x = father->position.x + x;
				queue[i].y = father->position.y + y;
			}
			else {
				queue[i].x = x;
				queue[i].y = y;
			}
			queue[i].w = anim.w;
			queue[i].h = anim.h;
			queue[i].num = numButtons;
			queue[i].anim = anim;
			queue[i].texture = atlas;
			queue[i].state = 0;
			queue[i].father = father;
			ret = GUI_Elements[i];
			for (uint j = 0; j < numButtons; j++) {
				buttons[j] = i;
				break;
			}
			numButtons++;
			break;
		}
	}
	if(text!=NULL){
		App->gui->AddText(x + (anim.w / 2) - (text_w / 2), y + (anim.h / 2) - (text_h / 2), text, color, font, GUI_Elements[numButtons-1]);
	}
	return ret;
}
//GUI* j1Gui::AddcheckBox() {
//	return true;
//}

void j1Gui::buttonClicked(int button) {
	App->scene->buttonClicked = button+1;
}

