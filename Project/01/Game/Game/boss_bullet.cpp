#include "stdafx.h"
#include "boss_bullet.h"
#include "global.h"

#define BULLET_WIDTH 30
#define BULLET_HEIGHT 30

BossBullet::BossBullet(float x, float y, float vx, float vy, int bossType)
{
	posX = x;
	posY = y;
	velY = vy*10;
	velX = vx * 10;
	radius = 8;
	isDead = false;
	bossBulletType = bossType;
}

void BossBullet::Update()
{
	
	posY += velY;
	posX += velX;
}

void BossBullet::Render()
{
	TextureElement* element = textureManager.getTexture(bossBulletType);
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

bool BossBullet::IsDead()
{
	return isDead;
}

float BossBullet::getRadius()
{
	return radius;
}

D3DXVECTOR2 BossBullet::getSize()
{
	return { BULLET_WIDTH , BULLET_HEIGHT };
}

D3DXVECTOR2 BossBullet::getPos()
{
	return { posX, posY };
}
