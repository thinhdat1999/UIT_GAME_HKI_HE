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
		}
		++it;
	}
	this->UpdateVisibleObjects();
}
void PlayScene::UpdatePlayer(float dt)
{
	
	player->Update(dt, grid->GetColliableObjects(player));
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
