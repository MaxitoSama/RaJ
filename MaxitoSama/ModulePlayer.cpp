#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleElements1.h"
#include "UI.h"
#include "ModuleFonts.h"
#include "ModuleAudio.h"
#include "Menu.h"
#include "ModuleFirstScene.h"
#include "ModuleEnemies.h"
#include "UI.h"


	
ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;
	
	//idle animation Right
	idle_Stop_1.PushBack({6,80,46,70});
	idle_Stop_1.PushBack({ 116,81,46,70 });
	idle_Stop_1.PushBack({ 63,81,46,70 });
	idle_Stop_1.PushBack({ 116,81,46,70 });

	idle_Stop_1.loop = true;
	idle_Stop_1.speed = 0.07f;

	//idle animation Left
	idle_Stop_2.PushBack({ 495,397,46,70 });
	idle_Stop_2.PushBack({ 385,398,46,70 });
	idle_Stop_2.PushBack({ 438,398,46,70 });
	idle_Stop_2.PushBack({ 385,398,46,70 });

	idle_Stop_2.loop = true;
	idle_Stop_2.speed = 0.07f;

	// Move Right
	right.PushBack({ 6,2,46,70 });
	right.PushBack({61,2,42,70 });
	right.PushBack({117,2,42,70 });
	right.PushBack({ 172,2,42,70 });

	right.loop = true;
	right.speed = 0.1f;

	// Move Left
	left.PushBack({ 496,317,46,70 });
	left.PushBack({ 440,318,42,70 });
	left.PushBack({ 385,318,42,70 });
	left.PushBack({ 330,318,42,70 });

	left.loop = true;
	left.speed = 0.1f;

	//Scythe Right
	Scythe_Right.PushBack({11,646,49,56});
	Scythe_Right.PushBack({68,645,46,58});
	Scythe_Right.PushBack({11,646,49,56 });
	Scythe_Right.PushBack({124,649,52,54});

	Scythe_Right.loop = true;
	Scythe_Right.speed = 0.1f;

	//Scythe Left
	Scythe_Left.PushBack({ 128,717,49,56 });
	Scythe_Left.PushBack({74,716,46,58});
	Scythe_Left.PushBack({ 128,717,49,56 });
	Scythe_Left.PushBack({ 13,720,52,54 });

	Scythe_Left.loop = true;
	Scythe_Left.speed = 0.1f;

	//DIE
	die.PushBack({331,190,29,26});
	die.PushBack({ 361,190,29,26 });
	die.PushBack({ 391,190,29,26 });
	die.loop = false;
	die.speed = 0.05f;	

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading Player Sheet");
	graphics = App->textures->Load("assets/Player_sheet.png");
	
	LOG("Loading Player Collider");
	Player_Coll = App->collision->AddCollider({ position.x, position.y, 46, 70 }, COLLIDER_PLAYER,this);
	//font_score = App->fonts->Load("fonts/Lletres_1.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZ./\ ", 2);

	position.x = SCREEN_WIDTH/2;
	position.y = 215;

	stop = false;
	anim = false;
	water = false;
	grenade = false;
	god = false;
	counter = 0;
	only = true;
	fall = false;
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player Sheet");
	App->textures->Unload(graphics);
	//App->fonts->UnLoad(font_score);
	//App->textures->Unload(textures);

	LOG("Destroying Player Collider");
	if (Player_Coll != nullptr)
		Player_Coll->to_delete = true;

	return true;
}
// Update: draw background
update_status ModulePlayer::Update()
{
	SDL_Event e;
	speed = 2;

	//LEFT
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;
		if (current_animation != &left)
		{
			left.Reset();
			current_animation = &left;
		}
		App->render->Blit(graphics, position.x-30, position.y+15, &(Scythe_Left.GetCurrentFrame()));
		player_last_direction = LEFT;
	}
	//RIGHT
	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;
		if (current_animation != &right)
		{
			right.Reset();
			current_animation = &right;
		}
		App->render->Blit(graphics, position.x+25, position.y+15, &(Scythe_Right.GetCurrentFrame()));
		player_last_direction = RIGHT;
	}

	//JUMP
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT && Jump==false)
	{
		Jump = true;
	}
	//DOWN
	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
	{
		/*if (position.y <SCREEN_HEIGHT - 20) {
			position.y += speed;
		}
		if (current_animation != &down)
		{
			down.Reset();
			current_animation = &down;
		}
		player_last_direction = DOWN;*/
	}
	//UP
	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
	{
		/*if (position.y > -1864 + SCREEN_HEIGHT) {
			position.y -= speed;
		}
		if (current_animation != &up)
		{
			up.Reset();
			current_animation = &up;
		}
		player_last_direction = UP;*/
	}

	//SHOT 
	
	shot();
	
	while (SDL_PollEvent(&e))
	{
		switch (e.type) {
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				shooting = true;
			}
			break;
		}
	}

	//GRAVITY SIMULATOR
	if (Jump == false)
	{
		position.y += 5;
	}

	//JUMP METHODE
	if (Jump == true && fall==false)
	{
		position.y -= 10;
		counter++;
		if (counter == 10)
		{
			counter = 0;
			fall = true;
		}
	}
	if (Jump == true && fall == true)
	{
		position.y += 10;
	}


	/*if (anim == true)
	{
		current_animation = &die;
		if (current_animation->Finished() == true)
		{
			current_animation->Reset();
				anim = false;
				alive = true;
				only = true;
		}
	}
	else
	{
		anim = false;	
		Disable();
	}

	
	*/
	
	// Special attack

	/*if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN ||
		App->input->controll[5] == KEY_STATE::KEY_DOWN) {   //Mes maco que lo de dalt no? (lo de dalt es pot borrar ja que ja no funciona )
		if (App->elements1->num_grenades > 0){
			current_animation = &grenadeThrow;
			if (grenade == false)
			App->particles->AddParticle(App->particles->grenade, position.x + 11, position.y + 3, COLLIDER_NONE);
		}
		grenade = true;
	}
	if (grenade) {
		if (current_animation->Finished() == true) {
			current_animation->Reset();
			grenade = false;
		}
	}*/

	//IDLE ANIMATIONS
	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE)
	{
		switch (player_last_direction)
		{
		case ModulePlayer::UP:
			current_animation = &idle_Stop_1;
			break;
		case ModulePlayer::DOWN:
			current_animation = &idle_Stop_1;
			break;
		case ModulePlayer::LEFT:
			current_animation = &idle_Stop_2;
			break;
		case ModulePlayer::RIGHT:
			current_animation = &idle_Stop_1;
			break;
		default:
			break;
		}
	}

	// Player Colliders Position
	Player_Coll->SetPos(position.x, position.y);


	// Draw everything --------------------------------------
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	
	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {
	if (c2->type == COLLIDER_WALL)
	{
		if (c1 == feetcoll && (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT
			|| App->input->controll[0] == KEY_STATE::KEY_REPEAT))
		{
			position.y += 1;
		}
		if (c1 == feetcoll && (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT
			|| App->input->controll[1] == KEY_STATE::KEY_REPEAT))
		{
			position.y -= 1;
		}
		if (c1 == feetcoll && (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT
			|| App->input->controll[3] == KEY_STATE::KEY_REPEAT))
		{
			position.x += 1;
		}
		if (c1 == feetcoll && (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT
			|| App->input->controll[2] == KEY_STATE::KEY_REPEAT))
		{
			position.x -= 1;
		}
	}
	
	if (c2->type == COLLIDER_ENEMY_SHOT && god == false)
	{
		if (alive) {
			alive = false;
			App->elements1->num_lives_play_1--;
			anim = true;
		}
	}
	
	if (c2->type == COLLIDER_ENEMY && god == false)
	{
		if (alive) {
			alive = false;
			App->elements1->num_lives_play_1--;
			anim = true;
		}
	}

	//Jump methode
	if (c2->type == COLLIDER_FLOOR)
	{
		position.y -= 5;
		Jump = false;
		fall = false;
	}
}

void ModulePlayer::shot() {
	int x, y;

	// Taking the Position of the mouse
	SDL_GetMouseState(&x, &y);

	//Changing the focus of the mouse (0,0) by default
	x = x - ((SCREEN_WIDTH*SCREEN_SIZE)/2) - (23*SCREEN_SIZE);
	y = y - position.y*SCREEN_SIZE -35* SCREEN_SIZE;
	
	//The direction of the bullet is the module of the new mouse position
	App->particles->bullet.speed.y = y/sqrt(x*x+y*y)*5;
	App->particles->bullet.speed.x = x/sqrt(x*x+y*y)*5;

	//Creates the Particle
	if (shots_fired < SHOTS_PER_BURST && shooting == true && App->ui->mana>0) {
		LOG("ShOOTTOODAAA!!!!");
		if (shot_current_delay < SHOT_DELAY)
			shot_current_delay++;
		else {
			App->particles->AddParticle(App->particles->bullet, position.x + 23, position.y + 35, COLLIDER_PLAYER_SHOT);
			shots_fired++;
			shot_current_delay = 0;
			App->ui->mana--;
		}
	}
	else {
		shots_fired = 0;
		shooting = false;
	}
}

