#include "stdafx.h"
#include "shield.h"
#include "global.h"

#define WIDTH 104


Shield::Shield(float x, float y)
{
	posX = x;
	posY = y;

	radious = 100;
}
void Shield::Update(float x, float y)
{
	posX = x;
	posY = y;
}

void Shield::Render( )
{
	TextureElement* element = textureManager.getTexture(SHIELD);
	RECT rc;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;

	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = 104;
	rc.bottom = 104;

	pos = { posX, posY, 0 };
	cen = { WIDTH / 2,WIDTH / 2,0 };

	element->sprite->Draw(element->texture, &rc, &cen, &pos, D3DCOLOR_XRGB(255, 255, 255));

	element->sprite->End();
}

D3DXVECTOR2 Shield::GetPos()
{
	return D3DXVECTOR2(posX, posY);
}

float Shield::GetRadiou()
{
	return radious;
}