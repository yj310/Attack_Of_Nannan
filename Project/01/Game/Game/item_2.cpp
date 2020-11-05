#include "item_2.h"
#include "global.h"
#include "player.h"

#define ITEM_WIDTH 50
#define ITEM_HEIGTH 50


Item2::Item2(float x, float y)
{
	
	isDead = false;
	isHit = false;
	classType = ITEM2;
	posX = x;
	posY = y;
}

void Item2::Update()
{
	if (posY >= WINDOW_HEIGHT)
	{
		isDead = true;
	}

	posY += 3;
}

void Item2::Render()
{
	TextureElement* element = textureManager.getTexture(TEX_PLAYER_ITEM_02);
	RECT rc;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;

	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 5;
	rc.top = 0;
	rc.right = 5+ITEM_WIDTH;
	rc.bottom =7+ ITEM_HEIGTH;

	pos = { posX,posY,0 };


	element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));
	element->sprite->End();

}

D3DXVECTOR2 Item2::GetPos()
{
	return D3DXVECTOR2(posX, posY);
}

float Item2::GetRadious()
{
	return 25;
}

int Item2::GetCalssType()
{
	return classType;
}


void Item2::SetIsHit(bool isHit)
{

}

bool Item2::GetIsHit()
{
	return isHit;
}

float Item2::GetWidth()
{
	return ITEM_WIDTH;
}

float Item2::GetHeight()
{
	return ITEM_HEIGTH;
}


bool Item2::IsDead()
{
	return isDead;
}