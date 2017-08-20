#include "UI.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Menu.h"
#include "ModuleFirstScene.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModuleElements1.h"
#include "ModuleFonts.h"

#include<stdio.h>



UI::UI()
{
}


UI::~UI()
{
}

// Load assets
bool UI::Start()
{
	LOG("Loading UI textures");
	Frame = App->textures->Load("assets/Circular_frame.png");
	Life=App->textures->Load("assets/Life.png");

	lives = 10;
	mana = 10;
	last_time = 0;
	reloading_vel = 1000;
	

	Life_frame = {8,2,185,13};
	Life_piece = {8,17,18,11};
	Mana_piece= { 8,32,18,11 };

	
	return true;
}

// UnLoad assets
bool UI::CleanUp()
{
	LOG("Unloading UI textures");
	App->textures->Unload(Frame);

	return true;
}

// Update: draw background
update_status UI::Update()
{
	App->render->Blit(Frame,App->player->position.x-(SCREEN_WIDTH / 2),0 ,NULL);

	for (int i = 0; i < lives; i++)
	{
		App->render->Blit(Life, App->player->position.x - (SCREEN_WIDTH / 2) + 81 + (i * 18), 20, &Life_piece);
	}
	for (int i = 0; i < mana; i++)
	{
		App->render->Blit(Life, App->player->position.x - (SCREEN_WIDTH / 2) + 81 + (i * 18), 33, &Mana_piece);
	}

	App->render->Blit(Life, App->player->position.x - (SCREEN_WIDTH / 2) + 78, 20, &Life_frame);
	App->render->Blit(Life, App->player->position.x - (SCREEN_WIDTH / 2) + 78, 33, &Life_frame);

	Mana();

	return UPDATE_CONTINUE;
}

void UI::Mana()
{
	current_time = SDL_GetTicks();
	if (current_time > last_time + reloading_vel && mana<10)
	{
		mana++;
		last_time = current_time;
	}
}