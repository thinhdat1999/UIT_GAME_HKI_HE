﻿#include "Animation.h"

// Render Animation tại vị trí (x,y) lên màn hình
void Animation::Render(float x, float y)
{
	if (sprites[CurFrameIndex] != NULL)
	{
		sprites[CurFrameIndex]->_isFlipHorizontal = this->isReverse;
		sprites[CurFrameIndex]->Render(x, y);
	}
}

// Update Animation sau thời gian delta-time
void Animation::Update(float dt)
{
	// Nếu quá thời gian tồn tại của 1 Frame -> chuyển Frame kế
	if (curFrameTime > timePerFrame)
	{
		curFrameTime = 0;

		// Kiểm tra đến Frame cuối -> trở lại Frame đầu
		if (++CurFrameIndex == totalFrames)
		{
			isLastFrame = true;
			CurFrameIndex = 0;
		}
	}
	// Nếu không thì tiếp tục cộng dồn thời gian cho Frame đang xét
	else
	{
		isLastFrame = false;
		curFrameTime += dt;
	}
}

Animation::~Animation()
{
	for (auto s : sprites)
	{
		s = nullptr;
	}
	sprites.clear();
}

Animation::Animation(Tag tag, int index)
{
	sprites.push_back(SpriteManager::GetInstance()->GetSprite(tag, index));
	totalFrames = 1;
	timePerFrame = DEFAULT_TPF;
	CurFrameIndex = 0;
	isLastFrame = false;
}

Animation::Animation(Tag tag, int firstIndex, int lastIndex, int tpf)
{
	sprites = SpriteManager::GetInstance()->GetSprites(tag, firstIndex, lastIndex);
	totalFrames = sprites.size();
	timePerFrame = tpf;
	CurFrameIndex = 0;
	isLastFrame = false;
}

CSprite * Animation::GetSprite(int i)
{
	return sprites[i];
}