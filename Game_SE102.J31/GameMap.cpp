#include "GameMap.h"

GameMap::GameMap(const char* filePath)
{
	LoadMap(filePath);
}

GameMap::~GameMap()
{
}

void GameMap::LoadMap(const char* filePath)
{
	ifstream input;
	input.open(filePath);
	int numSetTiles;
	if (input.is_open())
	{
		input >> rows >> columns;
		mWidth = columns << 4;
		mHeight = rows << 4;
		rect.width = mWidth;
		rect.height = mHeight;
		//Góc tọa độ map: bottom-left
		rect.x = 0;
		rect.y = rect.height;



		mapMatrix = new int*[rows];
		for (int i = 0; i < rows; ++i)
		{
			mapMatrix[i] = new int[columns];
			for (int j = 0; j < columns; ++j)
			{
				input >> mapMatrix[i][j];
			}
		}
		input >> numSetTiles;
		auto sprites = SpriteManager::GetInstance();
		for (int i = 0; i < numSetTiles; ++i)
		{
			sprites->AddSprite(new CSprite(MAP1, i << 4, 0, i + 1 << 4, 16));
		}
	}

}


void GameMap::Render()
{
	auto sprites = SpriteManager::GetInstance();
	for (int i = rBegin; i != rEnd; ++i)
	{
		for (int j = cBegin; j != cEnd; ++j)
		{
			auto sprite = sprites->GetSprite(MAP1, mapMatrix[i][j]);
			auto x = (j << 4) + (16 >> 1) - (int)mCamera->x;
			auto y = (i << 4) + (16 >> 1) - (int)mCamera->y;
			sprite->Render((j << 4) + (16 >> 1) - (int)mCamera->x, ((i << 4) + (16 >> 1)) - (int)mCamera->y);
		}
	}
	//Chuyển tọa độ world về tọa độ viewport sau khi vẽ map (bottom-left) 
	//Nếu vị trí y của player từ (0 -> SCREENHEIGHT / 2)  
	if (player->posY + (mCamera->height >> 1) < mCamera->height)
		mCamera->y = mCamera->height;
	else if (player->posY + (mCamera->height >> 1) > this->mHeight)
		mCamera->y = this->mHeight;
	else
		mCamera->y = player->posY + (mCamera->height >> 1);
}

int GameMap::getRow()
{
	return rows;
}

int GameMap::getColumn()
{
	return columns;
}

void GameMap::Update(float dt)
{
	mCamera->Update(this->rect);
	cBegin = max(0, mCamera->x / 16);
	cEnd = min(cBegin + ((mCamera->width >> 4) + 1), columns);
	rBegin = max(0, mCamera->y / 16);
	rEnd = min(rBegin + ((mCamera->height >> 4) + 1), rows);
}