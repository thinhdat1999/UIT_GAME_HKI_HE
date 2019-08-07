#include "PlayScene.h"

PlayScene::PlayScene()
{
	_backColor = D3DCOLOR_XRGB(0, 0, 0);
	_timeCounter = 0;
	LoadMap("Resource/CharlestonMap.txt");
	MapWidth = 2048; MapHeight = 480;
	grid = new Grid(MapWidth, MapHeight);

	p = player;

	p->posX = p->spawnX = 50;
	p->posY = p->spawnY = 70;
	p->DetectSpawnY(grid->GetColliableGrounds(p));
	p->Respawn();

	weapon = new WeaponShield();
	weapon->posX = p->posX + (p->isReverse ? 5 : -5);
	weapon->posY = p->posY + 5;
	weapon->isReverse = p->isReverse;
	if (!p->isReverse) weapon->vx = -weapon->vx;
	mCamera->x = 0;
	mCamera->y = p->posY + (mCamera->height >> 1);

}

PlayScene::~PlayScene()
{
}

void PlayScene::LoadMap(const char * filePath)
{
	mMap = new GameMap(filePath);
	//scoreboard = new ScoreBoard();

}

void PlayScene::Update(float dt)
{
	mCamera->x = p->posX - (mCamera->width >> 1);
	mCamera->y = p->posY + (mCamera->height >> 1);
	mMap->Update(dt);
	grid->Update();

	//scoreboard->Update(dt);

	UpdateObjects(dt);
	UpdatePlayer(dt);

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
	
	player->Update(dt, grid->GetColliableObjects(player));
	player->CheckGroundCollision(grid->GetColliableGrounds(player));
	player->CheckWallCollision(grid->GetColliableWalls(player));
	player->posX += player->dx;
	player->posY += player->dy;
	
	if (p->isAttacking) {
		p->isAttacking = false;
	}
	else if (p->isThrowing) {
		weapon->vx = WEAPON_SHIELD_SPEED;
		player->isThrowing = false;
		player->_allow[THROWING] = false;
		if (!p->isReverse) weapon->vx = -weapon->vx;
	}
	//if (player->isHoldingShield)
	//	weapon->Update(dt);
	//else
	weapon->Update(dt, grid->GetColliableObjects(weapon));
}

// Tải Scene lên màn hình bằng cách vẽ các Sprite trong Scene
void PlayScene::Render()
{
	mMap->Render();
	//scoreboard->Render();
	for (auto o : visibleObjects)
		o->Render(mCamera->x, mCamera->y);
	player->Render(mCamera->x, mCamera->y);
	weapon->Render(mCamera->x, mCamera->y);

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
