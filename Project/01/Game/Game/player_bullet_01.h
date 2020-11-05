#pragma once
#include "bullet.h"

class PlayerBullet : public Bullet
{
public:
	PlayerBullet(float x, float y, float vX, float vY);

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