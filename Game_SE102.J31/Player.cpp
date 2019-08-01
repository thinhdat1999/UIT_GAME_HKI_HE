#include "Player.h"
Player* Player::_instance = NULL;

Player::Player()
{
	animations[STANDING] = new Animation(PLAYER, 0);
	animations[RUNNING] = new Animation(PLAYER, 1, 4, DEFAULT_TPF);
	animations[SHIELD_UP] = new Animation(PLAYER, 5);
	animations[SITTING] = new Animation(PLAYER, 6);
	animations[JUMPING] = new Animation(PLAYER, 7);
	animations[FALLING] = new Animation(PLAYER, 7);
	animations[SPINNING] = new Animation(PLAYER, 8, 9, DEFAULT_TPF >> 1);
	animations[ATTACKING_JUMP] = new Animation(PLAYER, 10);
	animations[THROWING] = new Animation(PLAYER, 11, 12, DEFAULT_TPF);
	animations[ATTACKING_STAND] = new Animation(PLAYER, 13, 14, DEFAULT_TPF);
	animations[ATTACKING_SIT] = new Animation(PLAYER, 15, 16, DEFAULT_TPF);
	animations[DASHING] = new Animation(PLAYER, 17, 18, DEFAULT_TPF);
	animations[SHIELD_DOWN] = new Animation(PLAYER, 19);
	animations[INJURED] = new Animation(PLAYER, 23);
	tag = PLAYER;
	width = PLAYER_WIDTH;
	height = PLAYER_STANDING_HEIGHT;
}

// Destructor
Player::~Player()
{
	if (curAnimation) delete curAnimation;

	for (auto it = animations.begin(); it != animations.end(); ++it)
	{
		if (it->second) delete it->second;
		animations.erase(it);
	}
}

Player* Player::GetInstance()
{
	if (_instance == NULL)
		_instance = new Player();
	return _instance;
}

void Player::Respawn()
{

	this->_allow[JUMPING] = true;
	this->_allow[ATTACKING] = false;
	this->_allow[RUNNING] = true;
	this->_allow[THROWING] = true;
	this->isHoldingShield = true;
	this->isAttacking = false;
	this->isThrowing = false;
	this->vx = this->vy = this->dx = this->dy = 0;
	this->posX = this->spawnX;
	this->posY = this->spawnY;
	this->isDead = false;
	this->isReverse = true;
	this->weaponType = SHIELD;
	this->ChangeState(new PlayerStandingState());
}

void Player::ChangeState(PlayerState * newState)
{
	delete state;
	state = newState;
	stateName = newState->StateName;
	curAnimation = animations[stateName];
}
void Player::DetectSpawnY(std::unordered_set<Platform*> grounds)
{
	this->groundBound = Platform();

	for (auto g : grounds)
	{
		if (g->rect.x < this->spawnX && this->spawnX < g->rect.x + g->rect.width
			&& g->rect.y >= groundBound.rect.y && this->spawnY > g->rect.y)
		{
			groundBound = *g;
		}
	}
	this->spawnY = this->posY = groundBound.rect.y + (this->height >> 1);
}
void Player::Update(float dt, std::unordered_set<Object*> ColliableObjects)
{
	if (flashingTime > 0)
		flashingTime -= dt;
	else flashingTime = 0;
	curAnimation->Update(dt);
	state->Update(dt);
	if (player->posX < 0)
		player->posX = 0;
	if (player->posY < 0)
		player->posY = 0;
	CollisionResult result;
	result.isCollide = false;
	result.nx = result.ny = 0;
	result.entryTime = 1.0f;
	// Sweptaabb với grid objects
	//BEGIN
	for (auto o : ColliableObjects) {
		switch (o->tag)
		{
		case ENEMY:
		case BULLET:
		{
			if (this->stateName != INJURED)
			{
				auto r = Collision::GetInstance()->SweptAABB(this->GetBoundingBox(), o->GetBoundingBox());
				if (r.isCollide)
				{
					switch (o->type)
					{
					case BOSS1:
						//set máu
						break;
					default:
						/*this->SetHealth(health - 1);*/
						break;
					}
					result = r;
					break;
				}
			}
			break;
		}
		}
	}
	if (!result.isCollide || flashingTime)
	{
		dx = (_allow[RUNNING] ? vx * dt : 0);
		dy = vy * dt;
	}
	else
	{
		this->flashingTime = 2000;
		this->ChangeState(new PlayerInjuredState());
	}
	//END
}

void Player::UpdateTexture()
{
	if (flashingTime > 0) {
		if (curTexture == flashTexture) {
			curTexture = originalTexture;
		}
		else {
			curTexture = flashTexture;
		}
	}
	else curTexture = originalTexture;
}

bool Player::DetectGround(std::unordered_set<Platform*> grounds)
{
	auto rbp = this->GetRect();					//rect broading-phase
	auto bottom = rbp.y - rbp.height;
	rbp.y = rbp.y + dy;
	rbp.height = rbp.height - dy;

	if (rbp.isContain(groundBound.rect) && (bottom >= groundBound.rect.y))
		return true;

	for (auto g : grounds)
	{
  		if (rbp.isContain(g->rect) && (bottom >= g->rect.y))
		{
			groundBound = *g;
			return true;
		}
	}
	return false;
}

// Duyệt tìm tường va chạm
// Bằng cách dịch tường và duyệt trước
bool Player::DetectWall(std::unordered_set<Wall*> walls)
{
	bool flag = false;
	auto r = this->GetRect();
	r.x = dx > 0 ? r.x : r.x + dx;
	r.width = dx > 0 ? dx + r.width : r.width - dx;

	if (r.isContain(wallBound.rect))
	{
		flag = true;
	}
	else
	{
		for (auto w : walls)
		{
			if (w->rect.isContain(r))
			{
				wallBound = *w;
				flag = true;
				break;
			}
		}
	}
	return flag;
}

// Xử lí va chạm với mặt đất theo các vùng đất hiển thị
void Player::CheckGroundCollision(std::unordered_set<Platform*> grounds)
{
	if (this->isOnWall) return;

	// Trên không
	if (this->vy)
	{
		this->isOnGround = false;
	}

	// Tìm được vùng đất va chạm
	if (DetectGround(grounds))
	{
		if (this->vy < 0)
		{
			this->isOnGround = true;
			this->vy = this->dy = 0;
			this->posY = groundBound.rect.y + (this->height >> 1);

			if (stateName == ATTACKING_STAND)
				this->_allow[RUNNING] = false;
		}
	}

	// Nếu không thì đang chạy -> rơi
	else if (!this->vy)
	{
		this->ChangeState(new PlayerFallingState());
	}
}

// Kiểm tra va chạm tường
void Player::CheckWallCollision(std::unordered_set<Wall*> walls)
{
	if (this->isOnWall) return;

	if (this->vx && this->DetectWall(walls))
	{
		float wallLeft = wallBound.rect.x;
		float wallRight = wallLeft + wallBound.rect.width;
		float playerLeft = this->posX - (this->width >> 1);
		float playerRight = this->posX + (this->width >> 1);

		if (this->vx > 0 && playerRight > wallLeft && playerRight < wallRight)
		{
			this->vx = this->dx = 0;
			this->posX = wallLeft - (this->width >> 1);

			//if (wallBound.type && this->vy
			//	&& this->posY + (this->height >> 1) <= wallBound.rect.y
			//	&& this->posY - (this->height >> 1) >= wallBound.rect.y - wallBound.rect.height)
			//{
			//	this->isReverse = false;
			//	this->ChangeState(new PlayerClingingState());
			//}
		}
		else if (this->vx < 0 && playerLeft < wallRight && playerLeft > wallLeft)
		{
			this->vx = this->dx = 0;
			this->posX = wallRight + (this->width >> 1);

			//if (wallBound.type && this->vy
			//	&& this->posY + (this->height >> 1) <= wallBound.rect.y
			//	&& this->posY - (this->height >> 1) >= wallBound.rect.y - wallBound.rect.height)
			//{
			//	this->isReverse = true;
			//	this->ChangeState(new PlayerClingingState());
			//}
		}
	}
}


void Player::Render(float cameraX, float cameraY)
{
	UpdateTexture();
	screenX = this->posX - cameraX;
	screenY = cameraY - this->posY;
	curAnimation->isReverse = this->isReverse;
	curAnimation->AlphaRender(screenX, screenY, NULL, curTexture);

}

void Player::OnKeyDown(int keyCode)
{
	switch (keyCode) {
	case DIK_Z:
		if (_allow[THROWING] && weaponType == SHIELD && isHoldingShield
			&& this->stateName != ATTACKING_SIT && this->stateName != ATTACKING_STAND 
			&& this->stateName != ATTACKING_JUMP) {
			_allow[THROWING] = false;
			_allow[ATTACKING] = true;
			this->isThrowing = true;
			ChangeState(new PlayerAttackingState());
		}
		else if (_allow[ATTACKING])
			{
			_allow[ATTACKING] = false;
			ChangeState(new PlayerAttackingState());
			this->isAttacking = true;
			}
		break;
	case DIK_SPACE:

		if (_allow[JUMPING])
		{
			_allow[JUMPING] = false;
			if (stateName == SITTING && groundBound.type == 0) {
				player->height = PLAYER_STANDING_HEIGHT;
				ChangeState(new PlayerFallingState());
			}
			else 
			ChangeState(new PlayerJumpingState());
		}
		
		break;
	case DIK_UP:
		if (_allow[SHIELD_UP]) {
			ChangeState(new PlayerShieldUpState());
		}
		break;
	}
}

void Player::OnKeyUp(int keyCode)
{
	switch (keyCode)
	{
		// Khi thả phím DOWN: state hiện tại chuyển thành đứng
	case DIK_DOWN:
		if (stateName == SITTING)
			stateName = STANDING;
		break;
	case DIK_UP:
		if (stateName == SHIELD_UP)
			ChangeState(new PlayerStandingState());
		break;
	}
}

