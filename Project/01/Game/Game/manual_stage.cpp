#include "stdafx.h"
#include "global.h"
#include "manual_stage.h"

#define BACKGROUND_WIDTH WINDOW_WIDTH
#define BACKGROUND_HEIGHT WINDOW_WIDTH

#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 80


ManualStage::ManualStage()
{
	classType = MENUAL_STAGE;

	buttonState = TEX_MAIN_BUTTON;
}

void ManualStage::Update()
{

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(MyhWnd, &pt);

	if (pt.x > WINDOW_WIDTH * 0.9 - 100 && pt.x< WINDOW_WIDTH * 0.9 - 100 + BUTTON_WIDTH
		&& pt.y>WINDOW_HEIGHT * 0.9 && pt.y < WINDOW_HEIGHT * 0.9 + BUTTON_HEIGHT)
	{
		if (buttonState == TEX_MAIN_BUTTON)
		{
			soundManager.sndOnButton->Reset();
			soundManager.sndOnButton->Play(0, 0, 1);
		}
		buttonState = TEX_MAIN_BUTTON_BORD;
		if (inputManager.prevKeyBuffer[VK_LBUTTON] == 1 && inputManager.keyBuffer[VK_LBUTTON] == 0)
		{
			stageManager.CreateTitleStage();
		}
	}
	else
	{
		buttonState = TEX_MAIN_BUTTON;
	}
}

void ManualStage::Render()
{
	TextureElement* element = textureManager.getTexture(TEX_MANUAL_BACKGROUND);
	RECT rc;
	D3DXVECTOR3 pos;

	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = BACKGROUND_WIDTH;
	rc.bottom = BACKGROUND_HEIGHT;

	pos = { 0, 0, 0 };

	element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	element->sprite->End();

	//¹öÆ°
	element = textureManager.getTexture(buttonState);
	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);
	rc.left = 0;
	rc.top = 0;
	rc.right = 200;
	rc.bottom = 80;

	pos = { WINDOW_WIDTH * 0.9 - 100,WINDOW_HEIGHT * 0.9,0 };
	element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

	element->sprite->End();


}