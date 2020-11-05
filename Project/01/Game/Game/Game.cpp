#include "Game.h"

#include <Windows.h>

#include "global.h"

#include "cheat.h"


#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9   g_pd3dDevice = NULL;

InputManager inputManager;
TextureManager textureManager;
StageManager stageManager;
GameSystem gameSystem;
CSoundManager soundManager;
PlayerInfo ranking[7];

Cheat cheats;

HWND MyhWnd;

float deltaTime = 0.3f;
DWORD prevTime;

int Exp = 0;
int Level = 1;
int score = 0;
int scoreFinal = 0;
int heartEat = 0;


HRESULT InitD3D(HWND hWnd)
{
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	/*d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;*/

	d3dpp.Windowed = false;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferWidth = WINDOW_WIDTH;
	d3dpp.BackBufferHeight = WINDOW_HEIGHT;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}


	return S_OK;
}

void InitSound(HWND hWnd)
{
	soundManager.Initialize(hWnd, DSSCL_NORMAL);

	{
		WCHAR fileName[MAX_PATH];
		swprintf_s<MAX_PATH>(fileName, L"sound/BGM/titleStage.wav");
		soundManager.Create(&soundManager.BGMTitleStage, fileName);
	}
	{
		WCHAR fileName[MAX_PATH];
		swprintf_s<MAX_PATH>(fileName, L"sound/snd/onButton.wav");
		soundManager.Create(&soundManager.sndOnButton, fileName, DSBCAPS_CTRLVOLUME);
	}
	{
		WCHAR fileName[MAX_PATH];
		swprintf_s<MAX_PATH>(fileName, L"sound/BGM/firstStage.wav");
		soundManager.Create(&soundManager.BGMFirstStage, fileName, DSBCAPS_CTRLVOLUME);
	}
	{
		WCHAR fileName[MAX_PATH];
		swprintf_s<MAX_PATH>(fileName, L"sound/BGM/secondStage.wav");
		soundManager.Create(&soundManager.BGMSecondStage, fileName, DSBCAPS_CTRLVOLUME);
	}
	{
		WCHAR fileName[MAX_PATH];
		swprintf_s<MAX_PATH>(fileName, L"sound/snd/shootBullet01.wav");
		soundManager.Create(&soundManager.sndShootBullet01, fileName, DSBCAPS_CTRLVOLUME);
	}
	{
		WCHAR fileName[MAX_PATH];
		swprintf_s<MAX_PATH>(fileName, L"sound/snd/hitPlayer.wav");
		soundManager.Create(&soundManager.sndHitPlayer, fileName, DSBCAPS_CTRLVOLUME);
	}
	{
		WCHAR fileName[MAX_PATH];
		swprintf_s<MAX_PATH>(fileName, L"sound/snd/dieEnemy.wav");
		soundManager.Create(&soundManager.sndDieEnemy, fileName, DSBCAPS_CTRLVOLUME);
	}
	{
		WCHAR fileName[MAX_PATH];
		swprintf_s<MAX_PATH>(fileName, L"sound/snd/dieEnemy.wav");
		soundManager.Create(&soundManager.sndDieBoss, fileName, DSBCAPS_CTRLVOLUME);
	}
	{
		WCHAR fileName[MAX_PATH];
		swprintf_s<MAX_PATH>(fileName, L"sound/snd/hitEnemy.wav");
		soundManager.Create(&soundManager.sndHitEnemy, fileName, DSBCAPS_CTRLVOLUME);
	}
	{
		WCHAR fileName[MAX_PATH];
		swprintf_s<MAX_PATH>(fileName, L"sound/BGM/rank.wav");
		soundManager.Create(&soundManager.BGMRankStage, fileName, DSBCAPS_CTRLVOLUME);
	}
	{
		WCHAR fileName[MAX_PATH];
		swprintf_s<MAX_PATH>(fileName, L"sound/BGM/tutorial.wav");
		soundManager.Create(&soundManager.BGMTutorial, fileName, DSBCAPS_CTRLVOLUME);
	}
	{
		WCHAR fileName[MAX_PATH];
		swprintf_s<MAX_PATH>(fileName, L"sound/snd/levelUp.wav");
		soundManager.Create(&soundManager.sndLevelUp, fileName, DSBCAPS_CTRLVOLUME);
	}
	


}



void InitMyStuff()
{
	//textureManager.LoadTexture(L"image/background/titleBackground.png", TEX_TITLE_BACKGROUND);

	
	textureManager.LoadTexture(L"image/ui/mainButton.png", TEX_MAIN_BUTTON);
	textureManager.LoadTexture(L"image/ui/mainButton_bord.png", TEX_MAIN_BUTTON_BORD);
	textureManager.LoadTexture(L"image/object/bomb2.png", TEX_BOMB);


	textureManager.LoadTexture(L"image/ui/1nd.png", TEX_1ND);
	textureManager.LoadTexture(L"image/ui/2nd.png", TEX_2ND);
	textureManager.LoadTexture(L"image/ui/3nd.png", TEX_3ND);

	textureManager.LoadTexture(L"image/titleBackground/titleBackground_bossA.png", TEX_TITLE_BACKGROUND_BOSSA);
	textureManager.LoadTexture(L"image/titleBackground/titleBackground_bossB.png", TEX_TITLE_BACKGROUND_BOSSB);
	textureManager.LoadTexture(L"image/titleBackground/titleBackground_bossC.png", TEX_TITLE_BACKGROUND_BOSSC);
	textureManager.LoadTexture(L"image/titleBackground/titleBackground_bossD.png", TEX_TITLE_BACKGROUND_BOSSD);
	textureManager.LoadTexture(L"image/titleBackground/titleBackground_enemyA.png", TEX_TITLE_BACKGROUND_ENEMYA);
	textureManager.LoadTexture(L"image/titleBackground/titleBackground_enemyB.png", TEX_TITLE_BACKGROUND_ENEMYB);
	textureManager.LoadTexture(L"image/titleBackground/titleBackground_enemyC.png", TEX_TITLE_BACKGROUND_ENEMYC);
	textureManager.LoadTexture(L"image/titleBackground/titleBackground_enemyD.png", TEX_TITLE_BACKGROUND_ENEMYD);
	


	textureManager.LoadTexture(L"image/background/firstStageBackground.png", TEX_FIRST_STAGE_BACKGROUND);
	textureManager.LoadTexture(L"image/background/secondStageBackground.png", TEX_SECOND_STAGE_BACKGROUND);
	textureManager.LoadTexture(L"image/background/result.png", TEX_RESULT_TEXTURE);
	textureManager.LoadTexture(L"image/background/menualBackground.png", TEX_MANUAL_BACKGROUND);
	textureManager.LoadTexture(L"image/background/rankBackground.png", TEX_RANK_BACKGROUND);
	textureManager.LoadTexture(L"image/background/gameOver.png", TEX_GAME_OVER);
	textureManager.LoadTexture(L"image/background/fading.png", TEX_FADING);

	textureManager.LoadTexture(L"image/tutorial/shoot.png", TEX_TUTORIAL_SHOOT);
	textureManager.LoadTexture(L"image/tutorial/heart.png", TEX_TUTORIAL_HEART);
	textureManager.LoadTexture(L"image/tutorial/level.png", TEX_TUTORIAL_LEVEL);
	textureManager.LoadTexture(L"image/tutorial/exp.png", TEX_TUTORIAL_EXP);
	textureManager.LoadTexture(L"image/tutorial/hp.png", TEX_TUTORIAL_HP);



	textureManager.LoadTexture(L"image/charactor/player.png", TEX_PLAYER);

	// enemy
	textureManager.LoadTexture(L"image/charactor/enemy/enemyA.png", TEX_ENEMY_A);
	textureManager.LoadTexture(L"image/charactor/enemy/enemyB.png", TEX_ENEMY_B);
	textureManager.LoadTexture(L"image/charactor/enemy/enemyC.png", TEX_ENEMY_C);
	textureManager.LoadTexture(L"image/charactor/enemy/enemyD.png", TEX_ENEMY_D);
	textureManager.LoadTexture(L"image/charactor/enemy/bossA.png", TEX_BOSS_A);
	textureManager.LoadTexture(L"image/charactor/enemy/bossB.png", TEX_BOSS_B);
	textureManager.LoadTexture(L"image/charactor/enemy/bossC.png", TEX_BOSS_C);
	textureManager.LoadTexture(L"image/charactor/enemy/bossD.png", TEX_BOSS_D);

	// bullet
	textureManager.LoadTexture(L"image/object/playerBullet_01.png", TEX_PLAYER_BULLET_01);
	textureManager.LoadTexture(L"image/object/playerBullet_02.png", TEX_PLAYER_BULLET_02);
	textureManager.LoadTexture(L"image/object/enemy_bullet.png", TEX_ENEMY_BULLET);
	textureManager.LoadTexture(L"image/object/bossA_bullet.png", TEX_BOSSA_BULLET);;
	textureManager.LoadTexture(L"image/object/bossB_bullet.png", TEX_BOSSB_BULLET);;
	textureManager.LoadTexture(L"image/object/bossC_bullet.png", TEX_BOSSC_BULLET);;
	textureManager.LoadTexture(L"image/object/bossD_bullet.png", TEX_BOSSD_BULLET);
	
	// button
	textureManager.LoadTexture(L"image/ui/startButton.png", TEX_START_BUTTON);
	textureManager.LoadTexture(L"image/ui/startButton_bord.png", TEX_START_BUTTON_BORD);
	textureManager.LoadTexture(L"image/ui/manualButton.png", TEX_MANUAL_BUTTON);
	textureManager.LoadTexture(L"image/ui/manualButton_bord.png", TEX_MANUAL_BUTTON_BORD);
	textureManager.LoadTexture(L"image/ui/rankButton.png", TEX_RANK_BUTTON);
	textureManager.LoadTexture(L"image/ui/rankButton_bord.png", TEX_RANK_BUTTON_BORD);
	textureManager.LoadTexture(L"image/ui/breakButton.png", TEX_BREAK_BUTTON);
	textureManager.LoadTexture(L"image/ui/breakButton_bord.png", TEX_BREAK_BUTTON_BORD);
	textureManager.LoadTexture(L"image/ui/mainButton.png", TEX_MAIN_BUTTON);
	textureManager.LoadTexture(L"image/ui/mainButton_bord.png", TEX_MAIN_BUTTON_BORD);
	textureManager.LoadTexture(L"image/ui/mainButton_dark.png", TEX_MAIN_BUTTON_DARK);
	textureManager.LoadTexture(L"image/ui/mainButton_dark_bord.png", TEX_MAIN_BUTTON_DARK_BORD);

	// ingame UI
	textureManager.LoadTexture(L"image/ui/HP.png", TEX_PLAYER_HP); 
	textureManager.LoadTexture(L"image/ui/brokenHP.png", TEX_PLAYER_HP_BROKEN);
	textureManager.LoadTexture(L"image/ui/boss_a_HP_bar.png", TEX_BOSS_A_HP_BAR);
	textureManager.LoadTexture(L"image/ui/boss_a_HP.png", TEX_BOSS_A_HP);

	textureManager.LoadTexture(L"image/ui/skilCase.png", TEX_PLAYER_SKIL_CASE);
	textureManager.LoadTexture(L"image/ui/item_1.png", TEX_PLAYER_ITEM_01);
	textureManager.LoadTexture(L"image/ui/item_2.png", TEX_PLAYER_ITEM_02);
	textureManager.LoadTexture(L"image/ui/skil_1.png", TEX_PLAYER_SKIL_01);
	textureManager.LoadTexture(L"image/ui/skil_2.png", TEX_PLAYER_SKIL_02);

	textureManager.LoadTexture(L"image/ui/Level_1.png", TEX_LEVEL_1);
	textureManager.LoadTexture(L"image/ui/Level_2.png", TEX_LEVEL_2);
	textureManager.LoadTexture(L"image/ui/Level_3.png", TEX_LEVEL_3);
	textureManager.LoadTexture(L"image/ui/Level_4.png", TEX_LEVEL_4);
	textureManager.LoadTexture(L"image/ui/Level_5.png", TEX_LEVEL_5);
	textureManager.LoadTexture(L"image/ui/EXP_01.png", TEX_EXP_01);
	textureManager.LoadTexture(L"image/ui/EXP_02.png", TEX_EXP_02);

	textureManager.LoadTexture(L"image/background/waiting.png", WAITING_STAGE);

	textureManager.LoadTexture(L"image/ui/Yes.png",YES);
	textureManager.LoadTexture(L"image/ui/YesBord.png",YES_BORD);
	textureManager.LoadTexture(L"image/ui/no.png",NO);
	textureManager.LoadTexture(L"image/ui/NoBord.png",NO_BORD);

	textureManager.LoadTexture(L"image/object/shield.png", SHIELD);


	for (int i = 0; i < 7; ++i)
	{
		strcpy_s<128>(ranking[i].playerName, "player");
		ranking[i].playerScore = 0;
	}

	stageManager.CreateTitleStage();
	prevTime = GetTickCount();



}

void EngineUpdate()
{
	DWORD cur = GetTickCount();
	DWORD diff = cur - prevTime;
	deltaTime = diff / 1000.0f;
	if (deltaTime > 0.016f)
	{
		deltaTime = 0.016f;
	}
	prevTime = cur;



	stageManager.Update();
	//cheats.Update();
	inputManager.Update();
}

void EngineRender()
{
	if (NULL == g_pd3dDevice)
		return;

	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{

		stageManager.Render();

		g_pd3dDevice->EndScene();
	}

	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_GAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			EngineUpdate();
			EngineRender();
		}

	}

	return (int)msg.wParam;
}




ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAME));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	MyhWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, WINDOW_WIDTH, WINDOW_HEIGHT, nullptr, nullptr, hInstance, nullptr);

	if (!MyhWnd)
	{
		return FALSE;
	}
	InitD3D(MyhWnd);
	InitSound(MyhWnd);
	InitMyStuff();

	ShowWindow(MyhWnd, nCmdShow);
	UpdateWindow(MyhWnd);

	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		inputManager.keyBuffer[wParam] = 1;
		break;
	case WM_KEYUP:
		inputManager.keyBuffer[wParam] = 0;
		break;
	case WM_LBUTTONDOWN:
		inputManager.keyBuffer[VK_LBUTTON] = 1;
		//soundManager.sndClickButton->Reset();
		//soundManager.sndClickButton->Play(0, 0, 0.0001);
		break;
	case WM_LBUTTONUP:
		inputManager.keyBuffer[VK_LBUTTON] = 0;
		//sound->Play();
		break;
	case WM_RBUTTONDOWN:
		inputManager.keyBuffer[VK_RBUTTON] = 1;
		break;
	case WM_RBUTTONUP:
		inputManager.keyBuffer[VK_RBUTTON] = 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}