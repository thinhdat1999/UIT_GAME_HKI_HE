#pragma once
#include "SpriteManager.h"
#include "Camera.h"
#include <sstream>

class ScoreBoard {
public:
	int score;
	int playerHealth;
	int playerPower;
	bool isHasKey;
	SpriteManager* sprites;

	D3DCOLOR originalColor = D3DCOLOR_XRGB(255, 255, 255);
	D3DCOLOR flashColor = D3DCOLOR_ARGB(0, 255, 255, 255);
	D3DCOLOR curColor, exitcurColor;

	ScoreBoard();
	void UpdateColor();
	void Render();
	void Update(float dt);
	static ScoreBoard* GetInstance();

private:
	static ScoreBoard* _instance;
	void RenderHealth(float x, float y);
	void RenderExit(float x, float y);
	void RenderPlayerHealth();
};