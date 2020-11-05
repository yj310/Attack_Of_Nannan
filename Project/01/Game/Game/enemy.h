#pragma once
#include <d3dx9math.h>

class Enemy
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual bool IsDead() = 0;
	virtual float getRadius() = 0;
	virtual D3DXVECTOR2 getSize() = 0;
	virtual D3DXVECTOR2 getPos() = 0;
	virtual void Hit(float damage) = 0;
	virtual float getMaxHP() = 0;
	virtual float getHP() = 0;
	virtual int getClassType() = 0;
	
	
	bool isDead;
	float posX;
	float posY;
	float radius;
	float hp;
	float maxHP;
	int classType = 0;

	float enemyTime;
	bool isinit;
	//bool isBack;
	float moveX;
	float moveY;

	float disX;
	float disY;

	float speed;
};