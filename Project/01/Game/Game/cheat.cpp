#include "stdafx.h"
#include "cheat.h"
#include "player.h"
#include "global.h"
#include "first_game_stage.h"

void Cheat::CheatF1()
// 게임 플레이 시 무적 / 비무적 상태가 된다
{
	if (inputManager.prevKeyBuffer[VK_F1] == 1
		&& inputManager.keyBuffer[VK_F1] == 0)
	{
		if(gameSystem.player->dontHit == true)
			gameSystem.player->dontHit = false;
		else if (gameSystem.player->dontHit == false)
			gameSystem.player->dontHit = true;
	}
}

void Cheat::CheatF2()
// 레벨을 1단계 상승시킨다. (레벨업 보상 처리 동일)
{
	if (inputManager.prevKeyBuffer[VK_F2] == 1
		&& inputManager.keyBuffer[VK_F2] == 0)
	{
		
		switch (Level)
		{
		case 1:
			Exp = FIRST_LEVEL_2_EX;
			break;
		case 2:
			Exp = FIRST_LEVEL_3_EX;
			break;
		case 3:
			Exp = FIRST_LEVEL_4_EX;
			break;
		case 4:
			Exp = FIRST_LEVEL_5_EX;
			break;
		default:
			Exp = FIRST_LEVEL_5_EX;
			break;
		}
	}
}

void Cheat::CheatF3()
// 아이템을 1개 생성시킨다. 
{
	if (inputManager.prevKeyBuffer[VK_F3] == 1
		&& inputManager.keyBuffer[VK_F3] == 0)
	{

	}
}

void Cheat::CheatF4()
// 메뉴 화면으로 전환
{
	if (inputManager.prevKeyBuffer[VK_F4] == 1
		&& inputManager.keyBuffer[VK_F4] == 0)
	{
		stageManager.CreateTitleStage();
	}
}

void Cheat::CheatF5()
// 스테이지 1로 전환
{
	if (inputManager.prevKeyBuffer[VK_F5] == 1
		&& inputManager.keyBuffer[VK_F5] == 0)
	{
		stageManager.CreateFirstStage();
	}
}

void Cheat::CheatF6()
// 스테이지 2로 전환
{
	if (inputManager.prevKeyBuffer[VK_F6] == 1
		&& inputManager.keyBuffer[VK_F6] == 0)
	{
		stageManager.CreateSecondStage();
	}
}

void Cheat::CheatF7()
// 보스 죽이기
{
	if (inputManager.prevKeyBuffer[VK_F7] == 1
		&& inputManager.keyBuffer[VK_F7] == 0)
	{
		if (gameSystem.middleBoss != nullptr)
		{
			gameSystem.middleBoss->Hit(5000);
		}
		if (gameSystem.finalBoss != nullptr)
		{
			gameSystem.finalBoss->Hit(1000);
		}
	}
}


void Cheat::Update()
{
	CheatF1();
	CheatF2();
	CheatF3();
	CheatF4();
	CheatF5();
	CheatF6();
	CheatF7();
}
