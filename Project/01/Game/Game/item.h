#pragma once
#include <d3dx9.h>

class Item
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual D3DXVECTOR2  GetPos() = 0;
	virtual float GetRadious() = 0;
	virtual int GetCalssType() = 0;
	virtual void SetIsHit(bool isHit) = 0;
	virtual bool GetIsHit() = 0;
	virtual float GetWidth() = 0;
	virtual float GetHeight() = 0;
	virtual bool IsDead() = 0;

	bool isHit;
	bool isDead;
	int classType;

};