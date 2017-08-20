#include <stdlib.h>  
#include <time.h>  
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "Menu.h"
#include "Enemy.h"
#include "ModuleElements1.h"
#include "ROBOT_MAN.h"


ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	sprites = App->textures->Load("assets/Enemy.png");

	srand(time(NULL));

	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if (queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) {
			if (enemies[i]->alive) {
				enemies[i]->Move();
			}
			if (App->scene_start->player_2 == false)
			{
				if (App->player->anim) {
					enemies[i]->position.x = 100000;
					enemies_on_action = 0;
				}
			}
			else
			{
				if (App->player->anim ) {
					enemies[i]->position.x = 100000;
					enemies_on_action = 0;
				}
			}
		}

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) {
			if (enemies[i]->alive)
				enemies[i]->Draw(sprites);
			else
				eliminateEnemy(enemies[i], i);
		}


	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				/*LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;*/
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleEnemies::eliminateEnemy(Enemy * e, int i)
{
	App->render->Blit(sprites, e->position.x - 8, e->position.y - 8, &e->death->GetCurrentFrame(), 0.75f);

	if (e->dead_animation_current_life < e->dead_animation_life) {
		e->alive = false;
		enemies[i]->GetCollider()->SetPos(2000, 2000);
		e->dead_animation_current_life++;
	}
	else {
		enemies[i]->position.x = 2000;
		enemies[i]->position.y = 2000;
		enemies[i] = nullptr;
		enemies_on_action--;
	}
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}



void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::ROBOT_MAN:
			enemies[i] = new Robot_man(info.x, info.y);
			break;
		/*case ENEMY_TYPES::PRISONER_ENEMIES:
			enemies[i] = new PrisonerEnemies(info.x, info.y);
			enemies[i]->behaviour = info.behaviour;
			break;
		case ENEMY_TYPES::PRISONER:
			enemies[i] = new Prisoner(info.x, info.y);
			enemies[i]->behaviour = info.behaviour;
			break;
		case ENEMY_TYPES::BIKEENEMY:
			enemies[i] = new BikeEnemy(info.x, info.y);
			enemies[i]->behaviour = info.behaviour;
			break;
		case ENEMY_TYPES::GRANADIER:
			enemies[i] = new Granadier(info.x, info.y);
			enemies[i]->behaviour = info.behaviour;
			break;
		case ENEMY_TYPES::BARRICADE_TROOPER:
			enemies[i] = new BarricadeTrooper(info.x, info.y);
			enemies[i]->behaviour = info.behaviour;
			break;
		case ENEMY_TYPES::BOSS_TROOPER:
			enemies[i] = new FinalBossRifleMan(info.x, info.y);
			enemies[i]->behaviour = info.behaviour;
			break;
		case ENEMY_TYPES::COMMANDER:
			enemies[i] = new Commander(info.x, info.y);
			enemies[i]->behaviour = info.behaviour;
			break;
		case ENEMY_TYPES::BIKE_M2:
			enemies[i] = new Bike_M2(info.x, info.y);
			enemies[i]->behaviour = info.behaviour;
			break;
		case ENEMY_TYPES::CARENEMY:
			enemies[i] = new CarEnemy(info.x, info.y);
			enemies[i]->behaviour = info.behaviour;
			break;
		case ENEMY_TYPES::HOLE_TROOPER:
			enemies[i] = new HoleTrooper(info.x, info.y);
			enemies[i]->behaviour = info.behaviour;
			break;
		case ENEMY_TYPES::BUNKER:
			enemies[i] = new Bunker(info.x, info.y);
			enemies[i]->behaviour = info.behaviour;
			break;*/
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	//esborra l'enemic quan es tocat per una bullet del player
	if (c2->type == COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_GRENADE_EXPLOSION)
	{
		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
			{
				{
					if (enemies[i]->alive) {
						App->elements1->num_score += enemies[i]->score;
						enemies[i]->OnCollision(c2);
						if (enemies[i]->type == 1) {
							enemies[i]->position.x = 2000;
							enemies[i]->position.y = 2000;
							enemies[i] = nullptr;
						}
						else
						eliminateEnemy(enemies[i], i);
					}
				}
				break;
			}
		}
	}
}