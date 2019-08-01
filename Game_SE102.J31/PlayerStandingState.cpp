#include "PlayerStandingState.h"

// Khởi tạo State đang đứng của nhân vật
PlayerStandingState::PlayerStandingState()
{
	player->vx = 0;
	player->vy = 0;
	player->_allow[RUNNING] = true;
	player->_allow[JUMPING] = true;
	player->_allow[SITTING] = true;
	player->_allow[SHIELD_UP] = true;
	StateName = STANDING;
	if (player->isHoldingShield) player->_allow[THROWING] = true;
}

void PlayerStandingState::Update(float dt)
{
	this->HandleKeyboard();
}

// Xử lí các sự kiện bàn phím cho nhân vật
void PlayerStandingState::HandleKeyboard()
{
	// Nhấn phím di chuyển -> RUNNING
	if (keyCode[DIK_LEFT] || keyCode[DIK_RIGHT])
	{
		bool reset = false;
		if (player->buttonPressed) {
			if (player->FirstButton == keyCode[DIK_RIGHT] ? keyCode[DIK_RIGHT] : keyCode[DIK_LEFT])
			{
				int delay = GetTickCount() - player->timeOfFirstButton;
				if (delay < 180) {
					player->ChangeState(new PlayerDashingState());
				}
				reset = true;
			}
		}
		else {
			player->ChangeState(new PlayerRunningState());
			player->buttonPressed = true;
			player->FirstButton = keyCode[DIK_LEFT] ? keyCode[DIK_LEFT] : keyCode[DIK_RIGHT];
			player->timeOfFirstButton = GetTickCount();
		}
		if (reset) {
			player->buttonPressed = false;
			reset = false;
		}
		
	}
	/* Nhấn phím DOWN -> SITTING*/
	else if (keyCode[DIK_DOWN])
	{
		player->ChangeState(new PlayerSittingState());
	}
}