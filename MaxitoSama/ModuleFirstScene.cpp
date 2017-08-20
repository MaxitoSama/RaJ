#include "Globals.h"
#include <time.h>
#include <stdlib.h>  
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFirstScene.h"
#include "Menu.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModuleElements1.h"
#include "UI.h"


ModuleFirstScene::ModuleFirstScene()
{}

ModuleFirstScene::~ModuleFirstScene()
{}

// Load assets
bool ModuleFirstScene::Start()
{
	LOG("Loading Background Map 1");
	Background_Map = App->textures->Load("assets/Background_Map_1.png");

	LOG("Loading Player Module");
	App->player->Enable();

	LOG("Loading Colliders Module");
	App->collision->Enable();

	LOG("Loading user interface");
	App->ui->Enable();

	LOG("Loading Music Module and track");
	App->music->Enable();
	Volum = 8;
	music=App->music->Load("assets/Time_2.ogg");

	LOG("Loading the enemies");
	App->enemies->Enable();

	

	//COLLIDERS-------------------------------------------------------------------
	App->collision->AddCollider({ 0,285,1000,10}, COLLIDER_FLOOR);
	App->collision->AddCollider({ 500,230,1000,10 }, COLLIDER_FLOOR);

	//ENEMIES---------------------------------------------------------------------
	App->enemies->AddEnemy(ROBOT_MAN, 300, 215);

	//MUSIC PLAY
	LOG("HOli");
	Mix_PlayMusic(music, 100);
	

	return true;
}

// UnLoad assets
bool ModuleFirstScene::CleanUp()
{
	LOG("Unloading Background Map 1");
	App->textures->Unload(Background_Map);

	LOG("Unloading Player Module");
	App->player->Disable();

	LOG("Unloading Colliders Module");
	App->collision->Disable();
	
	LOG("Unloading user interface");
	App->ui->Disable();

	LOG("Unloadign Music");
	//Mix_FreeMusic(music);

	LOG("Unloading the enemies");
	App->enemies->Disable();

	return true;
}

// Update: draw background
update_status ModuleFirstScene::Update()
{
	Mix_VolumeMusic(Volum);
	uint w, h;
	App->textures->GetSize(Background_Map, w, h);

	for (int i = -1; i < 10; i++)
	{
		App->render->Blit(Background_Map, i*w, 0, NULL);
	}
	
	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_DOWN && Volum<=128)
	{
		Volum += 8;
	}
	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_DOWN && Volum>=0)
	{
		Volum -= 8;
	}


	return UPDATE_CONTINUE;
}