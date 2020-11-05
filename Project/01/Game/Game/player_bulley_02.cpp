#include "stdafx.h"
#include "player_bullet_02.h"
#include "global.h"

#define BULLET_WIDTH 10
#define BULLET_HEIGHT 30

PlayerBullet02::PlayerBullet02(float x, float y)
{
	posX = x;
	posY = y - 50;
	radius = 15;
	isDead = false;
}

void PlayerBullet02::Update()
{
	posY -= 10;
}

void PlayerBullet02::Render()
{
	TextureElement* element = textureManager.getTexture(TEX_PLAYER_BULLET_02);
	RECT rc;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;

	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = BULLET_WIDTH;
	rc.bottom = BULLET_HEIGHT;

	pos = { posX, posY+20, 0 };
	cen = { BULLET_WIDTH / 2, BULLET_HEIGHT / 2, 0 };

	element->sprite->Draw(element->texture, &rc, &cen, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	element->sprite->End();
}

bool PlayerBullet02::IsDead()
{
	return isDead;
}

float PlayerBullet02::getRadius()
{
	return radius;
}

D3DXVECTOR2 PlayerBullet02::getSize()
{
	return { BULLET_WIDTH , BULLET_HEIGHT };
}

D3DXVECTOR2 PlayerBullet02::getPos()
{
	return { posX, posY };
}
