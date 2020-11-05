#include "stdafx.h"
#include "stage_manager.h"
#include "global.h"
#include "title_stage.h"
#include "first_game_stage.h"
#include "second_game_stage.h"
#include "rank_stage.h"
#include "manual_stage.h"
#include "tutorial.h"


void StageManager::CreateTitleStage()
{
	
	if (currentStage != nullptr)
	{
		prevStage = currentStage;
		if (prevStage->classType == TITLE_STAGE)
		{
			soundManager.BGMTitleStage->Stop();
		}
		if (prevStage->classType == FIRST_GAME_STAGE)
		{
			soundManager.BGMFirstStage->Stop();
		}
		if (prevStage->classType == SECOND_GAME_STAGE)
		{
			soundManager.BGMSecondStage->Stop();
		}
		if (prevStage->classType == RANK_STAGE || prevStage->classType == MENUAL_STAGE)
		{
			soundManager.BGMRankStage->Stop();
		}
		if (prevStage->classType == TUTORIAL)
		{
			soundManager.BGMTutorial->Stop();
		}

		if (prevStage->classType == FIRST_GAME_STAGE || prevStage->classType == SECOND_GAME_STAGE)
		{
			gameSystem.ClearAll();
		}
	}
	soundManager.BGMTitleStage->Reset();
	soundManager.BGMTitleStage->Play(0, DSBPLAY_LOOPING, 1);
	TitleStage* titleStage = new TitleStage();
	currentStage = titleStage;
}

void StageManager::CreateTutorial()
{
	if (currentStage != nullptr)
	{
		prevStage = currentStage;
		if (prevStage->classType == TITLE_STAGE)
		{
			soundManager.BGMTitleStage->Stop();
		}
		if (prevStage->classType == FIRST_GAME_STAGE)
		{
			soundManager.BGMFirstStage->Stop();
		}
		if (prevStage->classType == SECOND_GAME_STAGE)
		{
			soundManager.BGMSecondStage->Stop();
		}
		if (prevStage->classType == RANK_STAGE || prevStage->classType == MENUAL_STAGE)
		{
			soundManager.BGMRankStage->Stop();
		}
		if (prevStage->classType == TUTORIAL)
		{
			soundManager.BGMTutorial->Stop();
		}


		if (prevStage->classType == FIRST_GAME_STAGE || prevStage->classType == SECOND_GAME_STAGE)
		{
			gameSystem.ClearAll();
		}
	}
	stageState = FadeOut;
	FadingCount = 0;
	soundManager.BGMTutorial->Reset();
	soundManager.BGMTutorial->Play(0, DSBPLAY_LOOPING, 1);
	Tutorial* tutorial = new Tutorial();
	currentStage = tutorial;

}

void StageManager::CreateFirstStage()
{
	if (currentStage != nullptr)
	{
		prevStage = currentStage;
		if (prevStage->classType == TITLE_STAGE)
		{
			soundManager.BGMTitleStage->Stop();
		}
		if (prevStage->classType == FIRST_GAME_STAGE)
		{
			soundManager.BGMFirstStage->Stop();
		}
		if (prevStage->classType == SECOND_GAME_STAGE)
		{
			soundManager.BGMSecondStage->Stop();
		}
		if (prevStage->classType == RANK_STAGE || prevStage->classType == MENUAL_STAGE)
		{
			soundManager.BGMRankStage->Stop();
		}
		if (prevStage->classType == TUTORIAL)
		{
			soundManager.BGMTutorial->Stop();
		}


		if (prevStage->classType == FIRST_GAME_STAGE || prevStage->classType == SECOND_GAME_STAGE)
		{
			gameSystem.ClearAll();
		}
	}
	stageState = FadeOut;
	FadingCount = 0;
	soundManager.BGMFirstStage->Reset();
	soundManager.BGMFirstStage->Play(0, DSBPLAY_LOOPING, 1);
	FirstGameStage* firstGameStage = new FirstGameStage();
	currentStage = firstGameStage;

}

void StageManager::CreateSecondStage()
{
	if (currentStage != nullptr)
	{
		prevStage = currentStage;
		if (prevStage->classType == TITLE_STAGE)
		{
			soundManager.BGMTitleStage->Stop();
		}
		if (prevStage->classType == FIRST_GAME_STAGE)
		{
			soundManager.BGMFirstStage->Stop();
		}
		if (prevStage->classType == SECOND_GAME_STAGE)
		{
			soundManager.BGMSecondStage->Stop();
		}
		if (prevStage->classType == RANK_STAGE || prevStage->classType == MENUAL_STAGE)
		{
			soundManager.BGMRankStage->Stop();
		}
		if (prevStage->classType == TUTORIAL)
		{
			soundManager.BGMTutorial->Stop();
		}


		stageState = FadeOut;
		FadingCount = 0;
		soundManager.BGMSecondStage->Reset();
		soundManager.BGMSecondStage->Play(0, DSBPLAY_LOOPING, 1);
		SecondGameStage* secondStage = new SecondGameStage();
		currentStage = secondStage;
		if (prevStage->classType == FIRST_GAME_STAGE || prevStage->classType == SECOND_GAME_STAGE)
		{
			score = scoreFinal;
			gameSystem.ClearAll();
		}
	}

	
}


void StageManager::CreateManualStage()
{
	if (currentStage != nullptr)
	{
		prevStage = currentStage;
		if (prevStage->classType == TITLE_STAGE)
		{
			soundManager.BGMTitleStage->Stop();
		}
		if (prevStage->classType == FIRST_GAME_STAGE)
		{
			soundManager.BGMFirstStage->Stop();
		}
		if (prevStage->classType == SECOND_GAME_STAGE)
		{
			soundManager.BGMSecondStage->Stop();
		}
		if (prevStage->classType == RANK_STAGE || prevStage->classType == MENUAL_STAGE)
		{
			soundManager.BGMRankStage->Stop();
		}
		if (prevStage->classType == TUTORIAL)
		{
			soundManager.BGMTutorial->Stop();
		}


		if (prevStage->classType == FIRST_GAME_STAGE || prevStage->classType == SECOND_GAME_STAGE)
		{
			gameSystem.ClearAll();
		}
	}
	soundManager.BGMRankStage->Reset();
	soundManager.BGMRankStage->Play(0, DSBPLAY_LOOPING, 1);
	ManualStage* manualStage = new ManualStage();
	currentStage = manualStage;
}


void StageManager::CreateRankStage()
{
	if (currentStage != nullptr)
	{
		prevStage = currentStage;
		if (prevStage->classType == TITLE_STAGE)
		{
			soundManager.BGMTitleStage->Stop();
		}
		if (prevStage->classType == FIRST_GAME_STAGE)
		{
			soundManager.BGMFirstStage->Stop();
		}
		if (prevStage->classType == SECOND_GAME_STAGE)
		{
			soundManager.BGMSecondStage->Stop();
		}
		if (prevStage->classType == RANK_STAGE || prevStage->classType == MENUAL_STAGE)
		{
			soundManager.BGMRankStage->Stop();
		}
		if (prevStage->classType == TUTORIAL)
		{
			soundManager.BGMTutorial->Stop();
		}


		if (prevStage->classType == FIRST_GAME_STAGE || prevStage->classType == SECOND_GAME_STAGE)
		{
			gameSystem.ClearAll();

			stageState = FadeOut;
			FadingCount = 0;
		}
	}
	soundManager.BGMRankStage->Reset();
	soundManager.BGMRankStage->Play(0, DSBPLAY_LOOPING, 1);
	RankStage* rankStage = new RankStage();
	currentStage = rankStage;


}

void StageManager::CreateRankStageB()
{
	if (currentStage != nullptr)
	{
		prevStage = currentStage;
		if (prevStage->classType == TITLE_STAGE)
		{
			soundManager.BGMTitleStage->Stop();
		}
		if (prevStage->classType == FIRST_GAME_STAGE)
		{
			soundManager.BGMFirstStage->Stop();
		}
		if (prevStage->classType == SECOND_GAME_STAGE)
		{
			soundManager.BGMSecondStage->Stop();
		}
		if (prevStage->classType == RANK_STAGE || prevStage->classType == MENUAL_STAGE)
		{
			soundManager.BGMRankStage->Stop();
		}
		if (prevStage->classType == TUTORIAL)
		{
			soundManager.BGMTutorial->Stop();
		}


		if (prevStage->classType == FIRST_GAME_STAGE || prevStage->classType == SECOND_GAME_STAGE)
		{
			gameSystem.ClearAll();
		}
	}
	soundManager.BGMRankStage->Reset();
	soundManager.BGMRankStage->Play(0, DSBPLAY_LOOPING, 1);
	stageState = FadeOut;
	FadingCount = 0;
	RankStage* rankStage = new RankStage();
	currentStage = rankStage;

	
	

}


void StageManager::Update()
{
	if (currentStage != nullptr)
	{
		if (stageState == FadeOut)
		{
			fading.Update();
			FadingCount++;
			if (FadingCount >= 50)
			{
				stageState = FadeIn;
			}
		}
		else if (stageState == FadeIn)
		{
			fading.Update();
			FadingCount--;
			if (FadingCount <= 0)
			{
				stageState = Playing;
			}
		}
		else
		{
			currentStage->Update();
		}
		
	}
	
}

void StageManager::Render()
{
	if (currentStage != nullptr)
	{
		if (stageState == FadeOut)
		{
			prevStage->Render();
			fading.Render();
		}
		if (stageState == FadeIn)
		{
			currentStage->Render();
			fading.Render();
		}
		if (stageState == Playing)
		{
			currentStage->Render();
		}
	}
}
