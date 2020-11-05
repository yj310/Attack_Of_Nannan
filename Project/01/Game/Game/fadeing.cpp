#include "fading.h"
#include "global.h"

Fading::Fading()
{

}

void Fading::Update()
{


}


void Fading::Render()
{

	TextureElement* element = textureManager.getTexture(TEX_FADING);
	RECT rc;
	D3DXVECTOR3 pos;

	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = WINDOW_WIDTH;
	rc.bottom = WINDOW_HEIGHT;

	pos = { 0, 0, 0 };

	element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_ARGB((255 / 50) * stageManager.FadingCount, 255, 255, 255));

	element->sprite->End();

}
