#pragma once
#include "stage.h"
#include "player.h"
#include "game_stage_ui.h"
#include "result_texture.h"
#include "game_over.h"
#include "waiting.h"
#include "second_stage_background.h"

class SecondGameStage :public Stage
{
public:

	SecondGameStage();
	void Update() override;
	void Render() override;
	void ClearAll();

	Player player;
	SecondStageBackground background;
	GameStageUI ui;
	ResultTexture result;
	GameOver gameOver;
	Waiting waiting;

};