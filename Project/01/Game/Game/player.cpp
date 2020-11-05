#include "stdafx.h"
#include "player.h"
#include "global.h"
#include "stage.h"

#define PLAYER_WIDTH 65
#define PLAYER_HEIGHT 100

Player::Player()
{
	posX = WINDOW_WIDTH / 2.f;
	posY = WINDOW_HEIGHT * 0.8f;
	isDead = false;
	radius = 30;
	speed = 350.f;
	//speed = 500.f;
	maxHP = 5;
	hp = maxHP;
	brokenHP = 0;
	damage = Level;
	maxShoutCount2 = 20;  //방사형
	maxShoutCount1 = 5;  //직사형
	shoutCount1 = 0;
	shoutCount2 = 0;
	dontHit = false;
	bulletType = TEX_PLAYER_BULLET_01;
	skilMaxTime1 = 10;
	skilMaxTime2 = 20;
	skilTime1 = -1;
	skilTime2 = -1;
	skilUseTime1 = 0;
	skilUseTime1 = 0;
	clickToUse1 = 0;
	clickToUse1 = 0;
	time = 1;
	hitTimer = 0;
}

void Player::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(MyhWnd, &pt);

	if (posX < 0+PLAYER_WIDTH/2)
		posX = PLAYER_WIDTH / 2;
	if (posX > WINDOW_WIDTH-PLAYER_WIDTH/2)
		posX = WINDOW_WIDTH - PLAYER_WIDTH / 2;
	if (posY < 0)
		posY = 0;
	if (posY > WINDOW_HEIGHT-PLAYER_HEIGHT/2)
		posY = WINDOW_HEIGHT - PLAYER_HEIGHT/2;
	if(shoutCount1 != 0)
		shoutCount1--;
	if (shoutCount2 != 0)
		shoutCount2--;

	if (inputManager.keyBuffer[VK_LEFT] == 1)
	{
		posX -= speed * deltaTime;
	}
	if (inputManager.keyBuffer[VK_RIGHT] == 1)
	{
		posX += speed * deltaTime;
	}
	if (inputManager.keyBuffer[VK_UP] == 1)
	{
		posY -= speed * deltaTime;
	}
	if (inputManager.keyBuffer[VK_DOWN] == 1)
	{
		posY += speed * deltaTime;
	}


	if (inputManager.keyBuffer['Z'] == 1 && inputManager.prevKeyBuffer['Z'] == 0)
	{
		//if (pt.x > WINDOW_WIDTH - 100 - 40 && pt.x < WINDOW_WIDTH - 100 - 40+80
		//	&& pt.y > WINDOW_HEIGHT - 440 - 200 + 30 && pt.y < WINDOW_HEIGHT - 440 - 200 + 30+80)
		//{
		//	if (skilTime1 == 0)
		//	{
		//		// 스킬 1 사용
		//		skilUseTime1 = 5;
		//		skilTime1 = skilMaxTime1;
		//		gameSystem.GenerateShield(posX, posY);

		//	}
		//	else if (skilTime1 > 0)
		//	{
		//		clickToUse1 = 50;
		//	}
		//}
		//else if (pt.x > 1160 && pt.x < 1160 + 50
		//	&& pt.y > 40 && pt.y < 40 + 50)
		//{
		//	if (skilTime2 == 0)
		//	{
		//		// 스킬 2 사용
		//		skilUseTime2 = 3;
		//		skilTime2 = skilMaxTime2;
		//	}
		//	else if (skilTime2 > 0)
		//	{
		//		clickToUse2 = 50;
		//	}
		////}

		if (bulletType == TEX_PLAYER_BULLET_02 && shoutCount2 <= 0)
		{
			gameSystem.GeneratePlayerBulletB(posX, posY);
			shoutCount2 = maxShoutCount2;

		}
		else if(bulletType == TEX_PLAYER_BULLET_01 && shoutCount1 <= 0)
		{
			soundManager.sndShootBullet01->Reset();
			soundManager.sndShootBullet01->Play();

			gameSystem.GeneratePlayerBulletA(posX+20, posY);
			gameSystem.GeneratePlayerBulletA(posX-20, posY);
			gameSystem.GeneratePlayerBulletA(posX, posY);
			shoutCount1 = maxShoutCount1;
		}
		
		
	}
	
	//실드
	if (inputManager.prevKeyBuffer['S'] == 1 && inputManager.keyBuffer['S'] == 0)
	{
		if (skilTime1 == 0)
		{
			skilUseTime1 = 5;
			skilTime1 = skilMaxTime1;
			gameSystem.GenerateShield(posX, posY);

		}
		else if (skilTime1 > 0)
		{
			clickToUse1 = 50;
		}
	}

	if (inputManager.prevKeyBuffer['A'] == 1 && inputManager.keyBuffer['A'] == 0)
	{
		if (skilTime2 == 0)
		{
			skilUseTime2 = 5;
			skilTime2 = skilMaxTime2;
			gameSystem.GenerateBomb(posX, posY);
		}
	}

	
	
	time -= deltaTime;
	if (time <= 0)
	{
		time = 1;
		if (skilUseTime1 > 0)
		{
			skilUseTime1--;
		}
		if (skilTime1 > 0)
		{
			skilTime1--;
		}
		if (skilTime2 > 0)
		{
			skilTime2--;
		}
		
	}
	if (clickToUse1 > 0)
		clickToUse1--;
	if (clickToUse2 > 0)
		clickToUse2--;


	hitTimer -= deltaTime;
	if (hitTimer <= 0)
	{
		hitTimer = 0;
		dontHit = false;
	}

	hp = maxHP - brokenHP;
}

void Player::Render()
{
	TextureElement* element = textureManager.getTexture(TEX_PLAYER);
	RECT rc;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;

	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = PLAYER_WIDTH;
	rc.bottom = PLAYER_HEIGHT;

	pos = { posX, posY, 0 };
	cen = { PLAYER_WIDTH / 2, PLAYER_HEIGHT / 2, 0 };

	if (hitTimer > 0)
	{
		int randv = rand() % 10;
		if (randv % 2 == 0)
		{
			//element->sprite->Draw(element->texture, &rc, &cen, &pos, D3DCOLOR_XRGB(255, 0, 0));
		}
		else
		{
			element->sprite->Draw(element->texture, &rc, &cen, &pos, D3DCOLOR_XRGB(255, 255, 255));
		}

	}
	else
	{
		element->sprite->Draw(element->texture, &rc, &cen, &pos, D3DCOLOR_XRGB(255, 255, 255));
	}


	element->sprite->End();
}


bool Player::IsDead()
{
	return isDead;
}

D3DXVECTOR2 Player::getSize()
{
	return { PLAYER_WIDTH , PLAYER_HEIGHT };
}

D3DXVECTOR2 Player::getPos()
{
	return { posX, posY };
}

float Player::getRadius()
{
	return radius;
}

void Player::Hit(float damage)
{
	if (!dontHit )
	{
		if (hitTimer <= 0)
		{
			soundManager.sndHitPlayer->Reset();
			soundManager.sndHitPlayer->Play();
			brokenHP+=damage;
			hitTimer = 1;
		}
	}
	
	
}

void Player::Reset()
{
	Level = 1;
	posX = WINDOW_WIDTH / 2.f;
	posY = WINDOW_HEIGHT * 0.8f;
	isDead = false;
	radius = 80;
	speed = 300.f;
	maxHP = 5;
	hp = maxHP;
	brokenHP = 0;
	damage = Level;
	shoutCount1 = 0;
	shoutCount2 = 0;
	dontHit = false;
	bulletType = TEX_PLAYER_BULLET_01;
	skilMaxTime1 = 15;
	skilMaxTime2 = 20;
	skilTime1 = -1;
	skilTime2 = -1;
	skilUseTime1 = 0;
	skilUseTime1 = 0;
	clickToUse1 = 0;
	clickToUse1 = 0;
	heartEat = 0;

	Exp = 0;
	if (!(stageManager.prevStage->classType == FIRST_GAME_STAGE
		&& stageManager.currentStage->classType == SECOND_GAME_STAGE))
	{
		score = 0;
	}
	
}
