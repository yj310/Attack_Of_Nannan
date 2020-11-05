#pragma once
#include "stage.h"
#include <d3dx9.h>
class GameOver : public Stage
{
public:
	GameOver();
	void Update() override;
	void Render() override;
	int mainButtonState;
	ID3DXFont* font = NULL;

};