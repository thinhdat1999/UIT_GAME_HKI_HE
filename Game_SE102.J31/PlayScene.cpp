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
					boss->DetectGround(grid->GetVisibleGrounds());
				}
				/*if (boss->bulletCountdown == 0)
				{
					for (int i = 0; i < 3; ++i)
					{
						auto b = BulletManager::CreateBullet(BOSS1);
						b->vx = !e->isReverse ? -0.5 : 0.5;
						b->posX = e->posX + (!e->isReverse ? 15 * i : -15 * i);
						b->posY = e->posY + (i - 1) * 20;
						b->ChangeState(ACTIVE);
						grid->AddObject(b);
					}
					boss->bulletCountdown = 3;
				}*/
				if (boss->isFinishAttack())
				{
					auto b = BulletManager::CreateBullet(BOSS1);
					b->bulletType = boss->bulletType;
					b->ChangeType(b->bulletType);
					b->isReverse = e->isReverse;
					if (!b->isReverse) 
						b->vx = -b->vx;
					b->posX = e->posX + (e->isReverse ? 5 : -5);
					b->posY = e->posY + 5;
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
	player->posX += player->vx * dt;
	player->posY += player->vy * dt;
	
	if (p->isAttacking) {
		p->isAttacking = false;
	}
	else if (p->isThrowing) {
		weapon->vx = WEAPON_SHIELD_SPEED;
		player->isThrowing = false;
		player->_allow[THROWING] = false;
		if (!p->isReverse) weapon->vx = -weapon->vx;
	}
	if (player->isHoldingShield)
		weapon->Update(dt);
	else
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
