#include "stdafx.h"
#include "cheat.h"
#include "player.h"
#include "global.h"
#include "first_game_stage.h"

void Cheat::CheatF1()
// ���� �÷��� �� ���� / ���� ���°� �ȴ�
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
// ������ 1�ܰ� ��½�Ų��. (������ ���� ó�� ����)
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
// �������� 1�� ������Ų��. 
{
	if (inputManager.prevKeyBuffer[VK_F3] == 1
		&& inputManager.keyBuffer[VK_F3] == 0)
	{

	}
}

void Cheat::CheatF4()
// �޴� ȭ������ ��ȯ
{
	if (inputManager.prevKeyBuffer[VK_F4] == 1
		&& inputManager.keyBuffer[VK_F4] == 0)
	{
		stageManager.CreateTitleStage();
	}
}

void Cheat::CheatF5()
// �������� 1�� ��ȯ
{
	if (inputManager.prevKeyBuffer[VK_F5] == 1
		&& inputManager.keyBuffer[VK_F5] == 0)
	{
		stageManager.CreateFirstStage();
	}
}

void Cheat::CheatF6()
// �������� 2�� ��ȯ
{
	if (inputManager.prevKeyBuffer[VK_F6] == 1
		&& inputManager.keyBuffer[VK_F6] == 0)
	{
		stageManager.CreateSecondStage();
	}
}

void Cheat::CheatF7()
// ���� ���̱�
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
