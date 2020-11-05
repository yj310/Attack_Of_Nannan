#include "stdafx.h"
#include "enemy_bullet.h"
#include "global.h"

#define BULLET_WIDTH 16
#define BULLET_HEIGHT 16

EnemyBullet::EnemyBullet(float x, float y)
{
	posX = x;
	posY = y;
	velY = 10;
	radius = 8;
	isDead = false;
}

void EnemyBullet::Update()
{
	posY += velY;
}

void EnemyBullet::Render()
{
	TextureElement* element = textureManager.getTexture(TEX_ENEMY_BULLET);
	RECT rc;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;

	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = BULLET_WIDTH;
	rc.bottom = BULLET_HEIGHT;

	pos = { posX, posY, 0 };
	cen = { BULLET_WIDTH / 2, BULLET_HEIGHT / 2, 0 };

	element->sprite->Draw(element->texture, &rc, &cen, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	element->sprite->End();
}

bool EnemyBullet::IsDead()
{
	return isDead;
}

float EnemyBullet::getRadius()
{
	return radius;
}

D3DXVECTOR2 EnemyBullet::getSize()
{
	return { BULLET_WIDTH , BULLET_HEIGHT };
}

D3DXVECTOR2 EnemyBullet::getPos()
{
	return { posX, posY };
}
