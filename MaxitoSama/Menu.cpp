#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleFirstScene.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "Menu.h"
#include "ModuleElements1.h"

ModuleInit::ModuleInit()
{}

ModuleInit::~ModuleInit()
{}

// Load assets
bool ModuleInit::Start()
{
	LOG("Loading Menu Background");
	background_texture = App->textures->Load("assets/background_menu.png");
	LOG("Loading Game Tittle");
	Game_Tittle = App->textures->Load("assets/Game_Title.png");
	LOG("Loading Next");
	Next = App->textures->Load("assets/Next.png");
	
	
	background.PushBack({ 0, 0, 480, 340 });
	background.PushBack({ 0, 0, 0, 0});
	background.speed = 0.02f;

	LOG("Loading audio scene");
	//music = App->music->LoadChunk("assets/Commando_01_Credit.wav");


	return true;
}

// UnLoad assets
bool ModuleInit::CleanUp()
{
	LOG("Unloading Menu Background");
	App->textures->Unload(background_texture);

	LOG("Unloading Game tittle");
	App->textures->Unload(Game_Tittle);
	
	LOG("Unloading Next");
	App->textures->Unload(Next);

	
	return true;
}

// Update: draw background
update_status ModuleInit::Update()
{

	SDL_Event e;
	

	// Draw everything --------------------------------------
	App->render->Blit(background_texture, 0, 0, NULL);
	App->render->Blit(Next, SCREEN_WIDTH-50, SCREEN_HEIGHT-50, NULL);
	App->render->Blit(Game_Tittle, 0, 0, &(background.GetCurrentFrame()), 0.75f);

	//Events

	while (SDL_PollEvent(&e)) 
	{
		switch (e.type) {
		case SDL_MOUSEBUTTONDOWN:
			mousePress(e.button,Next);
			break;
		}
	}


	return UPDATE_CONTINUE;
}

void ModuleInit::mousePress(SDL_MouseButtonEvent& b, SDL_Texture* image)
{
	uint imageW, imageH;
	
	App->textures->GetSize(image, imageW, imageH);

	LOG("Image Width -> %d", imageW);
	LOG("Image Height -> %d", imageH);

	if (b.button== SDL_BUTTON_LEFT && b.x >= (SCREEN_WIDTH*SCREEN_SIZE- imageW* SCREEN_SIZE) && b.y >= (SCREEN_HEIGHT*SCREEN_SIZE - imageH* SCREEN_SIZE))
	{
		LOG("Punteria");
		App->fade->FadeToBlack(this, App->first_scene, 0);
	}
}

