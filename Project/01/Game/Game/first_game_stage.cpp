#include "stdafx.h"
#include "first_game_stage.h"
#include "global.h"


FirstGameStage::FirstGameStage()
{
	isScral = true;
	isPlaying = true;
	isDone = false;   // false
	classType = FIRST_GAME_STAGE;
	gameSystem.player = &player;

}



void FirstGameStage::Update()
{
	
	if (!isPlaying)
	{
		if (isDone == true) //게임이 끝났을때만 결과
		{
			result.Update();
			//stageManager.CreateSecondStage();
		}
		else
		{
			waiting.Update();
		}
		
		
	}
	else if (player.hp <= 0)
	{
		gameOver.Update();
	}
	else
	{
		background.Update(isScral);
		player.Update();
		gameSystem.Update();
		ui.Update();
	}
	

}

void FirstGameStage::Render()
{
	background.Render();
	gameSystem.Render();
	player.Render();
	ui.Render();

	

	if (player.hp <= 0)
	{
		player.hp = 0;
		player.brokenHP = player.maxHP;
		gameOver.Render();
	}
	if (!isPlaying)
	{
		if (isDone == true)//게임이 끝났을때만 결과
		{
			result.Render();
			//stageManager.CreateSecondStage();
		}
		else
		{
			waiting.Render();
		}
	}
}

void FirstGameStage::ClearAll()
{
	player.Reset();
}
