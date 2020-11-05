#include "stdafx.h"
#include "player_bullet_01.h"
#include "global.h"

#define BULLET_WIDTH 30
#define BULLET_HEIGHT 30

PlayerBullet::PlayerBullet(float x, float y, float vx, float vy)
{
	posX = x;
	posY = y - 50;
	velX = vx * 10;
	velY = vy * 10;
	radius = 15;
	isDead = false;
}

void PlayerBullet::Update()
{
	posX -= velX;
	posY -= velY;
}

void PlayerBullet::Render()
{
	TextureElement* element = textureManager.getTexture(TEX_PLAYER_BULLET_01);
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

bool PlayerBullet::IsDead()
{
	return isDead;
}

float PlayerBullet::getRadius()
{
	return radius;
}

D3DXVECTOR2 PlayerBullet::getSize()
{
	return { BULLET_WIDTH , BULLET_HEIGHT };
}

D3DXVECTOR2 PlayerBullet::getPos()
{
	return { posX, posY };
}
