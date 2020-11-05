#pragma once

#include "bullet.h"

class EnemyBullet : public Bullet
{
public:
	EnemyBullet(float x, float y);

	void Update() override;
	void Render() override;
	bool IsDead() override;
	float getRadius() override;
	D3DXVECTOR2 getSize() override;
	D3DXVECTOR2 getPos() override;

	bool isDead;
	float posX;
	float posY;
	float velX;
	float velY;
	float radius;
}; 