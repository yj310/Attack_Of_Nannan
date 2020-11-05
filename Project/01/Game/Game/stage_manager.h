#pragma once

#include <vector>
#include "fading.h"
using namespace std;
class Stage;

class StageManager
{
public:
	
	enum State
	{
		FadeIn, 
		FadeOut, 
		Playing
	};

	Stage* nextStage;
	Stage* currentStage;
	Stage* prevStage;

	void CreateTitleStage();
	void CreateTutorial();
	void CreateFirstStage();
	void CreateSecondStage();
	void CreateManualStage();
	void CreateRankStage();
	void CreateRankStageB();

	void Update();
	void Render();

	Fading fading;
	State stageState;
	int FadingCount;

};