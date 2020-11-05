#pragma once
#include <d3dx9.h>
#include <vector>

using namespace std;

class TextureElement
{
public:
	int id;
	LPDIRECT3DTEXTURE9 texture;
	ID3DXSprite* sprite;

};

class TextureManager
{
public:
	vector<TextureElement*> elements;

	void LoadTexture(const TCHAR* name, int id);
	TextureElement* getTexture(int id);
};