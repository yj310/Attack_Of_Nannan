#pragma once

#include <d3dx9.h>
#include <d3dx9core.h>

#include "input_manager.h"
#include "texture_manager.h"
#include "stage_manager.h"
#include "game_system.h"
#include <vector>

#include "SDKsound.h"

using namespace std;

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 1024


#define STRIGHT 555
#define ROUND 666


#define FIRST_LEVEL_2_EX 50
#define FIRST_LEVEL_3_EX 150
#define FIRST_LEVEL_4_EX 300
#define FIRST_LEVEL_5_EX 500


// class Type
#define FIRST_GAME_STAGE 2000
#define SECOND_GAME_STAGE 2001
#define ENEMY_A 2002
#define ENEMY_B 2003
#define ENEMY_C 2004
#define ENEMY_D 2005
#define BOSS_A 2006
#define BOSS_B 2007
#define BOSS_C 2008
#define BOSS_D 2009
#define TITLE_STAGE 2010
#define RANK_STAGE 2011
#define MENUAL_STAGE 2012
#define TUTORIAL 2013
#define ITEM1 2014
#define ITEM2 2015

// texture id

#define TEX_MAIN_BUTTON 1
#define TEX_MAIN_BUTTON_BORDER 2
#define TEX_BOMB 3


#define TEX_1ND 10
#define TEX_2ND 20
#define TEX_3ND 30

#define TEX_TITLE_BACKGROUND_BOSSA 100
#define TEX_TITLE_BACKGROUND_BOSSB 101
#define TEX_TITLE_BACKGROUND_BOSSC 102
#define TEX_TITLE_BACKGROUND_BOSSD 103
#define TEX_TITLE_BACKGROUND_ENEMYA 104
#define TEX_TITLE_BACKGROUND_ENEMYB 105
#define TEX_TITLE_BACKGROUND_ENEMYC 106
#define TEX_TITLE_BACKGROUND_ENEMYD 107

#define TEX_TITLE_BACKGROUND 1000
#define TEX_FIRST_STAGE_BACKGROUND 1001
#define TEX_SECOND_STAGE_BACKGROUND 1002
#define TEX_RESULT_TEXTURE 1003
#define TEX_RANK_BACKGROUND 1005
#define TEX_GAME_OVER 1006
#define TEX_MANUAL_BACKGROUND 1007
#define TEX_FADING 1009

#define TEX_TUTORIAL_SHOOT 1500
#define TEX_TUTORIAL_HEART 1501
#define TEX_TUTORIAL_LEVEL 1502
#define TEX_TUTORIAL_EXP 1503
#define TEX_TUTORIAL_HP 1504

#define TEX_START_BUTTON 1200
#define TEX_START_BUTTON_BORD 1201
#define TEX_MANUAL_BUTTON 1202
#define TEX_MANUAL_BUTTON_BORD 1203
#define TEX_RANK_BUTTON 1206
#define TEX_RANK_BUTTON_BORD 1207
#define TEX_BREAK_BUTTON 1208
#define TEX_BREAK_BUTTON_BORD 1209
#define TEX_MAIN_BUTTON 1210
#define TEX_MAIN_BUTTON_BORD 1211
#define TEX_MAIN_BUTTON_DARK 1212
#define TEX_MAIN_BUTTON_DARK_BORD 1213

#define TEX_LEVEL_PACAGE 1250
#define TEX_LEVEL_1 1250
#define TEX_LEVEL_2 1251
#define TEX_LEVEL_3 1252
#define TEX_LEVEL_4 1253
#define TEX_LEVEL_5 1254
#define TEX_EXP_01 1256
#define TEX_EXP_02 1257
#define TEX_PLAYER_HP 1258
#define TEX_PLAYER_HP_BROKEN 1259
#define TEX_PLAYER_SKIL_01 1260
#define TEX_PLAYER_SKIL_02 1261
#define TEX_BOSS_A_HP_BAR 1262
#define TEX_BOSS_A_HP 1263
#define TEX_PLAYER_SKIL_CASE 1264
#define TEX_PLAYER_ITEM_01 1265
#define TEX_PLAYER_ITEM_02 1266

#define TEX_PLAYER 1300
#define TEX_PLAYER_BULLET_01 1301
#define TEX_PLAYER_BULLET_02 1302
#define TEX_ENEMY_A 1303
#define TEX_ENEMY_B 1304
#define TEX_ENEMY_C 1305
#define TEX_ENEMY_D 1306
#define TEX_BOSS_A 1307
#define TEX_BOSS_B 1308
#define TEX_BOSS_C 1309
#define TEX_BOSS_D 1310
#define TEX_ENEMY_BULLET 1311

#define TEX_BOSSA_BULLET BOSS_A
#define TEX_BOSSB_BULLET BOSS_B
#define TEX_BOSSC_BULLET BOSS_C
#define TEX_BOSSD_BULLET BOSS_D




#define WAITING_STAGE	3000
#define NO 4000
#define NO_BORD 4100
#define YES 5000
#define YES_BORD 5100

#define SHIELD 6000


extern LPDIRECT3D9 g_pD3D;
extern LPDIRECT3DDEVICE9 g_pd3dDevice;

extern HWND MyhWnd;
extern float deltaTime;
extern int Exp;
extern int Level;
extern int score;
extern int scoreFinal;
extern int heartEat;

// all the managers...
extern InputManager inputManager;
extern TextureManager textureManager;
extern StageManager stageManager;
extern GameSystem gameSystem;
extern CSoundManager soundManager;


class PlayerInfo
{
public:
	char playerName[128];
	int playerScore;
};


extern PlayerInfo ranking[7];