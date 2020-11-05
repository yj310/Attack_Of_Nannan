#include "stdafx.h"
#include "result_texture.h"
#include "global.h"
#include "player.h"
#include "stage.h"
#include <string>

#define RESULT_TEXTURE_WIDTH 1150
#define RESULT_TEXTULRE_HEIGHT 800
#define ENTERTIMER 40

#define NUMBER_LINE 500
#define MULTIPLY_LINE 700

ResultTexture::ResultTexture()
{
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

	fontSize = 1;
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
		&font_Small);
	
	enterTimer = ENTERTIMER;

	//isFirstStage
}

void ResultTexture::Update()
{
	if (inputManager.prevKeyBuffer[VK_BACK] == 1
		&& inputManager.keyBuffer[VK_BACK] == 0)
	{
		if(cname.size() > 0)
			cname.pop_back();
	}
	if (inputManager.prevKeyBuffer[VK_RETURN] == 1
		&& inputManager.keyBuffer[VK_RETURN] == 0)
	{
		if (stageManager.currentStage->classType == FIRST_GAME_STAGE)
		{
			stageManager.CreateSecondStage();
		}
		else
		{
			std::string name(cname.begin(), cname.end());
			strcpy_s(ranking[5].playerName, name.c_str());
			ranking[5].playerScore = (score + ((gameSystem.player->hp) * 200) + (heartEat * 20));
			ranking[6] = ranking[5];
			stageManager.CreateRankStageB();
		}
		
	
		
	}
	for (int i = 'A'; i < 'Z'; i++)
	{
		if (inputManager.prevKeyBuffer[i] == 1
			&& inputManager.keyBuffer[i] == 0)
		{
			cname.push_back((char)i);
		}
	}

	if (enterTimer > -1 * ENTERTIMER)
	{
		enterTimer--;
	}
	else
	{
		enterTimer = ENTERTIMER;
	}
}

void ResultTexture::Render()
{
	TextureElement* element = textureManager.getTexture(TEX_RESULT_TEXTURE);
	RECT rc;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;
	WCHAR text[256];

	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = RESULT_TEXTURE_WIDTH;
	rc.bottom = RESULT_TEXTULRE_HEIGHT;

	pos = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0 };
	cen = { RESULT_TEXTURE_WIDTH / 2, RESULT_TEXTULRE_HEIGHT / 2, 0 };

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
	_stprintf_s<256>(text, _T(":  %d"), scoreFinal);
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));
	
	if (stageManager.currentStage->classType == FIRST_GAME_STAGE
		|| (stageManager.FadingCount > 0 && stageManager.prevStage->classType == FIRST_GAME_STAGE))
	{

		if (enterTimer <= 25)
		{
			rc.left = 500;
			rc.top = 840;
			rc.right = 15;
			rc.bottom = 15;
			_stprintf_s<256>(text, _T("press enter to Next Stage!"));
			font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
				D3DXCOLOR(0.21f, 0.05f, 0.35f, 0.1f));
		}
	}
	else
	{
		rc.left = 200;
		rc.top = 780;
		rc.right = 15;
		rc.bottom = 15;
		_stprintf_s<256>(text, _T("닉네임 입력: "));
		font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
			D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));

		for (int i = 0; i < cname.size(); i++)
		{
			rc.left = 530 + i * 35;
			rc.top = 780;
			rc.right = 750 + i * 35;
			rc.bottom = 15;
			_stprintf_s<256>(text, _T(" %c"), cname[i]);
			font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
				D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));

		}

		if (enterTimer <= 25)
		{
			rc.left = 600;
			rc.top = 840;
			rc.right = 15;
			rc.bottom = 15;
			_stprintf_s<256>(text, _T("press enter to finish!"));
			font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
				D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.1f));
		}
	}
	
	


}