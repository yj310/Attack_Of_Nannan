#pragma once
#include <d3dx9math.h>

class Bullet
{
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual bool IsDead() = 0;
	virtual float getRadius() = 0;
	virtual D3DXVECTOR2 getSize() = 0;
	virtual D3DXVECTOR2 getPos() = 0;

	float posX;
	float posY;


};