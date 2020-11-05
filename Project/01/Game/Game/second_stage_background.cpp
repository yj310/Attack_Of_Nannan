#include "stdafx.h"
#include "second_stage_background.h"
#include "global.h"

#define BACKGROUND_WIDTH WINDOW_WIDTH
#define BACKGROUND_HEIGHT 950

SecondStageBackground::SecondStageBackground()
{
	posY = WINDOW_HEIGHT - BACKGROUND_HEIGHT;
}


void SecondStageBackground::Update(bool isScral)
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

void SecondStageBackground::Render()
{
	TextureElement* element = textureManager.getTexture(TEX_SECOND_STAGE_BACKGROUND);
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