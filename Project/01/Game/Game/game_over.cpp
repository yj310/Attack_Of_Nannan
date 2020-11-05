#include "stdafx.h"
#include "game_over.h"
#include "global.h"
#include "player.h"

#define GAME_OVER_TEXTURE_WIDTH 1150
#define GAME_OVER_TEXTULRE_HEIGHT 800

#define TITLE_BUTTON_X 980
#define TITLE_BUTTON_Y 780
#define TITLE_BUTTON_WIDTH 200
#define TITLE_BUTTON_HEIGHT 80


#define NUMBER_LINE 500
#define MULTIPLY_LINE 700

GameOver::GameOver()
{
	mainButtonState = TEX_MAIN_BUTTON_DARK;

	HDC hDC = GetDC(NULL);
	int nLogPixelsY = GetDeviceCaps(hDC, LOGPIXELSY);
	ReleaseDC(NULL, hDC);

	int fontSize = 30;
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
		&font);
}

void GameOver::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(MyhWnd, &pt);

	if (pt.x > TITLE_BUTTON_X&& pt.x < TITLE_BUTTON_X + TITLE_BUTTON_WIDTH && pt.y > TITLE_BUTTON_Y&& pt.y < TITLE_BUTTON_Y + TITLE_BUTTON_HEIGHT)
	{
		if (mainButtonState == TEX_MAIN_BUTTON_DARK)
		{
			soundManager.sndOnButton->Reset();
			soundManager.sndOnButton->Play(0, 0, 1);
		}
		mainButtonState = TEX_MAIN_BUTTON_DARK_BORD;
		if (inputManager.prevKeyBuffer[VK_LBUTTON] == 1
			&& inputManager.keyBuffer[VK_LBUTTON] == 0)
		{
			stageManager.CreateTitleStage();
		}
	}
	else
	{
		mainButtonState = TEX_MAIN_BUTTON_DARK;
	}



}

void GameOver::Render()
{
	TextureElement* element = textureManager.getTexture(TEX_GAME_OVER);
	RECT rc;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;
	WCHAR text[256];

	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = GAME_OVER_TEXTURE_WIDTH;
	rc.bottom = GAME_OVER_TEXTULRE_HEIGHT;

	pos = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0 };
	cen = { GAME_OVER_TEXTURE_WIDTH / 2, GAME_OVER_TEXTULRE_HEIGHT / 2, 0 };

	element->sprite->Draw(element->texture, &rc, &cen, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	element->sprite->End();


	rc.left = 200;
	rc.top = 350;
	rc.right = 15;
	rc.bottom = 15;

	_stprintf_s<256>(text, _T("기본 점수"));
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));


	rc.left = NUMBER_LINE;
	rc.top = 350;
	rc.right = 15;
	rc.bottom = 15;

	_stprintf_s<256>(text, _T(":  %d"), score);
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));

	rc.left = 200;
	rc.top = 450;
	rc.right = 15;
	rc.bottom = 15;
	_stprintf_s<256>(text, _T("먹은 하트"));
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));


	rc.left = NUMBER_LINE;
	rc.top = 450;
	rc.right = 15;
	rc.bottom = 15;
	_stprintf_s<256>(text, _T(":  %d"), heartEat);
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));

	rc.left = MULTIPLY_LINE;
	rc.top = 450;
	rc.right = 15;
	rc.bottom = 15;
	_stprintf_s<256>(text, _T(" * 20"));
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));

	rc.left = 200;
	rc.top = 550;
	rc.right = 15;
	rc.bottom = 15;
	_stprintf_s<256>(text, _T("남은 HP"));
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));

	rc.left = NUMBER_LINE;
	rc.top = 550;
	rc.right = 15;
	rc.bottom = 15;
	_stprintf_s<256>(text, _T(":  %d"), gameSystem.player->hp);
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));

	rc.left = MULTIPLY_LINE;
	rc.top = 550;
	rc.right = 15;
	rc.bottom = 15;
	_stprintf_s<256>(text, _T(" * 200"));
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));



	rc.left = 200;
	rc.top = 650;
	rc.right = 15;
	rc.bottom = 15;
	_stprintf_s<256>(text, _T("최종점수"));
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));

	rc.left = NUMBER_LINE;
	rc.top = 650;
	rc.right = 15;
	rc.bottom = 15;
	_stprintf_s<256>(text, _T(":  %d"), (score + (heartEat * 20)));
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));


	element = textureManager.getTexture(mainButtonState);
	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = TITLE_BUTTON_WIDTH;
	rc.bottom = TITLE_BUTTON_HEIGHT;

	pos = { TITLE_BUTTON_X, TITLE_BUTTON_Y, 0 };

	element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	element->sprite->End();
}