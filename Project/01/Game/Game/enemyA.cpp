#include "stdafx.h"
#include "enemyA.h"
#include "global.h"
#include "player.h"
#include "enemy_explosion.h"

#define ENEMY_WIDTH 60
#define ENEMY_HEIGHT 60

EnemyA::EnemyA()
{
	posX = rand() % 600 + (WINDOW_WIDTH / 2) - 300;
	posY = -70;
	state = kInit;
	velY = 6;
	radius = 30;
	hp = 3 + (Level * Level);
	isDead = false;
	classType = ENEMY_A;

}

void EnemyA::Update()
{
	if (state == kInit)
	{
		state = kMoveToPoint;
	}
	if (state == kMoveToPoint)
	{
		posY += velY;
		if (posY > WINDOW_HEIGHT * 0.3)
		{
			state = kChoosePoint;
		}
	}
	if (state == kChoosePoint)
	{
		//velX = ((rand() % 2 == 0) ? -1 : 1) * 5;
		if (posX < gameSystem.player->getPos().x)
		{
			velX = 2;
		}
		else
		{
			velX = -2;
		}
		state = kMoveToEnd;
	}
	if (state == kMoveToEnd)
	{
		posX += velX;
		posY += velY;
	}
	if (hp <= 0)
	{
		isDead = true;
		Exp += 5;
		
	}

	if (isDead == true)
	{
		gameSystem.GenerateEnemyExplosion(posX, posY);
	}


	if (hitTimer > 0)
		hitTimer--;
}

void EnemyA::Render()
{
	TextureElement* element = textureManager.getTexture(TEX_ENEMY_A);
	RECT rc;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;

	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = ENEMY_WIDTH;
	rc.bottom = ENEMY_HEIGHT;

	pos = { posX, posY, 0 };
	cen = { ENEMY_WIDTH / 2, ENEMY_HEIGHT / 2, 0 };

	if (hitTimer > 0)
		element->sprite->Draw(element->texture, &rc, &cen, &pos, D3DCOLOR_ARGB(255, 255, 0, 0));
	else
		element->sprite->Draw(element->texture, &rc, &cen, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	element->sprite->End();
}

bool EnemyA::IsDead()
{
	return isDead;
}

float EnemyA::getRadius()
{
	return radius;
}

D3DXVECTOR2 EnemyA::getSize()
{
	return { ENEMY_WIDTH, ENEMY_HEIGHT };
}

D3DXVECTOR2 EnemyA::getPos()
{
	return { posX, posY };
}

void EnemyA::Hit(float damage)
{
	hp -= damage;
	hitTimer = 6;
}

float EnemyA::getMaxHP()
{
	return maxHP;
}

float EnemyA::getHP()
{
	return hp;
}

int EnemyA::getClassType()
{
	return classType;
}

