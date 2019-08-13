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
	animations[DEAD] = new Animation(PLAYER, 36, 37, DEFAULT_TPF << 1);
	animations[ONWATER] = new Animation(PLAYER, 24);
	animations[WATER_RUNNING] = new Animation(PLAYER, 24, 25);
	animations[WATER_FALLING] = new Animation(PLAYER, 26, 28);
	animations[WATER_DIVING] = new Animation(PLAYER, 29, 30);
	animations[INWATER] = new Animation(PLAYER, 31, 33);
	tag = PLAYER;
	width = PLAYER_WIDTH;
	height = PLAYER_STANDING_HEIGHT;
	curGroundBoundID = -1; //mặc định
	health = 15;
	MaxHealth = 15;
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
	this->isOnMovingPlatform = false;
	this->isAttacking = false;
	this->isThrowing = false;
	this->vx = this->vy = this->dx = this->dy = 0;
	player->posX = player->spawnX;
	player->posY = player->spawnY;
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
void Player::ChangeAnimation(State stateName)
{
	this->curAnimation = animations[stateName];
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
			// if(o->type = MOVINGFLATFORM) {
			//auto rbp = this->GetRect();					//rect broading-phase
			//auto bottom = rbp.y - rbp.height;
			//rbp.y = rbp.y + dy;

			//if (rbp.isContain(o->platform.rect) && (bottom >= o->platform.rect.y))
			//	player->groundBound = *o->platform
			//	player->posX += o->platform->dx;
			//	player->posY += o->platform->dy;
			//}
			if (this->stateName != INJURED)
			{
				auto r = Collision::GetInstance()->SweptAABB(this->GetBoundingBox(), o->GetBoundingBox());
				if (r.isCollide || ((player->GetRect().isContain(o->GetRect()) &&
					(player->stateName == ATTACKING_SIT || player->stateName == ATTACKING_STAND 
					|| player->stateName == ATTACKING_JUMP))))
				{
					switch (this->stateName) {
					case DASHING:
						r.isCollide = false;
						if (o->tag == ENEMY) {
							switch (o->type) {
							case BOSS1:
								o->SubtractHealth();
								break;
							case BOSS2:
								if (o->typeAI == 0)
								{
									r.isCollide = true;
									if(!this->flashingTime)
										this->SetHealth(health - 3);
								}
								else if(o->typeAI == 1) 
									o->SubtractHealth();
								break;
							case MOVING_PLATFORM: case SPLITTING_PLATFORM: case LIGHTCONTROL:
								break;
							default:
								o->ChangeState(DEAD);
								break;
							}
						}
						break;
					case SHIELD_DOWN:
						if (r.ny == 1) {
							if (o->tag == ENEMY) {
								r.isCollide = false;
								switch (o->type) {
								case BOSS1: case BOSS2:
									o->SubtractHealth();
									break;
								case MOVING_PLATFORM: case SPLITTING_PLATFORM: case LIGHTCONTROL:
									break;
								default:
									o->ChangeState(DEAD);
									break;
								}
							}
						}
						break;
					case ATTACKING_JUMP: case ATTACKING_SIT: case ATTACKING_STAND:
						if ((this->isReverse && (o->posX - this->posX > 10)) || (!this->isReverse && (10 < this->posX - o->posX))) {
							if (o->tag == ENEMY) {
								switch (o->type) {
								case BOSS1:
									r.isCollide = false;
									o->SubtractHealth();
									break;
								case BOSS2:
									if (o->typeAI == 1)
									{
										r.isCollide = false;
										o->SubtractHealth();
									}
									break;
								case MOVING_PLATFORM: case SPLITTING_PLATFORM: 
									r.isCollide = false;
									break;
								case LIGHTCONTROL:
									if(!o->flashingTime)
										o->isAttacked = true;
									r.isCollide = false;
									break;
								default:
									o->ChangeState(DEAD);
									Sound::getInstance()->play("exploded");
									break;
								}
							}
							if (o->tag == BULLET) {
								switch (o->type) {
								case BOSS2:
									auto b = (BulletMiniBoss*)o;
									if (b->bulletType == 0)
									{
										r.isCollide = false;
										b->ChangeState(DEAD);
									}
									break;
								}
							}
						}
						else {
							switch (o->type)
							{
							case LIGHTCONTROL: {
								r.isCollide = false;
								break;
							}
							case BOSS1 : case BOSS2: {
								if (!this->flashingTime)
									this->SetHealth(health - 3);
								break;
							}
							case ROCKETSOLDIER:
								if (!flashingTime && o->tag == BULLET) {
									auto b = (BulletRocketSoldier*)o;
									b->ChangeState(DEAD);

								}
								if (!this->flashingTime)
									this->SetHealth(health - 2);
								break;
							case SPLITTING_PLATFORM: case MOVING_PLATFORM:

								r.isCollide = false;
								break;
							default:
								this->SetHealth(health - 1);
								if (o->tag == BULLET) {
									auto b = (Bullet*)o;
									b->isDead = true;
								}
								break;
							}
						}
						break;
					default:
					{
						switch (o->type)
						{
						case LIGHTCONTROL: {
							r.isCollide = false;
							break;
						}
						case BOSS2: {
							if (!this->flashingTime)
								this->SetHealth(health - 3);
							break;
						}
						case BOSS1:
							//set máu
							if (!this->flashingTime)
								this->SetHealth(health - 3);
							break;
						case ROCKETSOLDIER:
							if (!flashingTime && o->tag == BULLET) {
								auto b = (BulletRocketSoldier*)o;
								b->ChangeState(DEAD);

							}
							if (!this->flashingTime)
								this->SetHealth(health - 2);
							break;
						case SPLITTING_PLATFORM: case MOVING_PLATFORM:

							r.isCollide = false;
							break;
						default:
							if (!this->flashingTime)
								this->SetHealth(health - 1);
							if (o->tag == BULLET) {
								auto b = (Bullet*)o;
								b->isDead = true;
							}
							break;
						}
					}

					break;
					}
					result = r;
				}
			}
			break;
		}
		case HOLDER:
		{
			if ((player->GetRect().isContain(o->GetRect()) &&
				(player->stateName == ATTACKING_SIT || player->stateName == ATTACKING_STAND
					|| player->stateName == ATTACKING_JUMP))) {
				auto h = (Holder*)o;
				h->isAttacked = true;
			}
			break;
		}
		case ITEM: {
			if (this->GetRect().isContain(o->GetRect()))
			{
				o->isDead = true;
				Sound::getInstance()->play("item");
				switch (o->type) {
				case KEY: 
					this->isHasKey = true;
					this->SetKey();
					break;
				case ENERGY:
					if(health < MaxHealth)
						this->SetHealth(health + 2);
					break;
				case ENERGYX10:
					if (health < MaxHealth)
						this->SetHealth(health + 2);
					break;
				case POWERSTONE:
					if (power < 100) {
						power += 1;
					}
					else if (power == 100){
						power = 0;
						MaxHealth += 2;
					}
					break;
				case POWERSTONEX10:
					if (power < 100) {
						power += 10;
					}
					else if (power == 100) {
						power = 0;
						MaxHealth += 2;
					}
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
		this->flashingTime = 3000;
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
	//rbp.height = rbp.height - dy;

	if (rbp.isContain(groundBound.rect) && (bottom >= groundBound.rect.y))
		return true;

	for (auto g : grounds)
	{
		//Nếu type platform bằng 1 thì nhảy đụng và rớt xuống
		if (rbp.isContain(g->rect) && g->type == 1 && this->vy > 0 && (g->rect.y - g->rect.height) > this->posY) {
			this->ChangeState(new PlayerFallingState());
		}
		else if (rbp.isContain(g->rect) && g->type == 5 && !this->flashingTime){
			SetHealth(health - 1);
			groundBound = *g;
			this->flashingTime = 3000;
			this->ChangeState(new PlayerInjuredState());
			return true;
		}

		else if (rbp.isContain(g->rect) && g->type == 2 && this->vy <= 0 && this->stateName != SHIELD_DOWN) {
			this->height = PLAYER_SITTING_HEIGHT;
			groundBound = *g;
			return true;
		}
  		else if (rbp.isContain(g->rect) && (bottom >= g->rect.y))
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
	//if (this->isOnWater && this->vy < 0) {
	//	this->posY = groundBound.rect.y - (this->height >> 1);
	//	this->ChangeState(new PlayerOnWaterState());
	//	return;
	//}
	// Trên không
	if (this->vy)
	{
		this->isOnGround = false;
		this->isOnWater = false;
	}
	if (this->isOnWater) return;
	if (this->groundBound.dy < 0 && this->groundBound.type == 3 && this->isOnMovingPlatform) {
		this->isOnGround = true;
		this->posY += groundBound.dy;
		if(this->vy < 0)
			this->vy = this->dy = 0;
		return;
	}
	else if (this->groundBound.dy > 0 && this->groundBound.type == 3 && this->isOnMovingPlatform) {
		this->isOnGround = true;
		if (this->vy < 0)
			this->vy = this->dy = 0;
		return;
	}
	// Tìm được vùng đất va chạm
	if (DetectGround(grounds))
	{
		if (this->vy <= 0)
		{
			if (groundBound.type != 2) {
				this->isOnGround = true;
				this->vy = this->dy = 0;
				this->posY = groundBound.rect.y + (this->height >> 1);
				// Nếu là moving platform
				//if (groundBound.type == 3) {
				//	this->posX += groundBound.dx;
				//	this->posY = groundBound.rect.y + (this->height >> 1);
				//}
				if (stateName == ATTACKING_STAND)
					this->_allow[RUNNING] = false;
			}
			else if (groundBound.type == 2) {
				this->vy = this->dy = 0;
				if (stateName != SHIELD_DOWN) {
					this->isOnWater = true;
					this->posY = groundBound.rect.y;
					this->ChangeState(new PlayerOnWaterState());
				}
				else {
					this->isOnGround = true;
					this->posY = groundBound.rect.y + (this->height >> 1);
				}
			}
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
	if (!player->isDead) {
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
		case DIK_X:

			if (_allow[JUMPING])
			{
				_allow[JUMPING] = false;
				curGroundBoundID = -1;
				/*if(groundBoundID != -1)
					curGroundBoundID = groundBoundID;*/
				if (stateName == SITTING && groundBound.type == 0) {
					player->height = PLAYER_STANDING_HEIGHT;
					this->groundBound = Platform();
					ChangeState(new PlayerFallingState());
				}
				else
				{
					this->groundBound = Platform();
					ChangeState(new PlayerJumpingState());
				}
			}

			break;
		case DIK_UP:
			if (_allow[SHIELD_UP]) {
				ChangeState(new PlayerShieldUpState());
			}
			break;
		}
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

void Player::SetHealth(int health)
{
	this->health = health;
	scoreboard->playerHealth = health;

	if (this->health <= 0)
	{
		scoreboard->playerHealth = 0;
		this->health = 0;
		this->isDead = true;
	}
}


void Player::SetPower(int power)
{
	this->power = power;
	scoreboard->playerPower = power;
}

void Player::SetKey()
{
	player->isHasKey = true;
	scoreboard->isHasKey = true;
}
