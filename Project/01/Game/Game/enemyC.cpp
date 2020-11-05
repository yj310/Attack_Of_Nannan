#include "stdafx.h"
#include "enemyC.h"
#include "global.h"
#include "player.h"

#define ENEMY_WIDTH 60
#define ENEMY_HEIGHT 60

EnemyC::EnemyC()
{
	posX = rand() % 600 + (WINDOW_WIDTH / 2) - 300;
	posY = -70;
	state = kInit;
	velY = 6;
	radius = 30;
	hp = 3 + (Level * Level);
	isDead = false;
	classType = ENEMY_C;

}

void EnemyC::Update()
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
		gameSystem.GenerateEnemyExplosion(posX, posY);
	}

	if (hitTimer > 0)
		hitTimer--;
}

void EnemyC::Render()
{
	TextureElement* element = textureManager.getTexture(TEX_ENEMY_C);
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

bool EnemyC::IsDead()
{
	return isDead;
}

float EnemyC::getRadius()
{
	return radius;
}

D3DXVECTOR2 EnemyC::getSize()
{
	return { ENEMY_WIDTH, ENEMY_HEIGHT };
}

D3DXVECTOR2 EnemyC::getPos()
{
	return { posX, posY };
}

void EnemyC::Hit(float damage)
{
	hp -= damage;
	hitTimer = 6;
}

float EnemyC::getMaxHP()
{
	return maxHP;
}

float EnemyC::getHP()
{
	return hp;
}

int EnemyC::getClassType()
{
	return classType;
}

