#include "Sprite.h"

//Constructor - Khoi tao 1 Sprite tu duong dan
CSprite::CSprite(Tag tag, int left, int top, int right, int bottom)
{
	this->tag = tag;
	texture = TextureManager::GetInstance()->GetTexture(tag);
	rect.left = left;
	rect.top = top;
	rect.right = right;
	rect.bottom = bottom;
	center = D3DXVECTOR3((right - left) >> 1, (bottom - top) >> 1, 0);
	
}



//Ve sprite tai toa do (x,y)
//Voi (x,y) la trung tam cua Sprite
void CSprite::Render(float x, float y)
{
	//Tao rect de ve Sprite

	D3DXVECTOR3 p(x, y, 0);
	//spriteHandler->Draw(texture, &r, NULL, &p, D3DCOLOR_XRGB(255,255,255));
	// Nếu có lật hình (theo Ox hay Oy) thì thiết đặt biến đổi hình băng ma trận
	auto pPosition = D3DXVECTOR3(x, y, 0);
	auto pRotationCenter = D3DXVECTOR2(center.x, center.y);
	auto pScalingCenter = D3DXVECTOR2(x, y);
	auto pScaling = D3DXVECTOR2(_isFlipHorizontal ? -1 : 1, 1);
	

	D3DXMATRIX oldMatrix, curMatrix;
	D3DXMatrixTransformation2D(&curMatrix, &pScalingCenter, 0, &pScaling, &pRotationCenter, 0, NULL);
	spriteHandler->GetTransform(&oldMatrix);
	spriteHandler->SetTransform(&curMatrix);
	spriteHandler->Draw(texture, &rect, &center, &pPosition, D3DCOLOR_XRGB(255, 255, 255));
	spriteHandler->SetTransform(&oldMatrix);
}

void CSprite::ScaleRender(float x, float y, float scaleX, float scaleY)
{
	D3DXVECTOR3 p(x, y, 0);
	//spriteHandler->Draw(texture, &r, NULL, &p, D3DCOLOR_XRGB(255,255,255));

	// Nếu có lật hình (theo Ox hay Oy) thì thiết đặt biến đổi hình băng ma trận
	auto pPosition = D3DXVECTOR3(x, y, 0);
	auto pRotationCenter = D3DXVECTOR2(center.x, center.y);
	auto pScalingCenter = D3DXVECTOR2(x, y);
	auto pScaling = D3DXVECTOR2(scaleX, scaleY);

	D3DXMATRIX oldMatrix, curMatrix;
	D3DXMatrixTransformation2D(&curMatrix, &pScalingCenter, 0, &pScaling, &pRotationCenter, 0, NULL);
	spriteHandler->GetTransform(&oldMatrix);
	spriteHandler->SetTransform(&curMatrix);
	spriteHandler->Draw(texture, &rect, &center, &pPosition, D3DCOLOR_XRGB(255, 255, 255));
	spriteHandler->SetTransform(&oldMatrix);
}
void CSprite::AlphaRender(float x, float y, D3DCOLOR color, LPDIRECT3DTEXTURE9 newTexture)
{
	//Tao rect de ve Sprite

	D3DXVECTOR3 p(x, y, 0);
	//spriteHandler->Draw(texture, &r, NULL, &p, D3DCOLOR_XRGB(255,255,255));
	// Nếu có lật hình (theo Ox hay Oy) thì thiết đặt biến đổi hình băng ma trận
	auto pPosition = D3DXVECTOR3(x, y, 0);
	auto pRotationCenter = D3DXVECTOR2(center.x, center.y);
	auto pScalingCenter = D3DXVECTOR2(x, y);
	auto pScaling = D3DXVECTOR2(_isFlipHorizontal ? -1 : 1, 1);

	D3DXMATRIX oldMatrix, curMatrix;
	D3DXMatrixTransformation2D(&curMatrix, &pScalingCenter, 0, &pScaling, &pRotationCenter, 0, NULL);
	spriteHandler->GetTransform(&oldMatrix);
	spriteHandler->SetTransform(&curMatrix);
	if (newTexture != NULL)
		spriteHandler->Draw(newTexture, &rect, &center, &pPosition, D3DCOLOR_XRGB(255,255,255));
	else
		spriteHandler->Draw(texture, &rect, &center, &pPosition, color);
	spriteHandler->SetTransform(&oldMatrix);
}