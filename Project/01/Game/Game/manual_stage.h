#pragma once
#include "stage.h"

class ManualStage : public Stage
{
public:
	ManualStage();
	void Update() override;
	void Render() override;

	int buttonState;
	int mainButtonState = TEX_MAIN_BUTTON;
};