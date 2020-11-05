#include "enemy_explosion.h"
#include "global.h"

#define WIDTH 120

EnemyExplosion::EnemyExplosion(float x, float y)
{
    posX = x;
    posY = y;
    isDead = false;

    for (int i = 0; i < 3; ++i)
    {
        int x = i * WIDTH;
        int y = 1;
        int width = WIDTH;
        int height = WIDTH;

        AnimationFrame newFrame;
        newFrame.x = x;
        newFrame.y = y;
        newFrame.width = width;
        newFrame.height = height;
        newFrame.time = 0.1f;

        frames.push_back(newFrame);
    }

    frameIndex = 0;
    animTime = 0;
}

void EnemyExplosion::Update()
{
    animTime += deltaTime;

    if (animTime > frames[frameIndex].time)
    {
        frameIndex++;
        animTime = 0;

        if (frameIndex >= frames.size())
        {
            frameIndex = frames.size() - 1;
            isDead = true;
        }
    }
}

void EnemyExplosion::Render()
{
    TextureElement* element = textureManager.getTexture(TEX_BOMB);

    element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

    RECT srcRect = GetSourceRect();
   

    D3DXVECTOR3 pos(posX - 32, posY - 32, 0);
    D3DCOLOR spriteColor = D3DCOLOR_XRGB(255, 255, 255);

    element->sprite->Draw(element->texture, &srcRect, nullptr, &pos,
        spriteColor);

    element->sprite->End();
}

bool EnemyExplosion::IsDead()
{
    return isDead;
}

RECT EnemyExplosion::GetSourceRect()
{
    RECT srcRect;

    srcRect.left = frames[frameIndex].x;
    srcRect.top = frames[frameIndex].y;
    srcRect.right = frames[frameIndex].x + frames[frameIndex].width;
    srcRect.bottom = frames[frameIndex].y + frames[frameIndex].height;

    return srcRect;
}