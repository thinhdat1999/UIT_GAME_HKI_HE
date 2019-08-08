#include "PlayScene.h"

PlayScene::PlayScene(int level)
{
	_backColor = D3DCOLOR_XRGB(0, 0, 0);
	map = MapManager::GetInstance()->GetMap(level);
	grid = new Grid(level);

	delayStart = SCENE_DELAY_START;
	gameLevel = level;

	p = player;
	switch (level) {
	case 1: 
		p->posX = p->spawnX = 50;
		p->posY = p->spawnY = 70;
		break;
	case 2: case 3:
		p->posX = p->spawnX = 20;
		p->posY = p->spawnY = 70;
		break;
	case 4: case 5:
		p->posX = p->spawnX = 15;
		p->posY = p->spawnY = 802;
		break;
	case 6:
		p->posX = p->spawnX = 20;
		p->posY = p->spawnY = 70;
		break;
	}
	p->posX = p->spawnX = 15;
	p->posY = p->spawnY = 802;
	p->DetectSpawnY(grid->GetColliableGrounds(p));
	p->Respawn();
	p->SetHealth(p->health);

	weapon = new WeaponShield();
	weapon->posX = p->posX + (p->isReverse ? 5 : -5);
	weapon->posY = p->posY + 5;
	weapon->isReverse = p->isReverse;
	if (!p->isReverse) weapon->vx = -weapon->vx;

	mCamera->x = 0;
	mCamera->y = p->posY + (mCamera->height >> 1);
	Sound::getInstance()->setVolume(90.0f, "Theme");
	Sound::getInstance()->play("Theme", true);
	if (level == 2) {
		Sound::getInstance()->stop("Theme");
		Sound::getInstance()->play("bossmap", true);
	}

	switch (gameLevel)
	{
	case 1:
		endRect = Rect(2000, 128, 30, 352);
		break;

	case 2:
		endRect = Rect(0, 0, 0, 0);
		//auto button = new Rect(80, 416, 16, 16);
		//auto button2 = new Rect(16, 352, 16, 16);
		//auto button3 = new Rect(176, 384, 16, 16);
		break;

	case 3:
		endRect = Rect(0, 0, 0, 0);
		break;
	}
}

PlayScene::~PlayScene()
{
}


void PlayScene::Update(float dt)
{
	if (delayRestart)
	{
		delayRestart -= dt;
		if (delayRestart <= 0)
		{
			delayRestart = 0;
			this->RestartScene();
		}
		return;
	}

	UpdateScene();

	scoreboard->Update(dt);

	UpdateObjects(dt);
	UpdatePlayer(dt);

	if (p->GetRect().isContain(endRect))
	{
		delayEnd = SCENE_DELAY_END;
		/*Sound::getInstance()->play("win");*/

		if (gameLevel < NUMBER_MAP_LEVEL && player->isHasKey)
		{
			char soundFileName[10];
			sprintf_s(soundFileName, "Theme", gameLevel);
			Sound::getInstance()->stop(soundFileName);
			SceneManager::GetInstance()->ReplaceScene(new PlayScene(gameLevel + 1));
			return;
		}
	}
}

void PlayScene::UpdateObjects(float dt)
{
	auto it = visibleObjects.begin();
	while (it != visibleObjects.end())
	{
		auto o = *it;
		switch (o->tag)
		{
		case ENEMY:
		{
			auto e = (Enemy*)o;
			e->Update(dt);
			grid->MoveObject(e, e->posX + e->dx, e->posY + e->dy);

			switch (e->type)
			{
			case BOSS1:
			{

				auto boss = (EnemyWizard*)e;
				if (!boss->firstJump) {
					if (boss->delayHit > 0) {
						boss->delayHit -= dt;
					}
				}
				if (!boss->isOnGround) {
					boss->CheckGroundCollision(grid->GetVisibleGrounds());
				}
				
				if (boss->isFinishAttack())
				{
					auto b = BulletManager::CreateBullet(BOSS1);
					b->bulletType = boss->bulletType;
					b->ChangeType(b->bulletType);
					b->isReverse = e->isReverse;
					if (!b->isReverse) 
						b->vx = -b->vx;
					b->posX = e->posX + (e->isReverse ? 5 : -5);
					b->posY = e->posY + 8;
					b->ChangeState(ACTIVE);
					grid->AddObject(b);
					boss->bulletCount--;
					if (e->bulletCount == 0)
					{
						e->bulletCount = e->bullets;
						boss->ChangeState(JUMPING);
					}
				}
				if (boss->stateName == ATTACKING_JUMP && boss->bulletCount > 0) {
					auto r = boss->GetRect();
					r.y = player->GetRect().y;
					if (r.isContain(player->GetRect())) {
						auto b = BulletManager::CreateBullet(BOSS1);
						b->bulletType = boss->bulletType;
						b->ChangeType(b->bulletType);
						b->isReverse = e->isReverse;
						b->posX = player->posX;
						b->posY = e->posY - 15;
						b->ChangeState(ACTIVE);
						grid->AddObject(b);
						boss->bulletCount--;
					}
				}

				if (boss->stateName == DEAD)
				{
					for (auto o : visibleObjects)
					{
						if (o->tag == BULLET)
						{
							auto b = (Bullet*)o;
							b->ChangeState(DEAD);
						}
					}
				}
				break;
			}
			case BOSS2: 
			{
				auto boss = (EnemyMiniBoss*)e;
				if (!boss->isOnGround) {
					boss->CheckGroundCollision(grid->GetVisibleGrounds());
				}
				if (boss->stateName == ATTACKING && boss->bulletType == 0) {
					if (!boss->isFinishAttack() && boss->bulletCount > 0) {
						auto b = new BulletMiniBoss();
						b->bulletType = boss->bulletType;
						b->ChangeType(b->bulletType);
						b->isReverse = e->isReverse;
						if (!b->isReverse)
							b->vx = -b->vx;
						b->posX = e->posX;
						b->posY = e->posY + (e->height >> 1) + (b->height >> 1);
						b->ChangeState(ACTIVE);
						grid->AddObject(b);
						boss->bulletCount--;
						boss->b = b;
					}
					else if (boss->canShoot) {
						auto b = (BulletMiniBoss*)boss->b;
						b->isOut = true;
						boss->canShoot = false;
					}
				}
				if (boss->bulletType == 1 && boss->isFinishAttack() && boss->canShoot)
				{
					auto b = BulletManager::CreateBullet(BOSS2);
					b->bulletType = boss->bulletType;
					b->ChangeType(b->bulletType);
					b->isReverse = e->isReverse;
					if (!b->isReverse)
						b->vx = -b->vx;
					b->posX = e->posX + (e->isReverse ? 5 : -5);
					b->posY = e->posY + 10;
					b->ChangeState(ACTIVE);
					grid->AddObject(b);
					boss->canShoot = false;
				}
				break;
			}
			case BLUESOLDIER: 
			{
				auto soldier = (EnemyBlueSoldier*)e;
				if (soldier->typeAI == 1) {
					
					if (!soldier->isOnGround)
					{
						soldier->DetectCurGround(grid->GetColliableGrounds(soldier));
					}
					break;
				}
				if (soldier->isFinishAttack())
				{
					if (soldier->bulletCount > 0)
					{
						auto b = BulletManager::CreateBullet(e->type);
						b->isReverse = e->isReverse;
						if (!b->isReverse)
							b->vx = -b->vx;
						b->posX = e->posX + (e->isReverse ? 10 : -10);
						b->posY = e->posY + 15;
						b->ChangeState(ACTIVE);
						grid->AddObject(b);
						soldier->bulletCount--;
					}
					else if (soldier->bulletCount == 0 && soldier->delayTime < 2200)
					{
						soldier->bulletCount = soldier->bullets;
						if (e->typeAI == 0) {
							e->ChangeState(SITTING);
						}
						else
							e->ChangeState(RUNNING);
					}
				}
				break;
			}
			case ROCKETSOLDIER: 
			{
				auto soldier = (EnemyRocketSoldier*)e;
				if (soldier->typeAI == 1) {

					if (!soldier->isOnGround)
					{
						soldier->DetectCurGround(grid->GetColliableGrounds(soldier));
					}
					break;
				}
				if (soldier->isFinishAttack())
				{
					if (soldier->bulletCount > 0)
					{
						auto b = BulletManager::CreateBullet(e->type);
						b->isReverse = e->isReverse;
						if (!b->isReverse)
							b->vx = -b->vx;
						b->posX = e->posX + (e->isReverse ? 10 : -10);
						b->posY = e->posY + 15;
						b->ChangeState(ACTIVE);
						grid->AddObject(b);
						soldier->bulletCount--;
					}
					else if (soldier->bulletCount == 0 && soldier->delayTime < 0)
					{
						soldier->bulletCount = soldier->bullets;
						if (soldier->typeAI == 0) {
							if(soldier->stateName == ATTACKING_SIT)
								soldier->ChangeState(ATTACKING);
							else soldier->ChangeState(ATTACKING_SIT);
						}
						else
							soldier->ChangeState(RUNNING);
					}
				}
				break;
			}
			case SPLITTING_PLATFORM: {
				auto splitPlatform = (SplittingPlatform*)e;
				auto rbp = player->GetRect();					//rect broading-phase
				auto bottom = rbp.y - rbp.height;
				rbp.y = rbp.y + player->dy;

				if (rbp.isContain(splitPlatform->GetRect()) && (bottom >= splitPlatform->GetRect().y) && splitPlatform->stateName == STANDING)
				{
					player->groundBound = *splitPlatform->platform;
					splitPlatform->ChangeState(RUNNING);
				}
				else if (splitPlatform->stateName == ACTIVE && splitPlatform->isHasPlayerOn) {
					player->groundBound = Platform();
					player->ChangeState(new PlayerFallingState());
					splitPlatform->isHasPlayerOn = false;
				}
				break;
			}
			case MOVING_PLATFORM: {
				auto movingPlatform = (MovingPlatform*)e;
				auto rbp = player->GetRect();					//rect broading-phase
				auto bottom = rbp.y - rbp.height;
				if(player->isOnMovingPlatform && movingPlatform->dy < 0)
				rbp.y = rbp.y + movingPlatform->dy;
				else 
					rbp.y = rbp.y + player->dy;

				if (rbp.isContain(movingPlatform->GetRect()) && (bottom >= movingPlatform->GetRect().y) && !player->isOnMovingPlatform)
				{
					player->groundBound = *movingPlatform->platform;
					/*player->groundBound.dx = movingPlatform->dx;*/
					player->isOnMovingPlatform = true;
					/*movingPlatform->isHasPlayerOn = true;*/
				}
				else if (rbp.isContain(movingPlatform->GetRect()) && player->isOnMovingPlatform) {
					player->groundBound = *movingPlatform->platform;
					player->posX += movingPlatform->dx;
		/*			player->posY = movingPlatform->platform->rect.y + (player->height >> 1);*/
					if (movingPlatform->dy > 0)
						player->posY = movingPlatform->platform->rect.y + (player->height >> 1);
					else {
						
						player->posY = movingPlatform->platform->rect.y + (player->height >> 1) + movingPlatform->dy;
					}/*+ movingPlatform->dy*/;
				}
				else if(player->isOnMovingPlatform && !rbp.isContain(movingPlatform->GetRect())) {
					player->isOnMovingPlatform = false;
					player->groundBound = Platform();
				}
				break;
			}
			case LIGHTCONTROL: {
				auto button = (LightControl*)o;
				if (button->isAttacked) {
					button->isAttacked = false;
					if (gameLevel == 2 || gameLevel == 4) {
						map = MapManager::GetInstance()->GetMap(gameLevel + 1);
						gameLevel++;
					}
					else if (gameLevel == 3 || gameLevel == 5) {
						map = MapManager::GetInstance()->GetMap(gameLevel - 1);
						gameLevel--;
					}
				}
				break;
			}
			}

			break;
		}
		case HOLDER:
		{
			auto h = (Holder*)o;
			h->Update(dt);
			break;
		}
		case ITEM:
		{
			Item* i = (Item*)o;
			i->Update(dt);
			grid->MoveObject(i, i->posX, i->posY + i->dy);
			break;
		}
		case BULLET:
		{
			Bullet* b = (Bullet*)o;
			switch (b->type) {
			case BOSS2: {
				if (!b->isOnGround && b->bulletType == 0)
					b->CheckGroundCollision(grid->GetColliableGrounds(b));
				break;
			}
			}
			b->Update(dt);
			grid->MoveObject(b, b->posX + b->dx, b->posY + b->dy);
			break;
		}
		}
		++it;
	}
	this->UpdateVisibleObjects();
}
void PlayScene::UpdatePlayer(float dt)
{
	if (p->isDead)
	{
		player->vy = -PLAYER_FALLING_SPEED;
		player->ChangeAnimation(DEAD);
		Sound::getInstance()->stop("Theme");
		Sound::getInstance()->play("playerdead");
		this->SetRestartScene();
		return;
	}
	player->Update(dt, grid->GetColliableObjects(player));
	player->CheckGroundCollision(grid->GetColliableGrounds(player));
	player->CheckWallCollision(grid->GetColliableWalls(player));
	player->posX += player->dx;
	player->posY += player->dy;
	if (player->posX < mCamera->GetRect().x) {
		player->posX = mCamera->x + (player->width >> 1);
	}
	if (player->posX > mCamera->GetRect().x + mCamera->GetRect().width) {
		player->posX = mCamera->GetRect().x + mCamera->GetRect().width - (player->width * 2);
	}
	if (p->isAttacking) {
		p->isAttacking = false;
	}
	else if (p->isThrowing) {
		weapon->vx = WEAPON_SHIELD_SPEED;
		player->isThrowing = false;
		player->_allow[THROWING] = false;
		if (!p->isReverse) weapon->vx = -weapon->vx;
	}
	weapon->Update(dt, grid->GetColliableObjects(weapon));
}

// Tải Scene lên màn hình bằng cách vẽ các Sprite trong Scene
void PlayScene::Render()
{
	map->Render();
	scoreboard->Render();
	for (auto o : visibleObjects)
		o->Render(mCamera->x, mCamera->y);
	player->Render(mCamera->x, mCamera->y);
	weapon->Render(mCamera->x, mCamera->y);

}

void PlayScene::UpdateScene()
{
	if (mCamera->isLocked()) {
		mCamera->x = p->posX - (mCamera->width >> 1);
		mCamera->y = p->posY + (mCamera->height >> 1);
		
	}
	map->Update();
	grid->Update();
}

void PlayScene::UpdateVisibleObjects()
{
	auto it = visibleObjects.begin();
	while (it != visibleObjects.end())
	{
		if ((*it)->tag != WEAPON)
		{
			it = visibleObjects.erase(it);
		}
		else ++it;
	}
	for (auto o : grid->GetVisibleObjects())
	{
		visibleObjects.insert(o);
	}
}
void PlayScene::SetRestartScene()
{
	Sound::getInstance()->stop("Theme");
	Sound::getInstance()->play("over");
	delayRestart = SCENE_DELAY_RESTART;
	p->health = p->MaxHealth;
	p->SetHealth(p->health);
}

void PlayScene::RestartScene()
{
	Sound::getInstance()->setVolume(90.0f, "Theme");
	Sound::getInstance()->play("Theme", true);
	if (gameLevel == 2) {
		Sound::getInstance()->stop("Theme");
		Sound::getInstance()->play("bossmap", true);
	}
	player->Respawn();
	player->ChangeState(new PlayerStandingState());

	for (auto o : grid->respawnObjects)
	{
		switch (o->tag)
		{
		case ENEMY:
		{
			auto e = (Enemy*)o;
			e->ChangeState(STANDING);
			break;
		}
		case HOLDER:
		{
			auto h = (Holder*)o;
			h->isDead = false;
			break;
		}
		}
		grid->MoveObject(o, o->spawnX, o->spawnY);
	}

	for (auto o : visibleObjects)
	{
		if (o->tag == ENEMY)
		{
			auto e = (Enemy*)o;
			e->ChangeState(STANDING);
			grid->MoveObject(o, o->spawnX, o->spawnY);
		}
	}
	this->visibleObjects.clear();
	grid->respawnObjects.clear();
}
void PlayScene::OnKeyDown(int key)
{
	keyCode[key] = true;
	player->OnKeyDown(key);
}

void PlayScene::OnKeyUp(int key)
{
	keyCode[key] = false;
	player->OnKeyUp(key);
}
