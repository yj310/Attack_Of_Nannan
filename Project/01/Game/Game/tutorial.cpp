#include "tutorial.h"
#include "global.h"


Tutorial::Tutorial()
{
	classType = TUTORIAL;
	currentPage = TEX_TUTORIAL_SHOOT;

}

void Tutorial::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(MyhWnd, &pt);

	for (int i = 0; i < 256; i++)
	{
		if (inputManager.prevKeyBuffer[i] == 1
			&& inputManager.keyBuffer[i] == 0)
		{
			if (currentPage < TEX_TUTORIAL_HP)
				currentPage++;
			else
				stageManager.CreateFirstStage();
		}
	}
	
	

}

void Tutorial::Render()
{
	TextureElement* element = textureManager.getTexture(currentPage);
	RECT rc;
	D3DXVECTOR3 pos;

	element->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	rc.left = 0;
	rc.top = 0;
	rc.right = WINDOW_WIDTH;
	rc.bottom = WINDOW_HEIGHT;

	pos = { 0, 0, 0 };

	element->sprite->Draw(element->texture, &rc, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	element->sprite->End();

}