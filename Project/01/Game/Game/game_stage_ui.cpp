#include "stdafx.h"
#include "game_stage_ui.h"
#include "global.h"
#include "player.h"
#include "stage.h"

#define LEVEL_TEXTURE_WIDTH 62
#define LEVEL_TEXTURE_HEIGHT 62
#define EXP_TEXTURE_WIDTH 1024
#define EXP_TEXTURE_HEIGHT 32
#define PLAYER_HP_WIDTH 33
#define PLAYER_HP_HEIGHT 33
#define SKIL_CASE_WIDTH WINDOW_WIDTH - 100 - 40

GameStageUI::GameStageUI()
{
	HDC hDC = GetDC(NULL);
	int nLogPixelsY = GetDeviceCaps(hDC, LOGPIXELSY);
	ReleaseDC(NULL, hDC);

	int fontSize = 20;
	TCHAR g_strFont[256];
	wcscpy_s(g_strFont, 32, L"둥근모꼴");

	int nHeight = -fontSize * nLogPixelsY / 72;
	D3DXCreateFont(g_pd3dDevice,
		nHeight,               // Height
		0,                     // Width
		FW_BOLD,               // Weight
		1,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		g_strFont,
		&font);
}


void GameStageUI::Update()
{

}

void GameStageUI::Render()
{
	TextureElement* element;
	RECT rc;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;
	WCHAR text[256];

	// 레벨
	element = textureManager.getTexture(TEX_LEVEL_PACAGE + Level - 1);
	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = LEVEL_TEXTURE_WIDTH;
	rc.bottom = LEVEL_TEXTURE_HEIGHT;

	pos = { 30, 20, 0 };

	element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	element->sprite->End();


	rc.left = 0;
	rc.top = 0;
	rc.right = EXP_TEXTURE_WIDTH;
	rc.bottom = EXP_TEXTURE_HEIGHT;

	// 경험치 바 경험치
	element = textureManager.getTexture(TEX_EXP_02);
	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.right = EXP_TEXTURE_WIDTH / FIRST_LEVEL_5_EX * Exp;
	if (stageManager.currentStage->isDone)
		rc.right = EXP_TEXTURE_WIDTH;
	pos = { WINDOW_WIDTH / 2, 10, 0 };
	cen = { EXP_TEXTURE_WIDTH / 2 , 0, 0 };

	element->sprite->Draw(element->texture, &rc, &cen, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	element->sprite->End();

	// 경험치 바 배경
	element = textureManager.getTexture(TEX_EXP_01);
	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = EXP_TEXTURE_WIDTH;
	rc.bottom = EXP_TEXTURE_HEIGHT;

	pos = { WINDOW_WIDTH / 2, 10, 0 };


	element->sprite->Draw(element->texture, &rc, &cen, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	element->sprite->End();



	if (gameSystem.middleBoss != nullptr)
	{
		// HP바
		element = textureManager.getTexture(TEX_BOSS_A_HP_BAR);
		element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		rc.left = 0;
		rc.top = 0;
		rc.right = 250;
		rc.bottom = 5;


		pos = { gameSystem.middleBoss->getPos().x, gameSystem.middleBoss->getPos().y + 120, 0 };
		cen = { 250 / 2 , 0, 0 };

		element->sprite->Draw(element->texture, &rc, &cen, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

		element->sprite->End();

		// HP
		element = textureManager.getTexture(TEX_BOSS_A_HP);
		element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

		rc.right = gameSystem.middleBoss->getHP();
		element->sprite->Draw(element->texture, &rc, &cen, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

		element->sprite->End();
	}

	if (gameSystem.finalBoss != nullptr)
	{
		// HP바
		element = textureManager.getTexture(TEX_BOSS_A_HP_BAR);
		element->sprite->Begin(D3DXSPRITE_ALPHABLEND);
		rc.left = 0;
		rc.top = 0;
		rc.right = 500;
		rc.bottom = 5;


		pos = { gameSystem.finalBoss->getPos().x,gameSystem.finalBoss->getPos().y + 200, 0 };
		cen = { 500 / 2 , 0, 0 };

		element->sprite->Draw(element->texture, &rc, &cen, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

		element->sprite->End();

		// HP
		element = textureManager.getTexture(TEX_BOSS_A_HP);
		element->sprite->Begin(D3DXSPRITE_ALPHABLEND);


		rc.right = gameSystem.finalBoss->getHP();
		element->sprite->Draw(element->texture, &rc, &cen, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

		element->sprite->End();

	}


	// 스킬 케이스
	element = textureManager.getTexture(TEX_PLAYER_SKIL_CASE);
	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = 100;
	rc.bottom = 236;

	pos = { SKIL_CASE_WIDTH, WINDOW_HEIGHT - 236 - 200, 0 };

	element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	element->sprite->End();

	// 스킬 1
	element = textureManager.getTexture(TEX_PLAYER_SKIL_01);
	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = 80;
	rc.bottom = 80;

	pos = { SKIL_CASE_WIDTH + 10, WINDOW_HEIGHT - 239 - 200 + 30, 0 };

	if (gameSystem.player->skilTime1 == -1)
		element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_ARGB(255, 150, 150, 150));
	else if (gameSystem.player->skilTime1 == 0)
		element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	else
	{
		element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_ARGB(255, 150, 150, 150));
		/*if (gameSystem.player->clickToUse1 > 0)
		{
			rc.left = 1030;
			rc.top = 110;
			rc.right = 1145;
			rc.bottom = 130;
			_stprintf_s<256>(text, _T("아직 사용할 수 없습니다"));
			font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
				D3DXCOLOR(1, 1, 1, 1));
		}*/
	}
	element->sprite->End();

	if (gameSystem.player->skilTime1 > 0)
	{
		rc.left = SKIL_CASE_WIDTH + 10;
		rc.top = WINDOW_HEIGHT - 239 - 200 + 30;
		rc.right = 20;
		rc.bottom = 20;
		_stprintf_s<256>(text, _T("%d"), gameSystem.player->skilTime1);
		font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
			D3DXCOLOR(1, 1, 1, 1));
	}


	// 스킬 2
	element = textureManager.getTexture(TEX_PLAYER_SKIL_02);
	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = 80;
	rc.bottom = 80;

	pos = { SKIL_CASE_WIDTH + 10 , WINDOW_HEIGHT - 239 - 200 + 30 + 100, 0 };

	if (gameSystem.player->skilTime2 == -1)
		element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_ARGB(255, 150, 150, 150));
	else if (gameSystem.player->skilTime2 == 0)
		element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	else
	{
		element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_ARGB(255, 150, 150, 150));

	}
	element->sprite->End();

	if (gameSystem.player->skilTime2 > 0)
	{
		rc.left = SKIL_CASE_WIDTH + 10;
		rc.top = WINDOW_HEIGHT - 239 - 200 + 30 + 100;
		rc.right = 20;
		rc.bottom = 20;
		_stprintf_s<256>(text, _T("%d"), gameSystem.player->skilTime2);
		font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
			D3DXCOLOR(1, 1, 1, 1));
	}

	// hp
	rc.left = 0;
	rc.top = 0;
	rc.right = PLAYER_HP_WIDTH;
	rc.bottom = PLAYER_HP_HEIGHT;

	element = textureManager.getTexture(TEX_PLAYER_HP);
	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	for (int i = 0; i < gameSystem.player->hp; i++)
	{
		pos.x = 140 + i * 40;
		pos.y = 60;
		element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	}
	element->sprite->End();

	element = textureManager.getTexture(TEX_PLAYER_HP_BROKEN);
	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	for (int i = gameSystem.player->hp; i < gameSystem.player->maxHP; i++)
	{
		pos.x = 140 + i * 40;
		pos.y = 60;
		element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	}
	element->sprite->End();


	element = textureManager.getTexture(TEX_PLAYER_HP_BROKEN);

	// score
	rc.left = 10;
	rc.top = 100;
	rc.right = 30;
	rc.bottom = 270;
	_stprintf_s<256>(text, _T("score: %d"), score);
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(1, 1, 1, 1));
	// 먹은 하트
	rc.left = 10;
	rc.top = 140;
	rc.right = 30;
	rc.bottom = 290;
	_stprintf_s<256>(text, _T("heart: %d"), heartEat);
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(1, 1, 1, 1));

	///
	/*float d = gameSystem.pBulletBDamage;

	rc.left = 10;
	rc.top = 180;
	rc.right = 30;
	rc.bottom = 300;
	_stprintf_s<256>(text, _T("bulletDamage: %f"), d);
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(1, 1, 1, 1));


	EnemyA* e = new EnemyA();
	float h = e->hp;

	rc.left = 10;
	rc.top = 210;
	rc.right = 30;
	rc.bottom = 330;
	_stprintf_s<256>(text, _T("hp: %f"), h);
	font->DrawText(NULL, text, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(1, 1, 1, 1));*/
}