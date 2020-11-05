#pragma once
#include "SpriteEffect.h"
#include "animation_frame.h"
#include <windows.h>
#include <vector>

using namespace std;

class EnemyExplosion :public SpriteEffect
{
public:
	EnemyExplosion(float x, float y);
	void Update()override;
	void Render()override;
	bool IsDead()override;

	float posX;
	float posY;
	bool isDead;

	RECT GetSourceRect();

	vector<AnimationFrame> frames;
	int frameIndex;
	float animTime;
};