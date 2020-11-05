#include "stdafx.h"
#include "waiting.h"
#include "global.h"
#include "player.h"

#define BACKGROUND_WIDTH 1150
#define BAGROUND_HEIGHT 800

#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 80

#define YES_BUTTON_X 400
#define YES_BUTTON_Y 800
#define NO_BUTTON_X 650
#define NO_BUTTON_Y 800


#define NUMBER_LINE 500

Waiting::Waiting()
{
	HDC hDC = GetDC(NULL);
	int nLogPixelsY = GetDeviceCaps(hDC, LOGPIXELSY);
	ReleaseDC(NULL, hDC);

	int fontSize = 20;
	TCHAR g_strFont[256];
	wcscpy_s(g_strFont, 32, L"둥근모꼴");

	int nHeight = -fontSize * nLogPixelsY / 72;
	D3DXCreateFont(g_pd3dDevice,
		nHeight,
		0,
		FW_BOLD,
		1,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		g_strFont,
		&font_Small);

	fontSize = 30;
	nHeight = -fontSize * nLogPixelsY / 72;
	D3DXCreateFont(g_pd3dDevice,
		nHeight,
		0,
		FW_BOLD,
		1,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		g_strFont,
		&font);

	yesState = YES;
	noState = NO;

}

void Waiting::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(MyhWnd, &pt);



	if (pt.x > YES_BUTTON_X&& pt.x < YES_BUTTON_X + BUTTON_WIDTH && pt.y > YES_BUTTON_Y&& pt.y < YES_BUTTON_Y + BUTTON_HEIGHT)
	{
		if (yesState == YES)
		{
			soundManager.sndOnButton->Reset();
			soundManager.sndOnButton->Play(0, 0, 1);
		}
		yesState = YES_BORD;
		if (inputManager.prevKeyBuffer[VK_LBUTTON] == 1 && inputManager.keyBuffer[VK_LBUTTON] == 0)
		{
			stageManager.CreateTitleStage();
		}
	}
	else
	{
		yesState = YES;
	}

	if (pt.x > NO_BUTTON_X&& pt.x < NO_BUTTON_X + BUTTON_WIDTH && pt.y > NO_BUTTON_Y&& pt.y < NO_BUTTON_Y + BUTTON_HEIGHT)
	{
		if (noState == NO)
		{
			soundManager.sndOnButton->Reset();
			soundManager.sndOnButton->Play(0, 0, 1);
		}
		noState = NO_BORD;
		if (inputManager.prevKeyBuffer[VK_LBUTTON] == 1 && inputManager.keyBuffer[VK_LBUTTON] == 0)
		{
			stageManager.currentStage->isPlaying = true;
		}
	}
	else
	{
		noState = NO;
	}
}

void Waiting::Render()
{
	TextureElement* elemet = textureManager.getTexture(WAITING_STAGE);
	RECT rc;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;
	WCHAR text[256];

	elemet->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = BACKGROUND_WIDTH;
	rc.bottom = BAGROUND_HEIGHT;

	pos = { WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2,0 };
	cen = { BACKGROUND_WIDTH / 2,BAGROUND_HEIGHT / 2,0 };

	elemet->sprite->Draw(elemet->texture, &rc, &cen, &pos, D3DCOLOR_XRGB(255, 255, 255));
	elemet->sprite->End();


	rc.left = 200;
	rc.top = 300;
	rc.right = 15;
	rc.bottom = 15;

	_stprintf_s<256>(text, _T("레벨"));
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));


	rc.left = NUMBER_LINE;
	rc.top = 300;
	rc.right = 15;
	rc.bottom = 15;

	_stprintf_s<256>(text, _T(":  %d"), Level);
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));


	rc.left = 200;
	rc.top = 380;
	rc.right = 15;
	rc.bottom = 15;

	_stprintf_s<256>(text, _T("Score"));
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));


	rc.left = NUMBER_LINE;
	rc.top = 380;
	rc.right = 15;
	rc.bottom = 15;

	_stprintf_s<256>(text, _T(":  %d"), score);
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));

	rc.left = 200;
	rc.top = 460;
	rc.right = 15;
	rc.bottom = 15;

	_stprintf_s<256>(text, _T("경험치"));
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));


	rc.left = NUMBER_LINE;
	rc.top = 460;
	rc.right = 15;
	rc.bottom = 15;

	_stprintf_s<256>(text, _T(":  %d"), Exp);
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));


	rc.left = 200;
	rc.top = 540;
	rc.right = 15;
	rc.bottom = 15;

	_stprintf_s<256>(text, _T("hp"));
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));


	rc.left = NUMBER_LINE;
	rc.top = 540;
	rc.right = 15;
	rc.bottom = 15;

	_stprintf_s<256>(text, _T(":  %d"), gameSystem.player->hp);
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));


	rc.left = 200;
	rc.top = 620;
	rc.right = 15;
	rc.bottom = 15;

	_stprintf_s<256>(text, _T("먹은 하트"));
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));


	rc.left = NUMBER_LINE;
	rc.top = 620;
	rc.right = 15;
	rc.bottom = 15;

	_stprintf_s<256>(text, _T(":  %d"), heartEat);
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));






	// 종료 메시지
	rc.left = 520;
	rc.top = 700;
	rc.right = 15;
	rc.bottom = 15;
	_stprintf_s<256>(text, _T("종료하시겠습니까?"));
	font_Small->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));

	//yes
	elemet = textureManager.getTexture(yesState);
	elemet->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = BUTTON_WIDTH;
	rc.bottom = BUTTON_HEIGHT;

	pos = { YES_BUTTON_X, YES_BUTTON_Y, 0 };
	cen = { 0 ,0 ,0 };

	elemet->sprite->Draw(elemet->texture, &rc, &cen, &pos, D3DCOLOR_XRGB(255, 255, 255));
	elemet->sprite->End();


	//no
	elemet = textureManager.getTexture(noState);
	elemet->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = BUTTON_WIDTH;
	rc.bottom = BUTTON_HEIGHT;

	pos = { NO_BUTTON_X, NO_BUTTON_Y, 0 };
	cen = { 0 ,0 ,0 };

	elemet->sprite->Draw(elemet->texture, &rc, &cen, &pos, D3DCOLOR_XRGB(255, 255, 255));
	elemet->sprite->End();








}