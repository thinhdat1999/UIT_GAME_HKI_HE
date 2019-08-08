#include "Map.h"

Map::Map(int level)
{
	std::ifstream ifile;
	char fileName[30];
	int numSetTiles;
	sprintf_s(fileName, "Resource\\Texts\\matrix%d.txt", level);

	// Lấy thông tin hàng, cột và chiều dài, rộng của Map tương ứng
	ifile.open(fileName);
	
	ifile >> rows;
	ifile >> columns;
	width = columns << 4;
	height = rows << 4;

	rect.width = width;
	rect.height = height;
	rect.x = 0;
	rect.y = rect.height;

	
	ifile >> numSetTiles;
	// Tải các Sprite tương ứng của map vào Factory
	switch (level)
	{
	case 1:
		mapLevel = MAP1;
		break;

	case 2:
		mapLevel = MAP2;
		break;

	case 3:
		mapLevel = MAP3;
		break;
	case 4:
		mapLevel = MAP4;
		break;
	case 5:
		mapLevel = MAP5;
		break;
	case 6: 
		mapLevel = MAP6;
		break;
	}

	auto sprites = SpriteManager::GetInstance();
	for (int i = 0; i < numSetTiles; ++i)
	{
		sprites->AddSprite(new CSprite(mapLevel, i << 4, 0, i + 1 << 4, 16));
	}

	// Tạo ma trận tương ứng của Map đang xét
	mapMatrix = new int*[rows];
	for (int r = 0; r < rows; ++r)
	{
		mapMatrix[r] = new int[columns];
		for (int c = 0; c < columns; ++c)
		{
			ifile >> mapMatrix[r][c];
		}
	}

	ifile.close();


}

void Map::Update()
{
	mCamera->Update(this->rect);
	cBegin = max(0, mCamera->x / 16);
	cEnd = min(cBegin + ((mCamera->width >> 4) + 1), columns);
	rBegin = max(0, mCamera->worldY / 16);
	rEnd = min(rBegin + ((mCamera->height >> 4) + 1), rows);
}

void Map::Render()
{
	auto sprites = SpriteManager::GetInstance();
	for (int i = rBegin; i != rEnd; ++i)
	{
		for (int j = cBegin; j != cEnd; ++j)
		{
			auto sprite = sprites->GetSprite(mapLevel, mapMatrix[i][j]);
			sprite->Render((j << 4) + (16 >> 1) - (int)mCamera->x, ((i << 4) + (16 >> 1)) - (int)mCamera->worldY);
		}
	}
}