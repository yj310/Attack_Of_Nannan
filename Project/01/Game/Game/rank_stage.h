#pragma once
#include "stage.h"
#include <vector>

using namespace std;

class RankStage : public Stage
{
public:
	RankStage();

	void Update() override;
	void Render() override;

	void Load();
	void Save();

	ID3DXFont* font = NULL;

	bool isFirstStage;

	int buttonState;
};