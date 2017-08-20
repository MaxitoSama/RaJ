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

ModuleElements1::ModuleElements1()
{}

ModuleElements1::~ModuleElements1()
{}

// Load assets
bool ModuleElements1::Start()
{	
	
	return true;
}

// UnLoad assets
bool ModuleElements1::CleanUp()
{
	LOG("Unloading space scene");
	App->textures->Unload(textures);
//	App->textures->Unload(cannon);
	App->fonts->UnLoad(num_1);
	App->fonts->UnLoad(num_2);
	App->fonts->UnLoad(let_2);
	
	return true;
}

// Update: draw background
update_status ModuleElements1::Update()
{

	return UPDATE_CONTINUE;
}