#ifndef __UI_H__
#define __UI_H__

#include "Module.h"
#include "Animation.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

struct SDL_Texture;

class UI: public Module
{
public:
	UI();
	~UI();

	bool Start();
	update_status Update();
	bool CleanUp();

	void Mana();

public:

	SDL_Texture* Frame;
	SDL_Texture* Life;

	SDL_Rect Life_frame;
	SDL_Rect Life_piece;
	SDL_Rect Mana_piece;


	uint lives;
	uint mana; 
	uint last_time;
	uint current_time;
	uint reloading_vel;

};

#endif // __UI_H__