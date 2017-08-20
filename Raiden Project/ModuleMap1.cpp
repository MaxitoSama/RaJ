#include "Application.h"
#include "ModuleMap1.h"
#include "ModuleMap2.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "Menu.h"
#include "ModuleInput.h"
#include "ModuleAudio_1.h"
#include "ModuleAudio_2.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModulePowerUps.h"
#include "ModuleFonts.h"
#include "ModuleShadows.h"
#include "ModuleStageClear1.h"
#include "ModuleGroundExplosion.h"
#include "ModuleGroundEnemies.h"

#include <stdio.h>

ModuleMap1::ModuleMap1() : Module()
{
	
}
ModuleMap1::~ModuleMap1()
{
   
}

bool ModuleMap1::Init()
{
	LOG("Loading background assets");
	ground = { 0, 0, 1000, 1000 };
	Map1 = App->textures->Load("Assets/jeje.png");
  
	
	return true;
}

update_status ModuleMap1::Update()
{
	App->render->Blit(Map1, -200, 0, &ground,0,0);

	//Reset to chechpoint
	/*if (reset_collision && !initial_dead_time_got)
	{
		initial_dead_time = SDL_GetTicks();
		initial_dead_time_got = true;
	}
	if (SDL_GetTicks() - initial_dead_time > 1000 && reset_collision)
	{
		App->fade->FadeToBlack((Module*)App->map_1, (Module*)App->map_1);
		reset_collision = false;
		initial_dead_time_got = false;
	}*/

	//Reset to StageCleared
	
	return UPDATE_CONTINUE;
}

bool ModuleMap1::CleanUp()
{
	return true;
}