#pragma once
#include "enemy.h"

class EnemyD : public Enemy
{
public:


	EnemyD();
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
	float velX;
	float velY;
	float radius;
	float hp;
	int classType;

	float hitTimer;

};