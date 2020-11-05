#include <cstdlib>
#include <time.h>
#include "stdafx.h"
#include "game_system.h"
#include "global.h"
#include "math_util.h"
#include "player.h"
#include "stage.h"
#include "shield.h"
#include "enemy_explosion.h"
#include "item_1.h"
#include "item_2.h"


void GameSystem::ClearAll()
{
	if(enemies.size() > 0)
		enemies.clear();
	if (enemyBullets.size() > 0)
		enemyBullets.clear();
	if (playerBulletsA.size() > 0)
		playerBulletsA.clear();
	if (playerBulletsB.size() > 0)
		playerBulletsB.clear();
	if (bossBullets.size() > 0)
		bossBullets.clear();
	if (effects.size()>0)
		effects.clear();
	if (middleBoss != nullptr)
		middleBoss = nullptr;
	if (finalBoss != nullptr)
		finalBoss = nullptr;
	if (player != nullptr)
		player->Reset();
	
	pBulletADamage = 2;
	pBulletBDamage = 2;

	didBossA = false;
	didBossB = false;
}


void GameSystem::GenerateItem(float x, float y)
{
	//srand((unsigned int)time(NULL));
	int randValue = rand() % 100+1;
	float px = x;
	float py = y;
	/*if (randValue % 2)
	{
		Item1* newItem = new Item1(px, py);
		items.push_back(newItem);
	}
	else*/
	{
		if (Level >= 2)
		{
			Item2* newItem = new Item2(x, y);
			items.push_back(newItem);
		}
	
	}
	
}

void GameSystem::GenerateEnemyExplosion(float x, float y)
{
	EnemyExplosion* newEffect = new EnemyExplosion(x, y);
	effects.push_back(newEffect);
}


void GameSystem::GenerateBomb(float x, float y)
{
	
	for (int i = 0; i < enemies.size(); i++)
	{
		
		enemies[i]->Hit(500);
	}
	
}


void GameSystem::GenerateShield(float x, float y)
{
	Shield* shielde = new Shield(x, y);
	shield = shielde;

}

void GameSystem::GeneratePlayerBulletA(float x, float y) //직사형
{

	PlayerBullet02* bullet = new PlayerBullet02(x, y);
	playerBulletsB.push_back(bullet);

}



void GameSystem::GeneratePlayerBulletB(float x, float y) //방사형
{
	for (int i = 0; i < 6; i++)
	{
		float velx = -cos((i * 8 + 70) * 3.141562f / 180.f);
		float vely = sin((i * 8 + 70) * 3.141562f / 180.f);
		PlayerBullet* bullet = new PlayerBullet(x, y, velx, vely);
		playerBulletsA.push_back(bullet);


	}
}


void GameSystem::GenerateEnemyA()
{
	
	EnemyA* enemy = new EnemyA();
	enemy->classType = ENEMY_A;
	enemies.push_back(enemy);
	
}

void GameSystem::GenerateEnemyB()
{
	
	EnemyB* enemy = new EnemyB();
	enemy->classType = ENEMY_B;
	enemies.push_back(enemy);
	
}


void GameSystem::GenerateEnemyC()
{
	
	EnemyC* enemy = new EnemyC();
	enemy->classType = ENEMY_C;
	enemies.push_back(enemy);
}

void GameSystem::GenerateEnemyD()
{
	
	EnemyD* enemy = new EnemyD();
	enemy->classType = ENEMY_D;
	enemies.push_back(enemy);
}

void GameSystem::GenerateBossEnemyA()
{
	BossA* boss = new BossA();
	middleBoss = boss;
}

void GameSystem::GenerateBossEnemyB()
{
	BossB* boss = new BossB();
	finalBoss = boss;
}

void GameSystem::GenerateBossEnemyC()
{
	BossC* boss = new BossC();
	middleBoss = boss;
}

void GameSystem::GenerateBossEnemyD()
{
	BossD* boss = new BossD();
	finalBoss = boss;
}

void GameSystem::GenerateEnemyBullet(float x, float y)
{
	EnemyBullet* bullet = new EnemyBullet(x, y);
	enemyBullets.push_back(bullet);

}


void GameSystem::GenerateBossbullet(float x, float y, int bossType, int T)
{
	if (T == STRIGHT )
	{
		for (int i = 0; i < 6; i++)
		{
			float velx = -cos((i * 8 + 70) * 3.141562f / 180.f);
			float vely = sin((i * 8 + 70) * 3.141562f / 180.f);

			BossBullet* bullet = new BossBullet(x, y, velx, vely, bossType);
			bossBullets.push_back(bullet);
		}
	}
	else 
	{
		for (int i = 0; i < 36; i++)
		{

			float velx = -cos((i * 36 + 70) * 3.141562f / 180.f);
			float vely = sin((i * 36 + 70) * 3.141562f / 180.f);
			
			BossBullet* bullet = new BossBullet(x, y, velx, vely, bossType);
			bossBullets.push_back(bullet);

			
		}
	}
	

}




void GameSystem::Update()
{
	
	// esc 메인 화면
	if (inputManager.prevKeyBuffer[VK_ESCAPE] == 1
		&& inputManager.keyBuffer[VK_ESCAPE] == 0)
	{
		stageManager.currentStage->isPlaying = false;
	}

	// shield
	if (shield != nullptr)
	{
		shield->Update(player->posX, player->posY);
	}


	// 레벨업 & 능력치 상승
	if (Level == 1 && Exp >= FIRST_LEVEL_2_EX)
	{
		soundManager.sndLevelUp->Reset();
		soundManager.sndLevelUp->Play(0, 0, 1);
		player->maxHP += 1;
		pBulletADamage += pBulletADamage * 0.2;
		pBulletBDamage += pBulletBDamage * 0.2;
		player->maxShoutCount1 -= player->maxShoutCount1 * 0.2;
		player->brokenHP = 0;
		player->skilTime1 = 0;
		Level = 2;
	}
	if (Level == 2 && Exp >= FIRST_LEVEL_3_EX)
	{
		soundManager.sndLevelUp->Reset();
		soundManager.sndLevelUp->Play(0, 0, 1);
		player->maxHP += 1;
		pBulletADamage += pBulletADamage * 0.2;
		pBulletBDamage += pBulletBDamage * 0.2;
		player->maxShoutCount1 -= player->maxShoutCount1 * 0.2+1;
		player->brokenHP = 0;
		player->skilTime2 = 0;
		Level = 3;
	}
	if (Level == 3 && Exp >= FIRST_LEVEL_4_EX)
	{
		soundManager.sndLevelUp->Reset();
		soundManager.sndLevelUp->Play(0, 0, 1);
		player->maxHP += 1;
		pBulletADamage += pBulletADamage * 0.2;
		pBulletBDamage += pBulletBDamage * 0.2;
		player->maxShoutCount1 -= player->maxShoutCount1 * 0.2+3;
		player->maxShoutCount2 -= player->maxShoutCount2 * 0.2+3;
		player->brokenHP = 0;
		Level = 4;
	}
	if (Level == 4 && Exp >= FIRST_LEVEL_5_EX)
	{
		soundManager.sndLevelUp->Reset();
		soundManager.sndLevelUp->Play(0, 0, 1);
		player->maxHP += 1;
		pBulletADamage += pBulletADamage * 0.2;
		pBulletBDamage += pBulletBDamage * 0.2;
		player->maxShoutCount1 -= player->maxShoutCount1 * 0.2+2;
		player->maxShoutCount2 -= player->maxShoutCount2 * 0.2+2;
		player->brokenHP = 0;
		Level = 5;
	}


	// enemy 생성
	if (Level == 3 && didBossA == false)
	{
		if (stageManager.currentStage->classType == FIRST_GAME_STAGE)
		{
			GenerateBossEnemyA();
		}
		else if (stageManager.currentStage->classType == SECOND_GAME_STAGE)
		{
			GenerateBossEnemyC();
		}
		didBossA = true;
		stageManager.currentStage->isScral = false;
	}
	else if (Level == 5 && didBossB == false)
	{
		if (stageManager.currentStage->classType == FIRST_GAME_STAGE)
		{
			GenerateBossEnemyB();
		} 
		else if (stageManager.currentStage->classType == SECOND_GAME_STAGE)
		{
			GenerateBossEnemyD();
			
		}
		didBossB = true;
		stageManager.currentStage->isScral = false;
	}
	else if (middleBoss == nullptr && finalBoss == nullptr)
	{
		if (stageManager.currentStage->classType == FIRST_GAME_STAGE)
		{
			switch (Level)
			{
			case 1:
				if (rand() % 100 < 2)
					GenerateEnemyA();
				break;
			case 2:
				if (rand() % 100 < 3)
					GenerateEnemyA();
				break;
			case 3:
				if (rand() % 100 < 3)
					GenerateEnemyA();
				if (rand() % 100 < 1)
					GenerateEnemyB();
				break;
			case  4:
				if (rand() % 100 < 3)
					GenerateEnemyA();
				if (rand() % 100 < 1)
					GenerateEnemyB();
				break;
			default:
				break;
			}
		}
		else if (stageManager.currentStage->classType == SECOND_GAME_STAGE)
		{
			switch (Level)
			{
			case 1:
				if (rand() % 100 < 2)
					GenerateEnemyC();
				break;
			case 2:
				if (rand() % 100 < 3)
					GenerateEnemyC();
				break;
			case 3:
				if (rand() % 100 < 3)
					GenerateEnemyC();
				if (rand() % 100 < 1)
					GenerateEnemyD();
				break;
			case  4:
				if (rand() % 100 < 3)
					GenerateEnemyC();
				if (rand() % 100 < 1)
					GenerateEnemyD();
				break;
			default:
				break;
			}
		}
		
		
	}
	else if (stageManager.currentStage->classType == SECOND_GAME_STAGE && Level == 5)
	{
		if (rand() % 100 < 1)
			GenerateEnemyD();
	}

	// 총알 생성
	if (enemies.size() > 0)
	{
		for (auto iter = enemies.begin(); iter != enemies.end();)
		{
			if (rand() % 100 < 1)
				GenerateEnemyBullet((*iter)->getPos().x, (*iter)->getPos().y);
			
			iter++;
		}
	}

	


	// 업데이트
	for (auto iter = playerBulletsA.begin(); iter != playerBulletsA.end();)
	{
		if ((*iter)->getPos().y < 0 || (*iter)->IsDead())
		{
			iter = playerBulletsA.erase(iter);
		}
		else
		{	
			(*iter)->Update();
			iter++;
		}
	}
	
	for (auto iter = playerBulletsB.begin(); iter != playerBulletsB.end();)
	{
		if ((*iter)->getPos().y < 0 || (*iter)->IsDead())
		{
			iter = playerBulletsB.erase(iter);
		}
		else
		{
			(*iter)->Update();
			iter++;
		}
	}
	
	
	for (auto iter = enemyBullets.begin(); iter != enemyBullets.end();)
	{
		if ((*iter)->getPos().y > WINDOW_HEIGHT || (*iter)->IsDead())
		{
			iter = enemyBullets.erase(iter);
		}
		else
		{
			(*iter)->Update();
			iter++;
		}
	}

	for (auto iter = bossBullets.begin(); iter != bossBullets.end();)
	{
		if ((*iter)->getPos().y > WINDOW_HEIGHT || (*iter)->IsDead())
		{
			iter = bossBullets.erase(iter);
		}
		else
		{
			(*iter)->Update();
			iter++;
		}
	}


	for (auto iter = enemies.begin(); iter != enemies.end();)
	{
		if ((*iter)->getPos().y > WINDOW_HEIGHT || (*iter)->IsDead())
		{
			if ((*iter)->IsDead())
			{
				soundManager.sndDieEnemy->Reset();
				soundManager.sndDieEnemy->Play();
			}
			score += 30;
			iter = enemies.erase(iter);
		}
		else
		{
			(*iter)->Update();
			iter++;
		}
	}

	if (middleBoss != nullptr)
	{
		if (middleBoss->IsDead())
		{
			soundManager.sndDieBoss->Reset();
			soundManager.sndDieBoss->Play();

			delete middleBoss;
			middleBoss = nullptr;
			stageManager.currentStage->isScral = true;
			score += 1000;
			Exp += 50;
		}
		else
		{
			middleBoss->Update();
		}
	}
	

	if (finalBoss != nullptr)
	{
		if (finalBoss->IsDead())
		{
			soundManager.sndDieBoss->Reset();
			soundManager.sndDieBoss->Play();
			delete finalBoss;
			finalBoss = nullptr;
			stageManager.currentStage->isScral = true;
			score += 3000;
			if (stageManager.currentStage->classType == FIRST_GAME_STAGE || stageManager.currentStage->classType == SECOND_GAME_STAGE)
			{
				stageManager.currentStage->isPlaying = FALSE;
				stageManager.currentStage->isDone = true;
				
				scoreFinal = (score + ((gameSystem.player->hp) * 200) + (heartEat * 20));
			}
		}
		else
		{
			finalBoss->Update();
		}
	}


	for (auto iter = items.begin(); iter != items.end();)
	{
		if ((*iter)->GetPos().y > WINDOW_HEIGHT || (*iter)->IsDead())
		{
			iter = items.erase(iter);
		}
		else
		{
			(*iter)->Update();
			iter++;
		}
	}
	// 충돌처리


	for (auto iter = items.begin(); iter != items.end();)
	{

		float ax = player->getPos().x;
		float ay = player->getPos().y;
		float ar = player->getRadius();

		float bx = (*iter)->GetPos().x;
		float by = (*iter)->GetPos().y;
		float bw = (*iter)->GetWidth();
		float bh = (*iter)->GetHeight();
		float br = (*iter)->GetRadious();

		if ((*iter)->GetCalssType() == ITEM1)
		{
			if (isCircleVsBoxCollided(ax, ay, ar, bx, by, bw, bh)==true)
			{
				
				if (gameSystem.player->hp < player->maxHP) {
					gameSystem.player->hp = gameSystem.player->hp+1;
				}
				(*iter)->isDead = true;
				
			}
		}
		else
		{
			if (isCircleCollided(ax, ay, ar, bx, by, br))
			{
				gameSystem.player->skilTime1 = 0;
				if(Level>=3)
					gameSystem.player->skilTime2 = 0;
				(*iter)->isDead = true;
			}

		}
		
		iter++;
	}

	// enemy & playerBulletA
	for (auto iter = enemies.begin(); iter != enemies.end();)
	{
		for (auto iterB = playerBulletsA.begin(); iterB != playerBulletsA.end();)
		{
			float ax = (*iter)->getPos().x;
			float ay = (*iter)->getPos().y;
			float ar = (*iter)->getRadius();
			float bx = (*iterB)->getPos().x;
			float by = (*iterB)->getPos().y;
			float br = (*iterB)->getRadius();
			if (isCircleCollided(ax, ay, ar, bx, by, br))
			{
				soundManager.sndHitEnemy->Reset();
				soundManager.sndHitEnemy->Play(0, 0, 1);
				iterB = playerBulletsA.erase(iterB);
				(*iter)->Hit(pBulletADamage);
				score += 10;
				break;
			}
			else
			{
				iterB++;
			}
		}
		iter++;
	}

	// enemy & playerBulletB
	for (auto iter = enemies.begin(); iter != enemies.end();)
	{
		for (auto iterB = playerBulletsB.begin(); iterB != playerBulletsB.end();)
		{
			float ax = (*iter)->getPos().x;
			float ay = (*iter)->getPos().y;
			float ar = (*iter)->getRadius();
			float bx = (*iterB)->getPos().x;
			float by = (*iterB)->getPos().y;
			float bw = (*iterB)->getSize().x;
			float bh = (*iterB)->getSize().y;
			if (isCircleVsBoxCollided(ax, ay, ar, bx, by, bw, bh))
			{
				soundManager.sndHitEnemy->Reset();
				soundManager.sndHitEnemy->Play(0, 0, 1);
				iterB = playerBulletsB.erase(iterB);
				(*iter)->Hit(pBulletBDamage);
				score += 10;
				break;
			}
			else
			{
				iterB++;
			}
		}
		iter++;
	}

	// middleBoss
	if (middleBoss != nullptr)
	{
		float ax = middleBoss->getPos().x;
		float ay = middleBoss->getPos().y;
		float ar = middleBoss->getRadius();

		// & playerBulletA
		for (auto iter = playerBulletsA.begin(); iter != playerBulletsA.end();)
		{
			float bx = (*iter)->getPos().x;
			float by = (*iter)->getPos().y;
			float br = (*iter)->getRadius();
			if (isCircleCollided(ax, ay, ar, bx, by, br))
			{
				iter = playerBulletsA.erase(iter);
				middleBoss->Hit(pBulletADamage);
				score += 30;
				break;
			}
			else
			{
				iter++;
			}
		}

		// & playerBulleyB
		for (auto iter = playerBulletsB.begin(); iter != playerBulletsB.end();)
		{
			float bx = (*iter)->getPos().x;
			float by = (*iter)->getPos().y;
			float bw = (*iter)->getSize().x;
			float bh = (*iter)->getSize().y;
			if (isCircleVsBoxCollided(ax, ay, ar, bx, by, bw, bh))
			{
				iter = playerBulletsB.erase(iter);
				middleBoss->Hit(pBulletBDamage);
				score += 30;
				break;
			}
			else
			{
				iter++;
			}
		}
		
		// & player
		float bx = player->getPos().x;
		float by = player->getPos().y;
		float br = player->getRadius();
		if (isCircleCollided(ax, ay, ar, bx, by, br))
		{
			if (player->skilTime1 > 0)
				player->Hit(1);
			else
				player->Hit(2);

			//middleBoss->Hit(5);
		}
	}
	
	// finalBoss
	if (finalBoss != nullptr)
	{
		float ax = finalBoss->getPos().x;
		float ay = finalBoss->getPos().y;
		float ar = finalBoss->getRadius();

		// & playerBulletA
		for (auto iter = playerBulletsA.begin(); iter != playerBulletsA.end();)
		{
			float bx = (*iter)->getPos().x;
			float by = (*iter)->getPos().y;
			float br = (*iter)->getRadius();
			if (isCircleCollided(ax, ay, ar, bx, by, br))
			{
				iter = playerBulletsA.erase(iter);
				finalBoss->Hit(pBulletADamage);
				score += 30;
				break;
			}
			else
			{
				iter++;
			}
		}

		// & playerBulletB
		for (auto iter = playerBulletsB.begin(); iter != playerBulletsB.end();)
		{
			float bx = (*iter)->getPos().x;
			float by = (*iter)->getPos().y;
			float bw = (*iter)->getSize().x;
			float bh = (*iter)->getSize().y;
			if (isCircleVsBoxCollided(ax, ay, ar, bx, by, bw, bh))
			{
				iter = playerBulletsB.erase(iter);
				finalBoss->Hit(pBulletBDamage);
				score += 30;
				break;
			}
			else
			{
				iter++;
			}
		}
		
		//& player
		float bx = player->getPos().x;
		float by = player->getPos().y;
		float br = player->getRadius();
		if (isCircleCollided(ax, ay, ar, bx, by, br))
		{
			if (player->skilTime1 > 0)
				player->Hit(1);
			else
				player->Hit(2);
			//finalBoss->Hit(5);
		}
		
	}
	
	// shileld
	if (shield != nullptr && player->skilUseTime1 > 0)
	{
		// & bossBullet
		float ax = shield->GetPos().x;
		float ay = shield->GetPos().y;
		float ar = shield->GetRadiou();
		for (auto iter = bossBullets.begin(); iter != bossBullets.end();)
		{
			float bx = (*iter)->getPos().x;
			float by = (*iter)->getPos().y;
			float br = (*iter)->getRadius();
			if (isCircleCollided(ax, ay, ar, bx, by, br))
			{
				(*iter)->isDead = true;
				break;
			}
			iter++;
		}

		// & enemy
		for (auto iter = enemies.begin(); iter != enemies.end();)
		{
			float bx = (*iter)->getPos().x;
			float by = (*iter)->getPos().y;
			float br = (*iter)->getRadius();
			if (isCircleCollided(ax, ay, ar, bx, by, br))
			{
				(*iter)->Hit(1);
				break;
			}
			iter++;
		}
	}
	else
	// player
	{
		float ax = player->getPos().x;
		float ay = player->getPos().y;
		float ar = player->getRadius();
		// & enemy
		for (auto iter = enemies.begin(); iter != enemies.end();)
		{
			float bx = (*iter)->getPos().x;
			float by = (*iter)->getPos().y - 20;
			float br = (*iter)->getRadius();
			if (isCircleCollided(ax, ay, ar, bx, by, br))
			{
				player->Hit(1);
				(*iter)->Hit(50);
				break;
			}
			iter++;
		}

		// & bossBullet
		for (auto iter = bossBullets.begin(); iter != bossBullets.end();)
		{
			float bx = (*iter)->getPos().x;
			float by = (*iter)->getPos().y;
			float br = (*iter)->getRadius();
			if (isCircleCollided(ax, ay, ar, bx, by, br))
			{
				(*iter)->isDead = true;
				player->Hit(1);
				break;
			}

			iter++;
		}
	}



	// player & enemyBullet
	{
		float ax = player->getPos().x;
		float ay = player->getPos().y;
		float ar = player->getRadius();
		for (auto iter = enemyBullets.begin(); iter != enemyBullets.end();)
		{
			float bx = (*iter)->getPos().x;
			float by = (*iter)->getPos().y;
			float br = (*iter)->getRadius();
			if (isCircleCollided(ax, ay, ar, bx, by, br))
			{
				(*iter)->isDead = true;
				heartEat++;
				break;
			}
			iter++;
		}

	}

	



	//Item 만들기
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->IsDead())
		{
			if (rand() % 100 < 5)
			{
				float px = enemies[i]->getPos().x;
				float py = enemies[i]->getPos().y;
				GenerateItem(px, py);
			}
		}
	}



	//effect
	for (auto iter = effects.begin(); iter != effects.end(); )
	{
		(*iter)->Update();

		if ((*iter)->IsDead())
		{
			iter = effects.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	
}

void GameSystem::Render()
{
	for (int i = 0; i < playerBulletsA.size(); ++i)
	{
		playerBulletsA[i]->Render();
	}
	for (int i = 0; i < playerBulletsB.size(); ++i)
	{
		playerBulletsB[i]->Render();
	}
	for (int i = 0; i < enemies.size(); ++i)
	{
		enemies[i]->Render();
	}
	for (int i = 0; i < enemyBullets.size(); ++i)
	{
		enemyBullets[i]->Render();
	}
	for (int i = 0; i < bossBullets.size(); ++i)
	{
		bossBullets[i]->Render();
	}
	if(middleBoss !=nullptr)
		middleBoss->Render();
	if (finalBoss != nullptr)
		finalBoss->Render();
	if (shield != nullptr && player->skilUseTime1 > 0)
	{
		shield->Render();
	}
	
	for (int i = 0; i < effects.size(); ++i)
	{
		effects[i]->Render();
	}
	
	for (int i = 0; i < items.size(); i++)
	{
		items[i]->Render();
	}
}