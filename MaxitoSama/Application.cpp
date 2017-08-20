#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleFirstScene.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "Menu.h"
#include "ModuleEnemies.h"
#include "ModuleElements1.h"
#include "ModuleFonts.h"
#include "UI.h"


Application::Application()
{
	int i = 0;
	modules[i++] = window = new ModuleWindow();
	modules[i++] = render = new ModuleRender();
	modules[i++] = input = new ModuleInput();
	modules[i++] = textures = new ModuleTextures();
	modules[i++] = scene_start = new ModuleInit();
	modules[i++] = first_scene = new ModuleFirstScene(); // Charge all the scenes before Player!!! if we don't do that the player will be under the background
	modules[i++] = player = new ModulePlayer();
	modules[i++] = enemies= new ModuleEnemies();
	modules[i++] = particles = new ModuleParticles();
	modules[i++] = fade = new ModuleFadeToBlack();
	modules[i++] = collision = new ModuleCollision();
	modules[i++] = music = new ModuleAudio();
	modules[i++] = elements1 = new ModuleElements1();
	modules[i++] = ui = new UI();
	modules[i++] = fonts = new ModuleFonts();
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Disable all stopped modules here
	player->Disable();
	first_scene->Disable();
	music->Disable();
	collision->Disable();
	enemies->Disable();
	elements1->Disable();
	ui->Disable();
	// ---

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}