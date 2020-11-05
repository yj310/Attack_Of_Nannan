#pragma once
#include <d3dx9math.h>

class Player
{
public:

	Player();

	void Update();
	void Render();
	
	bool IsDead();
	D3DXVECTOR2 getSize();
	D3DXVECTOR2 getPos();
	float getRadius();
	void Hit(float damage);
	void Reset();


	float posX;
	float posY;
	bool isDead;
	float radius;
	float speed;
	int hp;
	float hitTimer;
	float damage;
	float maxShoutCount1;
	float maxShoutCount2;
	float shoutCount1;
	float shoutCount2;
	bool dontHit;
	int maxHP;
	int brokenHP;
	int skilMaxTime1;
	int skilMaxTime2;
	int skilTime1;
	int skilTime2;
	int skilUseTime1;
	int skilUseTime2;
	float time;
	int clickToUse1;
	int clickToUse2;

	int bulletType;

};