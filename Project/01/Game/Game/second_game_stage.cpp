#include "stdafx.h"
#include "second_game_stage.h"
#include "global.h"

SecondGameStage::SecondGameStage()
{
	isScral = true;
	isPlaying = true;
	isDone = false;
	classType = SECOND_GAME_STAGE;
	gameSystem.player = &player;
	
}

void SecondGameStage::Update()
{
	if (!isPlaying)
	{
		if (isDone == true)
		{
			result.Update();
		}
		else
		{
			waiting.Update();
		}
	}
	else if (player.hp <=0)
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

void SecondGameStage::Render()
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
		}
		else
		{
			waiting.Render();
		}
	}
	
}

void SecondGameStage::ClearAll()
{
	player.Reset();
}