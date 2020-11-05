#pragma once
#include <d3dx9.h>

class GameStageUI
{
public:
	GameStageUI();
	void Update();
	void Render();


	ID3DXFont* font = NULL;

};