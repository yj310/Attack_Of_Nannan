#include "stdafx.h"
#include "bossA.h"
#include "global.h"
#include "player.h"
#include "math_util.h"

#define BOSS_WIDTH 300
#define BOSS_HEIGHT 200

BossA::BossA()
{
	
	speed = 10;
	isinit = true;
	//isBack = true;
	state = init;
	posX = WINDOW_WIDTH / 2;
	posY = -100;
	radius = 80;
	maxHP = 250;
	hp = 250;
	isDead = false;
	velY = 0;
	velX = 0;
	classType = BOSS_A;
	enemyTime = 5;
}

void BossA::Update()
{
	if (hitTimer > 0)
		hitTimer--;
	


	switch (state)
	{
	case BossA::init:
		if (posY < WINDOW_HEIGHT * 0.2f)
			velY = 3;
		else
		{
			velY = 1;
			isinit = false;
			state = updown;
		}
		break;
	case BossA::updown:
		if (posY > WINDOW_HEIGHT * 0.2f + 15 || posY < WINDOW_HEIGHT * 0.2f - 15)
		{

			velY *= -1;
			enemyTime -=1;
			if (enemyTime <= 0)
			{
				moveX = gameSystem.player->getPos().x;
				moveY = gameSystem.player->getPos().y+10;

				disX = fabs((gameSystem.player->getPos().x) - posX);
				disY = fabs((gameSystem.player->getPos().y) - posY);

				state = move;
			}

			gameSystem.GenerateBossbullet(getPos().x , getPos().y,getClassType(),STRIGHT);
			
		}
		break;
	case BossA::move:
		enemyTime = 3;


		velX = disX / 40;
		velY = disY / 40;
	
		if (posX > moveX)
			velX *= -1;
		
		if (posY > moveY)
			velY *= -1;


		if (isCircleCollided(posX, posY, radius,moveX,moveY,gameSystem.player->getRadius()))
		{
			velX = 0;
			velY = 0;
			state = back;
		}
		if (velY > moveY)
		{
			state = back;
		}

		break;
	case BossA::back:
		
		if (posY > WINDOW_HEIGHT * 0.2)
		{
			velY = -speed;
		}
		else
		{
			float a= WINDOW_HEIGHT * 0.2f - 15;
			float b = WINDOW_HEIGHT * 0.2f + 15;
			posX, posY;
			velY = 1;
			state = updown;
		}
			
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

void BossA::Render()
{
	TextureElement* element = textureManager.getTexture(TEX_BOSS_A);
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

bool BossA::IsDead()
{
	return isDead;
}

float BossA::getRadius()
{
	return radius;
}

D3DXVECTOR2 BossA::getSize()
{
	return { BOSS_WIDTH, BOSS_HEIGHT };
}

D3DXVECTOR2 BossA::getPos()
{
	return { posX, posY };
}

void BossA::Hit(float damage)
{
	if (!isinit)
	{
		hp -= damage;
		hitTimer = 4;

	}
}

float BossA::getMaxHP()
{
	return maxHP;
}

float BossA::getHP()
{
	return hp;
}

int BossA::getClassType()
{
	return classType;
}