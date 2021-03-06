#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1Scene.h"
#include "j1Fonts.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	if(App->map->Load("iso_walk.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if(App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	debug_tex = App->tex->Load("maps/path2.png");

	// TODO 3: Create the banner (rect {485, 829, 328, 103}) and the text "Hello World"

	//Background
	label1 = App->gui->AddLabel(0, 0, { 799, 23, 1024, 768 },NULL,this);
	label2 = App->gui->AddLabel(40, 30, { 52, 387, 150, 150 }, NULL, this);
	label3 = App->gui->AddLabel(310 ,23, { 362, 336, 367, 89 }, NULL, this);
	label4 = App->gui->AddLabel(700,400, { 408, 484, 201, 236 }, NULL, this);
	text_menu = App->gui->AddText(440, 45, "MENU", { 255,255,255 }, App->font->default, NULL, this);
	text_history = App->gui->AddText(50, 230, "       This is the", { 255,255,255 },App->font->default,NULL,this);
	text_history2 = App->gui->AddText(50, 270, "  beginning of a", { 255,255,255 }, App->font->default, NULL, this);
	text_history3 = App->gui->AddText(50, 310, "great adventure", { 255,255,255 }, App->font->default, NULL, this);
	 //WOW Logo
//	App->gui->AddLabel(46, 36, { 1962, 311, 254, 99 },NULL,this);
	//ESRB
//	App->gui->AddLabel(36, 960, { 2046, 724, 128, 40 },NULL,this);
	//Blizzard Logo
//	App->gui->AddLabel(871, 958, { 1985, 66, 128, 78 },NULL,this);

	////Account name
	//App->gui->AddText(870, 522, "Account Name", { 255,255,0 }, App->font->default, NULL, this);
	////Account Password
	//App->gui->AddText(845, 625, "Account Password", { 255,255,0 }, App->font->default);
	////WoWps.org TBC
	//App->gui->AddText(1701, 889, "WoWps.org TBC", { 59,59,59 }, App->font->default);
	////Version 2.0.12 (6546) (Release)
	//App->gui->AddText(5, 1000, "Version 2.0.12 (6546) (Release)", { 255,255,0 }, App->font->default);
	////Mar 30 2007
	//App->gui->AddText(5, 1024, "Mar 30 2007", { 255,255,0 }, App->font->default);
	////Copyright 2004-2007  Blizzard Entertainment. All Rights Reserved.
	//App->gui->AddText(567, 1024, "Copyright 2004-2007  Blizzard Entertainment. All Rights Reserved.", { 255,255,0 }, App->font->default);

	////ManageAccountButton
	//App->gui->AddButton(35, 813, { 2273,538,167,45 }, "Manage Account", { 255,255,0 }, App->font->default);
	////CommunitySide button
	//App->gui->AddButton(35, 868, { 2273,538,167,45 }, "Community Side", { 255,255,0 }, App->font->default);
	////Login Button
	//App->gui->AddButton(837, 741, { 2273,538,167,45 }, "Login", { 255,255,0 }, App->font->default);
	////Cinematics Button
	//App->gui->AddButton(1646, 728, { 2273,538,167,45 }, "Cinematics", { 255,255,0 }, App->font->default);
	////Credits Button
	//App->gui->AddButton(1646, 780, { 2273,538,167,45 }, "Credits", { 255,255,0 }, App->font->default);
	////TermsOfUse Button
	//App->gui->AddButton(1646, 833, { 2273,538,167,45 }, "Terms of Use", { 255,255,0 }, App->font->default);
	////Quit Button
	//App->gui->AddButton(1646, 997, { 2273,538,167,45 }, "Quit", { 255,255,0 }, App->font->default);
	// App->gui->AddText(100, 100, "Wizard's power", { 255,255,0 }, App->font->default,NULL,this);
	//App->gui->AddLabel(200, 100, { 332,298,468,302 }, NULL, this);
	button_start = App->gui->AddButton(400, 150, { 0,4,182,56 }, "Play", { 255,255,255 }, App->font->default, NULL,this);
	button_continue = App->gui->AddButton(400, 220, { 0,0,182,56 }, "Continue", { 255,255,255 }, App->font->default, NULL, this);
	button_settings = App->gui->AddButton(400, 290, { 0,0,182,56 }, "Settings", { 255,255,255}, App->font->default, NULL, this);
	button_credits = App->gui->AddButton(400, 360, { 0,0,182,56 }, "Credits", { 255,255,255 }, App->font->default, NULL, this);
	button_exit = App->gui->AddButton(400, 430, { 0,0,182,56 }, "Exit", { 255,255,255 }, App->font->default, NULL, this);
	
	
//	App->gui->AddLabel(455, 50, { 255,341,461,237 }, NULL, this);
	//App->gui->AddButton(200, 150, { 642,169,229,69 }, "3", { 255,255,0 }, App->font->default, NULL, this);
	//App->gui->AddButton(450, 150, { 642,169,229,69 }, "EXIT GAME", { 255,255,0 }, App->font->default, NULL, this);

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{

	// debug pathfing ------------------
	static iPoint origin;
	static bool origin_selected = false;

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);

	if(App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if(origin_selected == true)
		{
			App->pathfinding->CreatePath(origin, p);
			origin_selected = false;
		}
		else
		{
			origin = p;
			origin_selected = true;
		}
	}

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	bool ret = true;
	if (close == true)
	{
		ret = false;
	}
	// Gui ---
	
	// -------
	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= floor(200.0f * dt);

	//App->map->Draw();

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count(),
					map_coordinates.x, map_coordinates.y);

	//App->win->SetTitle(title.GetString());

	// Debug pathfinding ------------------------------
	//int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);
	p = App->map->MapToWorld(p.x, p.y);

	App->render->Blit(debug_tex, p.x, p.y);

	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

	for(uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		App->render->Blit(debug_tex, pos.x, pos.y);
	}

	return ret;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void j1Scene::GUIInteract(GUI* g)
{
	LOG("HIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII");
	if (g == button_start)
	{

	}
	if (g == button_continue)
	{

	}
	if (g == button_settings)
	{

	}
	if (g == button_credits)
	{

	}
	if (g == button_exit )
	{
		LOG("HIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII");
		close = true;
	}
}
