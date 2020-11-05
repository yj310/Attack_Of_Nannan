#pragma once
#include "bullet.h"
#include "player_bullet_01.h"
#include "enemy.h"
#include "enemyA.h"
#include "enemyB.h"
#include "enemyC.h"
#include "enemyD.h"
#include <vector>
#include "bossA.h"
#include "bossB.h"
#include "bossC.h"
#include "bossD.h"
#include "player_bullet_02.h"
#include "enemy_bullet.h"
#include "boss_bullet.h"
#include "shield.h"
#include "SpriteEffect.h"
#include "item.h"

using namespace std;

class Player;

class GameSystem
{
public:

	vector<PlayerBullet*> playerBulletsA;
	vector<PlayerBullet02*> playerBulletsB;
	vector<Enemy*> enemies;
	vector<EnemyBullet*> enemyBullets;
	vector<BossBullet*> bossBullets;
	vector<SpriteEffect*>effects;
	Enemy* middleBoss;
	Enemy* finalBoss;
	Shield* shield;

	Player* player;
	//vector<enemyBullet*> enemyBullets;

	vector<Item*>items;

	void GenerateShield(float x, float y);
	void GenerateItem(float x, float y);
	void GenerateBomb(float x, float y);
	void GenerateEnemyExplosion(float x, float y);
	
	void GeneratePlayerBulletA(float x, float y);
	void GeneratePlayerBulletB(float x, float y);

	void GenerateEnemyA();
	void GenerateEnemyB();
	void GenerateEnemyC();
	void GenerateEnemyD();
	void GenerateBossEnemyA();
	void GenerateBossEnemyB();
	void GenerateBossEnemyC();
	void GenerateBossEnemyD();
	void GenerateEnemyBullet(float x, float y);
	void GenerateBossbullet(float x, float y, int bossType, int T);
	void ClearAll();

	void Update();
	void Render();

	bool didBossA = false;
	bool didBossB = false;

	float pBulletADamage = 2;
	float pBulletBDamage = 2;

};