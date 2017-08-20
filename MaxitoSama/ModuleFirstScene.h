#ifndef __MODULEFIRSTSCENE_H__
#define __MODULEFIRSTSCENE_H__

#include "Module.h"
#include "Animation.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

#define FINAL_BOSS_ENEMIES_1 10

struct SDL_Texture;

class ModuleFirstScene : public Module
{
public:
	ModuleFirstScene();
	~ModuleFirstScene();

	bool Start();
	update_status Update();
	bool CleanUp();
	

public:
	SDL_Texture* Background_Map = nullptr;

	Mix_Music* music = NULL;

	Collider* mur1=nullptr;
	Collider* box = nullptr;

	bool enteredBossArea = false;
	bool finishedBossArea = false;
	bool music_boss = false;
	bool fading = false;

	int Volum;
	int final_boss_rand;

};

#endif // __MODULEFIRSTSCENE_H__