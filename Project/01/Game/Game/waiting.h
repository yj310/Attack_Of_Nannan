#pragma once
#include "stage.h"
#include <d3dx9.h>

class Waiting :public Stage
{
public:
	Waiting();
	void Update() override;
	void Render() override;

	ID3DXFont* font = NULL;
	ID3DXFont* font_Small = NULL;

	int yesState;
	int noState;

};