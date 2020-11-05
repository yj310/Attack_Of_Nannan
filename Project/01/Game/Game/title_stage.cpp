#include "stdafx.h"
#include "title_stage.h"
#include "global.h"
#include <ctime>


#define START_BUTTON_X 1000
#define START_BUTTON_Y 600
#define START_BUTTON_WIDTH 200
#define START_BUTTON_HEIGHT 80

#define MANUAL_BUTTON_X 1000
#define MANUAL_BUTTON_Y 700
#define MANUAL_BUTTON_WIDTH 200
#define MANUAL_BUTTON_HEIGHT 80

#define RANK_BUTTON_X 1000
#define RANK_BUTTON_Y 800
#define RANK_BUTTON_WIDTH 200
#define RANK_BUTTON_HEIGHT 80

#define BREAK_BUTTON_X 1000
#define BREAK_BUTTON_Y 900
#define BREAK_BUTTON_WIDTH 200
#define BREAK_BUTTON_HEIGHT 80

TitleStage::TitleStage()
{
	classType = TITLE_STAGE;
	startButtonState = TEX_START_BUTTON;
	manualButtonState = TEX_MANUAL_BUTTON;
	breakButtonState = TEX_BREAK_BUTTON;
	rankButtonState = TEX_RANK_BUTTON;
	isScral = false;
	srand((unsigned int)time(NULL));
	randTextTitle = TEX_TITLE_BACKGROUND_BOSSA + rand() % 8;
}

void TitleStage::Update()
{

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(MyhWnd, &pt);

	// startButton
	if (pt.x > START_BUTTON_X && pt.x < START_BUTTON_X + START_BUTTON_WIDTH
		&& pt.y > START_BUTTON_Y && pt.y < START_BUTTON_Y + START_BUTTON_HEIGHT)
	{
		if (startButtonState == TEX_START_BUTTON)
		{
			soundManager.sndOnButton->Reset();
			soundManager.sndOnButton->Play(0, 0, 0.0001);
		}
		startButtonState = TEX_START_BUTTON_BORD;

		
		if (inputManager.prevKeyBuffer[VK_LBUTTON] == 1
			&& inputManager.keyBuffer[VK_LBUTTON] == 0)
		{
			// game start..
			stageManager.CreateTutorial();

		}
	}
	else
	{
		startButtonState = TEX_START_BUTTON;
	}

	// manualButton
	if (pt.x > MANUAL_BUTTON_X && pt.x < MANUAL_BUTTON_X + MANUAL_BUTTON_WIDTH
		&& pt.y > MANUAL_BUTTON_Y && pt.y < MANUAL_BUTTON_Y + MANUAL_BUTTON_HEIGHT)
	{
		if (manualButtonState == TEX_MANUAL_BUTTON)
		{
			soundManager.sndOnButton->Reset();
			soundManager.sndOnButton->Play(0, 0, 1);
		}
		manualButtonState = TEX_MANUAL_BUTTON_BORD;
		
		if (inputManager.prevKeyBuffer[VK_LBUTTON] == 1
			&& inputManager.keyBuffer[VK_LBUTTON] == 0)
		{
			stageManager.CreateManualStage();
		}
	}
	else
	{
		manualButtonState = TEX_MANUAL_BUTTON;
	}
	

	// rankButton
	if (pt.x > RANK_BUTTON_X && pt.x < RANK_BUTTON_X + RANK_BUTTON_WIDTH
		&& pt.y > RANK_BUTTON_Y && pt.y < RANK_BUTTON_Y + RANK_BUTTON_HEIGHT)
	{
		if (rankButtonState == TEX_RANK_BUTTON)
		{
			soundManager.sndOnButton->Reset();
			soundManager.sndOnButton->Play(0, 0, 1);
		}
		rankButtonState = TEX_RANK_BUTTON_BORD;
		
		if (inputManager.prevKeyBuffer[VK_LBUTTON] == 1
			&& inputManager.keyBuffer[VK_LBUTTON] == 0)
		{
			stageManager.CreateRankStage();
		}
	}
	else
	{
		rankButtonState = TEX_RANK_BUTTON;
	}

	// breakButton
	if (pt.x > BREAK_BUTTON_X && pt.x < BREAK_BUTTON_X + BREAK_BUTTON_WIDTH
		&& pt.y > BREAK_BUTTON_Y && pt.y < BREAK_BUTTON_Y + BREAK_BUTTON_HEIGHT)
	{
		if (breakButtonState == TEX_BREAK_BUTTON)
		{
			soundManager.sndOnButton->Reset();
			soundManager.sndOnButton->Play(0, 0, 1);
		}
		breakButtonState = TEX_BREAK_BUTTON_BORD;
		
		if (inputManager.prevKeyBuffer[VK_LBUTTON] == 1
			&& inputManager.keyBuffer[VK_LBUTTON] == 0)
		{
			PostQuitMessage(0);
		}
	}
	else
	{
		breakButtonState = TEX_BREAK_BUTTON;
	}
}

void TitleStage::Render()
{
	// background
	
	TextureElement* element = textureManager.getTexture(randTextTitle);
	RECT rc;
	D3DXVECTOR3 pos;

	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = WINDOW_WIDTH;
	rc.bottom = WINDOW_HEIGHT;

	pos = { 0, 0, 0 };

	element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	element->sprite->End();

	// startButton
	element = textureManager.getTexture(startButtonState);

	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = START_BUTTON_WIDTH;
	rc.bottom = START_BUTTON_HEIGHT;

	pos = { START_BUTTON_X, START_BUTTON_Y, 0 };

	element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	element->sprite->End();

	// ManualButton
	element = textureManager.getTexture(manualButtonState);

	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = MANUAL_BUTTON_WIDTH;
	rc.bottom = MANUAL_BUTTON_HEIGHT;

	pos = { MANUAL_BUTTON_X, MANUAL_BUTTON_Y, 0 };

	element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	element->sprite->End();


	// rankButton
	element = textureManager.getTexture(rankButtonState);

	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = RANK_BUTTON_WIDTH;
	rc.bottom = RANK_BUTTON_HEIGHT;

	pos = { RANK_BUTTON_X, RANK_BUTTON_Y, 0 };

	element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	element->sprite->End();

	// breakButton
	element = textureManager.getTexture(breakButtonState);

	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = BREAK_BUTTON_WIDTH;
	rc.bottom = BREAK_BUTTON_HEIGHT;

	pos = { BREAK_BUTTON_X, BREAK_BUTTON_Y, 0 };

	element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	element->sprite->End();

}