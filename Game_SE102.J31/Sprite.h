#pragma once
#include "string"
#include "TextureManager.h"

using namespace std;

class CSprite
{
protected:
	RECT rect; //position of sprite in texture
	LPDIRECT3DTEXTURE9 texture;
	D3DXVECTOR3 center;
public:
	CSprite() {};
	CSprite(Tag tag, int left, int top, int right, int bottom);
	void Render(float x = 0, float y = 0);
	void ScaleRender(float x = 0, float y = 0, float scaleX = 1, float scaleY = 1);

	Tag tag; //sprite Tag
	bool _isFlipVertical, _isFlipHorizontal;
};
