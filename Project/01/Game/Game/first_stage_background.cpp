#include "stdafx.h"
#include "first_stage_background.h"
#include "global.h"

#define BACKGROUND_WIDTH WINDOW_WIDTH
#define BACKGROUND_HEIGHT 950

FirstStageBackgound::FirstStageBackgound()
{
	posY = WINDOW_HEIGHT - BACKGROUND_HEIGHT;

}

void FirstStageBackgound::Update(bool isScral)
{
	if (isScral)
	{
		if (posY >= WINDOW_HEIGHT)
		{
			posY = WINDOW_HEIGHT - BACKGROUND_HEIGHT;
		}

		posY += 3.f;
	}
	
}

void FirstStageBackgound::Render()
{
	TextureElement* element = textureManager.getTexture(TEX_FIRST_STAGE_BACKGROUND);
	RECT rc;
	D3DXVECTOR3 pos;

	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = BACKGROUND_WIDTH;
	rc.bottom = BACKGROUND_HEIGHT;

	pos = { 0, posY, 0 };

	element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	pos = { 0, posY - BACKGROUND_HEIGHT, 0 };

	element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));


	pos = { 0, posY - BACKGROUND_HEIGHT - BACKGROUND_HEIGHT, 0 };

	element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	element->sprite->End();
	

}