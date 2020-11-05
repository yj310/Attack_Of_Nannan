#include "stdafx.h"
#include "enemyD.h"
#include "global.h"

#define ENEMY_WIDTH 60
#define ENEMY_HEIGHT 60

EnemyD::EnemyD()
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

void EnemyD::Update()
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
		gameSystem.GenerateEnemyExplosion(posX, posY);
	}

	if (hitTimer > 0)
		hitTimer--;
}

void EnemyD::Render()
{
	TextureElement* element = textureManager.getTexture(TEX_ENEMY_D);
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

bool EnemyD::IsDead()
{
	return isDead;
}

float EnemyD::getRadius()
{
	return radius;
}

D3DXVECTOR2 EnemyD::getSize()
{
	return { ENEMY_WIDTH, ENEMY_HEIGHT };
}

D3DXVECTOR2 EnemyD::getPos()
{
	return { posX, posY };
}

void EnemyD::Hit(float damage)
{
	hp -= damage;
	hitTimer = 6;
}

float EnemyD::getMaxHP()
{
	return maxHP;
}

float EnemyD::getHP()
{
	return hp;
}

int EnemyD::getClassType()
{
	return classType;
}
