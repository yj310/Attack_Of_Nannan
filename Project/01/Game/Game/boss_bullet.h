#pragma once

#include "bullet.h"

class BossBullet : public Bullet
{
public:
	BossBullet(float x, float y, float vx, float vy, int bossType);

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
	int bossBulletType;
};