#include "ScoreBoard.h"

ScoreBoard* ScoreBoard::_instance = NULL;

ScoreBoard::ScoreBoard()
{
	score = 0;
	this->sprites = SpriteManager::GetInstance();
	this->playerPower = 0;
	this->playerHealth = 10;
	this->delayTime = 300;
	exitcurColor = originalColor;
}

void ScoreBoard::UpdateColor()
{
	if (playerHealth < 5) {
		if (curColor == flashColor) {
			curColor = originalColor;
		}
		else {
			curColor = flashColor;
		}
	}
	else curColor = originalColor;
	if (delayTime <= 0) {
		if (exitcurColor == flashColor) {
			exitcurColor = originalColor;
		}
		else {
			exitcurColor = flashColor;
		}
		delayTime = 300;
	}
}

void ScoreBoard::Render()
{
	UpdateColor();
	RenderPlayerHealth();
	RenderExit(46, 24);
}

void ScoreBoard::RenderHealth(float x, float y)
{
	int curHealth;
	if (playerHealth % 5 == 0) {
		curHealth = playerHealth / 5;
	}
	else {
		curHealth = playerHealth / 5 + 1;
	}
	for (int i = 0; i < curHealth; i++) {
		sprites->GetSprite(PLAYER, 34)->AlphaRender(x, y + i*8, curColor, NULL);
	}

}

void ScoreBoard::RenderExit(float x, float y)
{
	if(isHasKey)
		sprites->GetSprite(PLAYER, 35)->AlphaRender(x, y, exitcurColor, NULL);
}


void ScoreBoard::RenderPlayerHealth()
{
	RenderHealth(28 , 16);
}
void ScoreBoard::Update(float dt)
{
	/*if (isEndGame)
	{
		if (this->playerPower > 0)
		{
			this->score += 200;
			this->playerPower--;
		}
	}*/
	if (delayTime > 0)
		delayTime -= dt;
}

ScoreBoard* ScoreBoard::GetInstance()
{
	if (_instance == NULL)
		_instance = new ScoreBoard();
	return _instance;
}