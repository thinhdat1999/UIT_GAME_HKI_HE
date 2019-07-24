#include "PlayScene.h"

PlayScene::PlayScene()
{
	_backColor = D3DCOLOR_XRGB(0, 0, 0);
	_timeCounter = 0;
	LoadMap("Resource/CharlestonMap.txt");
	MapWidth = 2048; MapHeight = 480;
	p = player;

	p->posX = p->spawnX = 50;
	p->posY = p->spawnY = 70;
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

	//grid->Update();

	//scoreboard->Update(dt);

	/*UpdateObject(dt);*/
	
	UpdatePlayer(dt);

}

/*void PlayScene::UpdateObject(float dt)
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
			grid->MoveObject(e, e->x + e->vx*dt, e->y + e->vy*dt);

			switch (e->type)
			{
			case E_CLOAKMAN:
			case E_GUNMAN:
			case E_BAZOKA:
			{
				if (e->isDoneAtk)
				{
					if (e->_state == ATTACKING && e->_curAnimation->isLastFrame)
					{
						auto bullet = EnemyBullet::CreateBullet(e->type);
						bullet->isReverse = e->isReverse;
						if (bullet->isReverse)
							bullet->vx = -bullet->vx;
						bullet->x = e->x + (e->isReverse ? -5 : 5);
						bullet->y = e->y + 3;
						bullet->ChangeState(ATK_WITH_WEAPON);
						grid->AddObject(bullet);
						e->bulletCount--;

						if (e->bulletCount == 0)
						{
							e->bulletCount = e->bulletTotal;
							e->ChangeState(RUNNING);
						}
					}
				}
				break;
			}
			}
		}
		case BULLET:
		{
			Bullet* bullet = (Bullet*)o;
			bullet->Update(dt);
			grid->MoveObject(bullet, bullet->x + bullet->dx, bullet->y + bullet->dy);
			break;
		}
		}
		++it;
	}
	this->UpdateVisibleObjects();
}
*/
void PlayScene::UpdatePlayer(float dt)
{
	
	player->Update(dt);
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
	weapon->Update(dt);
}

// Tải Scene lên màn hình bằng cách vẽ các Sprite trong Scene
void PlayScene::Render()
{
	mMap->Render();
	//scoreboard->Render();
	//for (auto o : visibleObjects)
	//	o->Render(mCamera->GetPositionX(), mCamera->GetPositionY());
	player->Render(mCamera->x, mCamera->y);
	weapon->Render(mCamera->x, mCamera->y);

}

void PlayScene::UpdateVisibleObjects()
{
	//visibleObjects.clear();
	/*auto it = visibleObjects.begin();
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
	}*/
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
