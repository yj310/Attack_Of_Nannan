#include "stdafx.h"
#include "enemyB.h"
#include "global.h"

#define ENEMY_WIDTH 60
#define ENEMY_HEIGHT 60

EnemyB::EnemyB()
{
	posX = rand() % 600 + (WINDOW_WIDTH / 2) - 300;
	posY = 00;
	velX = (rand() % 2 == 0) ? 18 : -18;
	velY = 4;
	radius = 30;
	hp = 6;
	isDead = false;
	classType = ENEMY_B;

}

void EnemyB::Update()
{
	posX += velX;
	posY += velY;
	if (posX <= 30 || posX >= WINDOW_WIDTH - 30)
	{
		velX *= -1;
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

void EnemyB::Render()
{
	TextureElement* element = textureManager.getTexture(TEX_ENEMY_B);
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

bool EnemyB::IsDead()
{
	return isDead;
}

float EnemyB::getRadius()
{
	return radius;
}

D3DXVECTOR2 EnemyB::getSize()
{
	return { ENEMY_WIDTH, ENEMY_HEIGHT };
}

D3DXVECTOR2 EnemyB::getPos()
{
	return { posX, posY };
}

void EnemyB::Hit(float damage)
{
	hp -= damage;
	hitTimer = 6;
}

float EnemyB::getMaxHP()
{
	return maxHP;
}

float EnemyB::getHP()
{
	return hp;
}

int EnemyB::getClassType()
{
	return classType;
}


