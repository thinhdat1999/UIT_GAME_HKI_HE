#pragma once
#include "Sprite.h"
#include "SpriteManager.h"
#include <vector>
#include <map>

class Animation
{
private:
	int totalFrames;						// Tổng số Frame
	int timePerFrame;						// Thời gian tồn tại mỗi frame trước khi chuyển
	int curFrameTime;						// Thời gian hiện tại của Frame đang xét
	vector<CSprite*> sprites;			// Các Sprite (Frame) để tạo nên Animation

public:
	Animation() {};
	~Animation();
	Animation(Tag tag, int index);
	Animation(Tag tag, int firstIndex, int lastIndex, int timePerFrame = DEFAULT_TPF);
	void AddSprite(Tag tag, int index);
	void Render(float x, float y);
	void AlphaRender(float x, float y, D3DCOLOR color);
	void Update(float dt);

	int CurFrameIndex;
	bool isLastFrame;
	bool isReverse;
	CSprite* GetSprite(int index);
};