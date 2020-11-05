#pragma once
#include "item.h"
#include <d3dx9.h>

class Item2 :public Item
{
public:
	Item2(float x, float y);
	void Update()override;
	void Render()override;

	D3DXVECTOR2 GetPos()override;
	float GetRadious() override;
	int GetCalssType() override;
	void SetIsHit(bool isHit) override;
	bool GetIsHit() override;
	float GetWidth()override;
	float GetHeight()override;
	bool IsDead() override;

	float posX;
	float posY;
};
