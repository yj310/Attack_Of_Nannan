#include "stdafx.h"
#include "global.h"
#include "rank_stage.h"

#define BACKGROUND_WIDTH WINDOW_WIDTH
#define BACKGROUND_HEIGHT WINDOW_WIDTH

#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 80



RankStage::RankStage()
{
	classType = RANK_STAGE;

	buttonState = TEX_MAIN_BUTTON;
	
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

	
	Load();

	PlayerInfo temp;
	for (int i = 0; i < 5; i++)
	{
		for (int j = i + 1; j < 6; j++)
		{
			if (ranking[i].playerScore < ranking[j].playerScore)
			{
				temp = ranking[i];
				ranking[i] = ranking[j];
				ranking[j] = temp;
			}
		}
	}

	Save();
	
}

void RankStage::Load()
{
	FILE* fp = nullptr;

	fopen_s(&fp, "ranking.dat", "rt");

	if (fp != nullptr)
	{
		for (int i = 0; i < 5; ++i)
		{
			char name[128];
			int score;
			fscanf_s(fp, "%s %d", name, 128, &score);
			strcpy_s<128>(ranking[i].playerName, name);
			ranking[i].playerScore = score;
		}

		fclose(fp);
	}
}

void RankStage::Save()
{
	FILE* fp = nullptr;
	fopen_s(&fp, "ranking.dat", "wt");

	for (int i = 0; i < 5; ++i)
	{
		fprintf(fp, "%s %d\n", ranking[i].playerName, ranking[i].playerScore);
	}

	fclose(fp);
}

void RankStage::Update()
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





void RankStage::Render()
{
	TextureElement* element = textureManager.getTexture(TEX_RANK_BACKGROUND);
	RECT rc;
	D3DXVECTOR3 pos;
	WCHAR text[256];

	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = BACKGROUND_WIDTH;
	rc.bottom = BACKGROUND_HEIGHT;

	pos = { 0, 0, 0 };

	element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	element->sprite->End();

	
	rc.left = 100;
	rc.top = 350;
	rc.right = 15;
	rc.bottom = 15;
	for (int i = 0; i < 5; i++)
	{
		rc.left = 200;
		rc.top = 300 + i * 80;

		_stprintf_s<256>(text, _T("%d : "), i+1);
		font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
			D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));

		for (int j = 0; j < strlen(ranking[i].playerName); j++)
		{
			
			rc.left = 300 + 30 * j;
			_stprintf_s<256>(text, _T("%c"), ranking[i].playerName[j]);
			font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
				D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));
			
		}
		
		rc.left = 950;
		_stprintf_s<256>(text, _T("%d"), ranking[i].playerScore);
		font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
			D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));
	}
	
	rc.left = 100;
	rc.top = 800;

	char tex[] = "You : ";
	for (int i = 0; i < strlen(tex); i++)
	{
		rc.left = 200 + 30 * i;
		_stprintf_s<256>(text, _T("%c"), tex[i]);
		font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
			D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));


	}

	for (int i = 0; i < strlen(ranking[6].playerName);  i++)
	{
		rc.left = 400 + 30 * i;
		_stprintf_s<256>(text, _T("%c"), ranking[6].playerName[i]);
		font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
			D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));
	}

	rc.left = 950;
	_stprintf_s<256>(text, _T("%d"), ranking[6].playerScore);
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(0.21f, 0.05f, 0.35f, 1.0f));



	//버튼
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