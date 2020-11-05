#pragma once
#include <d3dx9.h>
#include <vector>
using namespace std;


class ResultTexture
{
public:
	ResultTexture();
	void Update();
	void Render();
	ID3DXFont* font = NULL;
	ID3DXFont* font_Small = NULL;

	vector<char> cname;

	int enterTimer;
};