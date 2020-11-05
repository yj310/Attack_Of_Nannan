#pragma once
#include "enemy.h"

class BossD : public Enemy
{
public:
	BossD();

	void Update() override;
	void Render() override;
	bool IsDead() override;
	float getRadius() override;
	D3DXVECTOR2 getSize() override;
	D3DXVECTOR2 getPos() override;
	void Hit(float damage) override;
	float getMaxHP() override;
	float getHP() override;
	int getClassType() override;

	bool isDead;
	float posX;
	float posY;
	float radius;
	float hp;
	float maxHP;
	float velY;
	float velX;

	float hitTimer;

	enum State
	{
		init,
		updown,
		move,
		updown2,
		move2,

		back
	};

	State state;

};