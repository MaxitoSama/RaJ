#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#define BULLET_SPEED 5
#define GRENADE_SPEED 1.3f
#define SHOTS_PER_BURST 1
#define SHOT_DELAY 0
#define GRAVITY 0;

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	void shot();

public:
	SDL_Texture* graphics = nullptr;
	SDL_Texture* textures = nullptr;
	
	Mix_Chunk* music = NULL;
	
	SDL_Rect bridge;

	Animation* current_animation = nullptr;
	Animation idle_Stop_1;
	Animation idle_Stop_2;
	Animation left;
	Animation right;
	Animation die;
	Animation bullet_explosion;
	Animation Scythe_Right;
	Animation Scythe_Left;

	Collider* Player_Coll;
	Collider* feetcoll;
	
	int font_score = -1;
	int speed;


	enum LastDirection { UP, DOWN, LEFT, RIGHT, UPRIGHT, UPLEFT, DOWNRIGHT, DOWNLEFT};
	LastDirection player_last_direction;
	iPoint position;
	bool stop = false;
	bool alive = false;
	bool anim = false;
	bool water = false;
	bool grenade = false;
	bool distance = false;
	bool Jump = false;
	bool fall=false;
	bool shooting = false;
	int shots_fired = 0;
	int shot_current_delay = 0;
	int score = 0;
	int counter = 0;
	bool god = false;
	bool only = true;
};

#endif