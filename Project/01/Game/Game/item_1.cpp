#include "item_1.h"
#include "global.h"
#include "player.h"

#define ITEM_WIDTH 30
#define ITEM_HEIGTH 61


Item1::Item1(float x, float y)
{
	velY = 3;
	isDead = false;
	isHit = false;
	classType = ITEM1;
	posX = x;
	posY = y;
}

void Item1::Update()
{
	
	if (posY >= WINDOW_HEIGHT)
	{
		isDead = true;
	}

	posY += velY;
}

void Item1::Render()
{
	TextureElement* element = textureManager.getTexture(TEX_PLAYER_ITEM_01);
	RECT rc;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;

	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 16;
	rc.top = 0;
	rc.right = 15+ITEM_WIDTH;
	rc.bottom = 16+ITEM_HEIGTH;

	pos = { posX,posY,0 };


	element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));
	element->sprite->End();

}

D3DXVECTOR2 Item1::GetPos()
{
	return D3DXVECTOR2(posX, posY);
}

float Item1::GetRadious()
{
	return 20;
}

int Item1::GetCalssType()
{
	return classType;
}

void Item1::SetIsHit(bool isHit)
{
	this->isHit = isHit;
}

bool Item1::GetIsHit()
{
	return isHit;
}

float Item1::GetWidth()
{
	return ITEM_WIDTH;
}

float Item1::GetHeight()
{
	return ITEM_HEIGTH;
}

bool Item1::IsDead()
{
	return isDead;
}