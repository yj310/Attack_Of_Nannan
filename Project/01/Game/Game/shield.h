#pragma once
#include <d3dx9.h>

class Shield
{
public:
	Shield(float x, float y);
	void Update(float x, float y);
	void Render();
	D3DXVECTOR2 GetPos();
	float GetRadiou();


	float posX;
	float posY;
	float radious;


};