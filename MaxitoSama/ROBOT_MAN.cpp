#include "ROBOT_MAN.h"
#include <math.h>
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"


Robot_man::Robot_man(int x, int y) : Enemy(x, y)
{
	moveLeft.PushBack({ 3, 98, 55, 73 });
	moveLeft.PushBack({ 78, 102, 55, 75 });
	moveLeft.PushBack({ 151, 99, 55, 76 });
	moveLeft.PushBack({ 225, 102, 55, 75 });
	moveLeft.PushBack({ 294, 101, 55, 73 });
	moveLeft.PushBack({ 361, 99, 55, 75 });
	moveLeft.PushBack({ 429, 98, 55, 76 });
	moveLeft.PushBack({ 492, 99, 55, 75 });
	moveLeft.PushBack({ 555, 99, 55, 73 });
	moveLeft.speed = 0.2f;
	moveLeft.loop = true;
	animation = &moveLeft;

	path.PushBack({ -0.5f,0.0f }, 100, animation);
	path2.PushBack({ 0.5f, 0.0f }, 100, animation);

	collider = App->collision->AddCollider({ 0, 0, 59, 20 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;

	one = true;
	two = false;
}

void Robot_man::Move()
{
	/*if (one)
	{
		position.x = original_pos.x + (25.0f * sinf(wave) * 5);
	}
	else
	{
		if (wave < -1.0f)
			one = true;
		else
			wave -= 0.05f;
	}

	position.x = original_pos.x+ (25.0f * sinf(wave)*5);*/

	if (one) 
	{
		position.x = original_pos.x + (float)path2.GetCurrentPosition(&animation).x;
		position.y = original_pos.y + (float)path2.GetCurrentPosition(&animation).y;
		if (position.x >= 400)
		{
			original_pos.x = position.x;
			one = false;
		}
	}
	else
	{
		position.x = original_pos.x + (float)path.GetCurrentPosition(&animation).x;
		position.y = original_pos.y + (float)path.GetCurrentPosition(&animation).y;
		
		if (position.x <= 300)
		{
			original_pos.x = position.x;
			one = true;
		}
	}
}

