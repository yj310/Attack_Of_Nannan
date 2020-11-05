#include "stdafx.h"
#include "bossB.h"
#include "global.h"
#include "player.h"
#include "math_util.h"

#define BOSS_WIDTH 500
#define BOSS_HEIGHT 333

BossB::BossB()
{
	enemyTime = 5;
	isinit = true;
	state = init;
	posX = WINDOW_WIDTH / 2;
	posY = -160;
	radius = 150;
	maxHP = 500;
	hp = maxHP;
	isDead = false;
	velX = 0.0;
	velY = 0.8;
	classType = BOSS_B;

}

void BossB::Update()
{
	if (hitTimer > 0)
		hitTimer--;

	switch (state)
	{
	case BossB::init:
		if (posY < WINDOW_HEIGHT * 0.2f)
			velY = 3;
		else
		{
			velY = 1;
			isinit = false;
			state = updown;
		}
		break;
	case BossB::updown:
		if (posY > WINDOW_HEIGHT * 0.2 + 15 || posY < WINDOW_HEIGHT * 0.2f - 15)
		{

			velY *= -1;
			enemyTime -= 1;
			gameSystem.GenerateBossbullet(posX, posY, getClassType(), STRIGHT);
			if (enemyTime <= 0)
			{
				state = move;
			}
		}
		break;
	case BossB::move:
		if (posY < WINDOW_HEIGHT * 0.4)
		{
			velY = 3;
		}
		else
		{
			velY = 1;
			state = updown2;
			enemyTime = 5;
		}
		break;
	case BossB::updown2:
		if (posY > WINDOW_HEIGHT * 0.4f + 15 || posY < WINDOW_HEIGHT * 0.4f - 15)
		{
			enemyTime--;
			velY *= -1;
			gameSystem.GenerateBossbullet(getPos().x, getPos().y, getClassType(),ROUND);
			
			if (enemyTime <= 0)
			{
				state = move2;
				velY = 0;
				velX = 3;
			}
		}
		break;
	case BossB::move2:
		velY = 0;
		if (posY > WINDOW_HEIGHT * 0.3)
		{
			velY = -1;
		}
		if (posX == WINDOW_WIDTH / 2)
		{
			gameSystem.GenerateBossbullet(getPos().x, getPos().y, getClassType(), ROUND);
		}
		if (posX > WINDOW_WIDTH-BOSS_WIDTH/2 || posX < 0 + BOSS_WIDTH / 2)
		{
			velX *= -1;
			gameSystem.GenerateBossbullet(getPos().x, getPos().y, getClassType(), ROUND);
		}
		break;
	case BossB::back:
		break;
	default:
		break;
	}
	

	if (hp <= 0)
	{
		isDead = true;
	}

	posY += velY;
	posX += velX;
}

void BossB::Render()
{
	TextureElement* element = textureManager.getTexture(TEX_BOSS_B);
	RECT rc;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;

	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = BOSS_WIDTH;
	rc.bottom = BOSS_HEIGHT;

	pos = { posX, posY, 0 };
	cen = { BOSS_WIDTH / 2, BOSS_HEIGHT / 2, 0 };

	if (hitTimer > 0)
		element->sprite->Draw(element->texture, &rc, &cen, &pos, D3DCOLOR_ARGB(255, 255, 0, 0));
	else
		element->sprite->Draw(element->texture, &rc, &cen, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	element->sprite->End();
}

bool BossB::IsDead()
{
	return isDead;
}

float BossB::getRadius()
{
	return radius;
}

D3DXVECTOR2 BossB::getSize()
{
	return { BOSS_WIDTH, BOSS_HEIGHT };
}

D3DXVECTOR2 BossB::getPos()
{
	return { posX, posY };
}

void BossB::Hit(float damage)
{
	if (state != init)
	{
		hp -= damage;
		hitTimer = 4;
	}
	
}

float BossB::getMaxHP()
{
	return maxHP;
}

float BossB::getHP()
{
	return hp;
}

int BossB::getClassType()
{
	return classType;
}

