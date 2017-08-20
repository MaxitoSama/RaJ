#include "Globals.h"
#include "Application.h"
#include "ModuleMap2.h"
#include "Menu.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleMap1.h"
#include "ModuleInput.h"
#include "ModuleStageClear1.h"
#include "ModuleAudio_1.h"
#include "ModuleAudio_2.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModulePlayer2.h"
#include "ModulePowerUps.h"
#include "ModuleShadows.h"
#include "ModuleGroundExplosion.h"
#include "ModuleGroundEnemies.h"
#include "ModuleFonts.h"
#include <stdio.h>

Menu::Menu() : Module()
{

}
Menu::~Menu()
{

}

bool Menu::Init()
{
	LOG("Loading background assets");
	App->map_1->Disable();

	App->StageClear1->Disable();
	App->audio_2->Close();
	App->particles->Disable();
	App->shadows->Disable();
	App->player->Disable();
	App->player2->Disable();

	sprintf_s(insert_coin, 50, "INSERT COIN");
	ground = { 0, 0 ,224 * 3 ,256 * 3};
	Welcome = App->textures->Load("Assets/WelcomeScreen.png");
	return true;
}

update_status Menu::Update()
{
	App->render->Blit(Welcome, 0, 0, &ground, 224 * 3, 256*3 + 62 );

	App->fonts->BlitText(220, 760, font, insert_coin);
		
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, App->map_1);
	}
	return UPDATE_CONTINUE;
}

bool Menu::CleanUp()
{
	return true;
}