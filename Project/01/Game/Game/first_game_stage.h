#pragma once
#include "stage.h"
#include "first_stage_background.h"
#include "player.h"
#include "game_stage_ui.h"
#include "result_texture.h"
#include "game_over.h"
#include "waiting.h"

class FirstGameStage : public Stage
{
public:

	FirstGameStage();

	void Update() override;
	void Render() override;
	void ClearAll();

	Player player;
	FirstStageBackgound background;
	GameStageUI ui;
	ResultTexture result;
	GameOver gameOver;
	Waiting waiting;
};