#include "Grid.h"


void Grid::CreateGridFile(int level)
{
	std::ifstream ifile;
	char gridFileName[30];
	sprintf_s(gridFileName, "Resource\\Texts\\grid%d.txt", level);

	// Nếu không tìm thấy file grid -> Tạo file từ map objects trong level đó
	ifile.open(gridFileName);
	if (ifile.fail())
	{
		ifile.close();

		// Đọc file matrix để lấy size map -> xác định số cell trong grid
		char fileMapName[30];
		sprintf_s(fileMapName, "Resource\\Texts\\matrix%d.txt", level);
		ifile.open(fileMapName);

		int numTiles, rowTiles, colTiles;
		ifile >> rowTiles >> colTiles >> numTiles;
		ifile.close();

		int colCell = ceil((float)(colTiles * TILE_SIZE) / (SCREEN_WIDTH >> 1));
		int rowCell = ceil((float)(rowTiles * TILE_SIZE) / (SCREEN_HEIGHT >> 1)) + 1;

		// Đọc từng loại object và đẩy vào grid (mỗi loại có thông số cách tính Rect khác nhau)
		char objectsFileName[30];
		sprintf_s(objectsFileName, "Resource\\Texts\\objects%d.txt", level);
		ifile.open(objectsFileName);

		auto objs = std::vector<GameObject*>();

		while (!ifile.eof())
		{
			auto obj = new GameObject();
			Rect* rect = NULL;
			char type;
			int value;

			ifile >> type;
			obj->type = type;

			switch (type)
			{
			case 'g': //ground: x, y, width, height, type
			case 'w': //wall: x, y, width, height
			{
				int n = (type == 'g' ? 5 : 4);
				for (int i = 0; i < n; ++i)
				{
					ifile >> value;
					obj->value.push_back(value);
				}

				rect = new Rect(obj->value[0], obj->value[1], obj->value[2], obj->value[3]);
				break;
			}

			case 'h': //holder: posX, posY, itemID
			{
				for (int i = 0; i < 3; ++i)
				{
					ifile >> value;
					obj->value.push_back(value);
				}

				auto h = new Holder(obj->value[2]);
				h->posX = obj->value[0];
				h->posY = obj->value[1];
				rect = new Rect(h->GetRect());
				delete h;
				break;
			}

			case 'e': //enemy: enemyID, posX, posY, typeAI, activeDistance
			{
				for (int i = 0; i < 3; ++i)
				{
					ifile >> value;
					obj->value.push_back(value);
				}

				auto e = EnemyManager::CreateEnemy(obj->value[0]);
				e->posX = obj->value[1];
				e->posY = obj->value[2];

				// đọc thêm typeAI nếu có
				switch (e->type)
				{
				case ROCKETSOLDIER:
				{
					ifile >> value;
					obj->value.push_back(value);
					ifile >> value;
					obj->value.push_back(value);
					break;
				}
				case BLUESOLDIER:
				{
					ifile >> value;
					obj->value.push_back(value);
					e->typeAI = value;
					if (e->typeAI == 1 || e->typeAI == 0) {
						ifile >> value;
						obj->value.push_back(value);
					}
					break;
				}
				//Moving platform có typeAI, vx, vy, distanceX, distanceY
				case MOVING_PLATFORM: {
					ifile >> value;
					obj->value.push_back(value);
					e->typeAI = value;
					if (e->typeAI == 0) {
						for (int i = 0; i < 2; ++i) {
							ifile >> value;
							obj->value.push_back(value);
						}
					}
					else if (e->typeAI == 1) {
						for (int i = 0; i < 4; ++i) {
							ifile >> value;
							obj->value.push_back(value);
						}
					}
					
					break;
				}
				}
				rect = new Rect(e->GetRect());
				delete e;
				break;
			}
			}

			// Xác định cell object đó và đẩy vào
			obj->leftCell = rect->x / Cell::width;
			obj->rightCell = (rect->x + rect->width) / Cell::width;
			obj->topCell = rect->y / Cell::height;
			obj->bottomCell = (rect->y - rect->height) / Cell::height;
			delete rect;
			objs.push_back(obj);
		}

		// Viết ra file grid và xoá các object sau khi có thông số
		std::ofstream ofile;
		ofile.open(gridFileName);
		ofile << colCell << " " << rowCell << " " << objs.size();

		for (auto o : objs)
		{
			ofile << "\n" << o->type << "\n";
			for (auto v : o->value)
			{
				ofile << v << " ";
			}
			ofile << "\n" << o->leftCell << " " << o->topCell << " " << o->rightCell << " " << o->bottomCell;
			delete o;
		}

		ifile.close();
		ofile.close();
	}
	else ifile.close();
}

Grid::Grid(int level)
{
	this->CreateGridFile(level);

	std::ifstream ifile;
	char gridFileName[30];
	sprintf_s(gridFileName, "Resource\\Texts\\grid%d.txt", level);

	int numObjects;
	ifile.open(gridFileName);
	ifile >> columns >> rows >> numObjects;

	for (int y = 0; y < rows; ++y)
	{
		auto row = std::vector<Cell*>();
		for (int x = 0; x < columns; ++x)
		{
			row.push_back(new Cell(x, y));
		}
		cells.push_back(row);
	}

	int value;
	char type;
	int top, left, right, bottom;
	std::vector<int> values;
	std::unordered_set<Rect*> grounds;

	for (int i = 0; i < numObjects; ++i)
	{
		ifile >> type;
		switch (type)
		{
		case 'g': // ground: x,y,width,height, type
		{
			for (int i = 0; i < 5; ++i)
			{
				ifile >> value;
				values.push_back(value);
			}
			auto ground = new Platform(values[0], values[1], values[2], values[3], values[4]);

			ifile >> left >> top >> right >> bottom;
			for (int r = bottom; r <= top; ++r)
			{
				if (r < 0 || r >= rows) continue;
				for (int c = left; c <= right; ++c)
				{
					if (c < 0 || c >= columns) continue;
					cells[r][c]->grounds.push_back(ground);
				}
			}
			break;
		}

		case 'w': // wall: x,y,width,height
		{
			for (int i = 0; i < 4; ++i)
			{
				ifile >> value;
				values.push_back(value);
			}
			auto wall = new Wall(values[0], values[1], values[2], values[3]);

			ifile >> left >> top >> right >> bottom;
			for (int r = bottom; r <= top; ++r)
			{
				if (r < 0 || r >= rows) continue;
				for (int c = left; c <= right; ++c)
				{
					if (c < 0 || c >= columns) continue;
					cells[r][c]->walls.push_back(wall);
				}
			}
			break;
		}

		case 'h': // holder: posX, posY, itemID
		{
			for (int i = 0; i < 3; ++i)
			{
				ifile >> value;
				values.push_back(value);
			}
			auto holder = new Holder(values[2]);
			holder->spawnX = holder->posX = values[0];
			holder->spawnY = holder->posY = values[1];

			ifile >> left >> top >> right >> bottom;
			for (int r = bottom; r <= top; ++r)
			{
				if (r < 0 || r >= rows) continue;
				for (int c = left; c <= right; ++c)
				{
					if (c < 0 || c >= columns) continue;
					cells[r][c]->objects.insert(holder);
				}
			}
			break;
		}

		case 'e': // enemy: typeID, posX, posY, typeAI, activeDistance
		{
			for (int i = 0; i < 3; ++i)
			{
				ifile >> value;
				values.push_back(value);
			}
			auto enemy = EnemyManager::CreateEnemy(values[0]);
			enemy->spawnX = enemy->posX = values[1];
			enemy->spawnY = enemy->posY = values[2];
			// Xác định ground xuất hiện cho các enemy ở đất
			switch (enemy->type)
			{
			case BLUESOLDIER:
			case ROCKETSOLDIER:
				enemy->DetectSpawnY(this->GetColliableGrounds(enemy));
				break;
			}

			// Xác định typeAI và activeDistance cho các Enemy 
			switch (enemy->type)
			{
			case BLUESOLDIER:
			{
				auto soldier = (EnemyBlueSoldier*)enemy;
				ifile >> value;
				values.push_back(value);
				soldier->typeAI = value;
				if (soldier->typeAI == 1) {
					ifile >> value;
					values.push_back(value);
					soldier->activeDistance = value;
				}
				else if (soldier->typeAI == 0) {
					ifile >> value;
					values.push_back(value);
					soldier->delay = value;
				}
				break;
			}
			case ROCKETSOLDIER: {
				ifile >> value;
				values.push_back(value);
				auto soldier = (EnemyRocketSoldier*)enemy;
				soldier->typeAI = value;
				ifile >> value;
				values.push_back(value);
				soldier->bulletType = value;
				break;
			}
			case MOVING_PLATFORM: {
				auto platform = (MovingPlatform*)enemy;
				ifile >> value;
				values.push_back(value);
				platform->typeAI = value;
				platform->platformID = value;
				if (platform->typeAI == 0) {
					ifile >> value;
					values.push_back(value);
					platform->vx = platform->speed = float(value) / 10;
					ifile >> value;
					values.push_back(value);
					platform->maxDistanceX = value;
				}
				else if (platform->typeAI == 1) {
					ifile >> value;
					values.push_back(value);
					platform->vx = platform->speed = float(value) / 10;
					ifile >> value;
					values.push_back(value);
					platform->vy = value;
					ifile >> value;
					values.push_back(value);
					platform->maxDistanceX = value;
					ifile >> value;
					values.push_back(value);
					platform->maxDistanceY = value;
				}
				break;
			}
			}

			ifile >> left >> top >> right >> bottom;
			for (int r = bottom; r <= top; ++r)
			{
				if (r < 0 || r >= rows) continue;
				for (int c = left; c <= right; ++c)
				{
					if (c < 0 || c >= columns) continue;
					cells[r][c]->objects.insert(enemy);
				}
			}
			
			break;
		}
		}
		values.clear();
	}
	ifile.close();
}
Grid::Grid(int mapWidth, int mapHeight)
{
	//Khởi tạo mảng cells[][] theo rows và columns dựa trên độ lớn của map
	rows = mapHeight / Cell::height;
	columns = ceil((float)(mapWidth) / Cell::width);
	for (int y = 0; y < rows; ++y)
	{
		auto row = vector<Cell*>();
		for (int x = 0; x < columns; ++x) {
			row.push_back(new Cell(x, y));
		}
		cells.push_back(row);
	}

	//Add Object, grounds, wall Stage 1
	//BEGIN
	//auto *h = new Holder(4);
	//h->spawnX = h->posX = 72;
	//h->spawnY = h->posY = 200;
	//AddObject(h);
	//auto *h2 = new Holder(4);
	//h2->spawnX = h2->posX = 136;
	//h2->spawnY = h2->posY = 104;
	//AddObject(h2);
	//auto *h3 = new Holder(4);
	//h3->spawnX = h3->posX = 328;
	//h3->spawnY = h3->posY = 88;
	//AddObject(h3);
	//auto *h4 = new Holder(2);
	//h4->spawnX = h4->posX = 424;
	//h4->spawnY = h4->posY = 184;
	//AddObject(h4);
	//auto *h5 = new Holder(6);
	//h5->spawnX = h5->posX = 584;
	//h5->spawnY = h5->posY = 151;
	//h5->maxItem = 3;
	//AddObject(h5);
	//auto *h6 = new Holder(2);
	//h6->spawnX = h6->posX = 840;
	//h6->spawnY = h6->posY = 151;
	//AddObject(h6);
	//auto *h7 = new Holder(3);
	//h7->spawnX = h7->posX = 1096;
	//h7->spawnY = h7->posY = 88;
	//AddObject(h7);
	//auto *h8 = new Holder(5);
	//h8->spawnX = h8->posX = 1192;
	//h8->spawnY = h8->posY = 184;
	//AddObject(h8);
	//auto *h9 = new Holder(2);
	//h9->spawnX = h9->posX = 1416;
	//h9->spawnY = h9->posY = 104;
	//AddObject(h9);
	//auto *h10 = new Holder(5);
	//h10->spawnX = h10->posX = 1352;
	//h10->spawnY = h10->posY = 200;
	//AddObject(h10);
	//auto *h11 = new Holder(3);
	//h11->spawnX = h11->posX = 1608;
	//h11->spawnY = h11->posY = 88;
	//AddObject(h11);
	//auto *h12 = new Holder(6);
	//h12->spawnX = h12->posX = 1704;
	//h12->spawnY = h12->posY = 184;
	//AddObject(h12);



	//AddGround(new Platform(0, 47, 96, 16, 0));
	//AddGround(new Platform(160, 47, 1216, 16, 0));
	//AddGround(new Platform(1436, 47, 360, 16, 0));
	//AddGround(new Platform(1791, 64, 65, 32, 1));
	//AddGround(new Platform(1855, 49, 160, 49, 1));
	//AddGround(new Platform(1791, 180, 256, 50, 1));
	//AddGround(new Platform(48, 176, 48, 16, 0));
	//AddGround(new Platform(34, 288, 222, 16, 0));
	//AddGround(new Platform(290, 288, 222, 16, 0));
	//AddGround(new Platform(546, 288, 222, 16, 0));
	//AddGround(new Platform(802, 288, 222, 16, 0));
	//AddGround(new Platform(1058, 288, 222, 16, 0));
	//AddGround(new Platform(1314, 288, 222, 16, 0));
	//AddGround(new Platform(1568, 288, 224, 16, 0));
	//AddGround(new Platform(576, 128, 32, 16, 0));
	//AddGround(new Platform(624, 208, 32, 16, 0));
	//AddGround(new Platform(672, 128, 48, 16, 0));
	//AddGround(new Platform(928, 128, 48, 16, 0));
	//AddGround(new Platform(832, 128, 32, 16, 0));
	//AddGround(new Platform(880, 208, 32, 16, 0));
	//AddGround(new Platform(1328, 176, 48, 16, 0));
	//AddGround(new Platform(0, 32, 1790, 32, 2));
	//// WALL
	//AddWall(new Wall(1790, 60, 66, 63));
	//AddWall(new Wall(1766, 277, 28, 109));
	//AddWall(new Wall(2016, 173, 31, 173));

	//auto *e = EnemyManager::CreateEnemy(1);
	//e->posX = e->spawnX = 694;
	//e->posY = e->spawnY = 150;
	//e->typeAI = 0;
	//e->DetectSpawnY(this->GetColliableGrounds(e));
	//AddObject(e);

	//auto *e2 = EnemyManager::CreateEnemy(1);
	//e2->posX = e2->spawnX = 951;
	//e2->posY = e2->spawnY = 150;
	//e2->typeAI = 0;
	//e2->DetectSpawnY(this->GetColliableGrounds(e2));
	//AddObject(e2);

	//auto *e3 = EnemyManager::CreateEnemy(1);
	//e3->posX = e3->spawnX = 808;
	//e3->posY = e3->spawnY = 71;
	//e3->typeAI = 1;
	//e3->DetectSpawnY(this->GetColliableGrounds(e3));
	//AddObject(e3);

	//auto *e4 = EnemyManager::CreateEnemy(1);
	//e4->posX = e4->spawnX = 1114;
	//e4->posY = e4->spawnY = 318;
	//e4->typeAI = 1;
	//e4->DetectSpawnY(this->GetColliableGrounds(e4));
	//AddObject(e4);
	//auto soldier = (EnemyBlueSoldier*)e4;
	//soldier->activeDistance = -120;


	//auto *e5 = EnemyManager::CreateEnemy(3);
	//e5->posX = e5->spawnX = 403;
	//e5->posY = e5->spawnY = 72;
	//e5->typeAI = 0;
	//e5->DetectSpawnY(this->GetColliableGrounds(e5));
	//AddObject(e5);
	//auto *e6 = EnemyManager::CreateEnemy(3);
	//e6->posX = e6->spawnX = 589;
	//e6->posY = e6->spawnY = 72;
	//e6->typeAI = 0;
	//e6->DetectSpawnY(this->GetColliableGrounds(e6));
	//AddObject(e6);
	//auto *e7 = EnemyManager::CreateEnemy(3);
	//e7->posX = e7->spawnX = 1623;
	//e7->posY = e7->spawnY = 77;
	//e7->typeAI = 0;
	//e7->DetectSpawnY(this->GetColliableGrounds(e7));
	//AddObject(e7);
	//END

	//Add Ground & Boss Map2
	//BEGIN

	AddGround(new Platform(0, 32, 255, 32, 1));
	AddGround(new Platform(48, 128, 48, 16, 0));
	auto e = EnemyManager::CreateEnemy(5);
	e->spawnX = e->posX = 120;
	e->spawnY = e->posY = 150;
	AddObject(e);

	auto e1 = EnemyManager::CreateEnemy(6);
	e1->spawnX = e1->posX = 160;
	e1->spawnY = e1->posY = 80;
	e1->speed = -0.1;
	//e1->dy = e1->vy = 2.0f;
	AddObject(e1);
	//auto e = EnemyManager::CreateEnemy(4);
	//e->spawnX = e->posX = 190;
	//e->spawnY = e->posY = 220;
	//e->ChangeState(FALLING);
	//AddObject(e);

	//END
}
void Grid::AddGround(Platform *g)
{
	int LeftCell = g->rect.x / Cell::width;
	int RightCell = (g->rect.x + g->rect.width) / Cell::width;
	int TopCell = g->rect.y / Cell::height;
	int BottomCell = (g->rect.y - g->rect.height) / Cell::height;
	for (int y = BottomCell; y <= TopCell; ++y)
	{
		for (int x = LeftCell; x <= RightCell; ++x)
		{
			cells[y][x]->grounds.push_back(g);
		}
	}
}
void Grid::AddWall(Wall *w) {
	int LeftCell = w->rect.x / Cell::width;
	int RightCell = (w->rect.x + w->rect.width) / Cell::width;
	int TopCell = w->rect.y / Cell::height;
	int BottomCell = (w->rect.y - w->rect.height) / Cell::height;
	for (int y = BottomCell; y <= TopCell; ++y)
	{
		for (int x = LeftCell; x <= RightCell; ++x)
		{
			cells[y][x]->walls.push_back(w);
		}
	}
}
Grid::~Grid()
{
	std::unordered_set<Object*> objs;
	std::unordered_set<Wall*> walls;
	std::unordered_set<Platform*> grounds;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			for (auto o : cells[i][j]->objects)
			{
				objs.insert(o);
			}

			for (auto w : cells[i][j]->walls)
			{
				walls.insert(w);
			}

			for (auto g : cells[i][j]->grounds)
			{
				grounds.insert(g);
			}

			cells[i][j]->objects.clear();
			cells[i][j]->walls.clear();
			cells[i][j]->grounds.clear();
			delete cells[i][j];
		}
		cells[i].clear();
	}
	cells.clear();

	for (auto o : objs)
	{
		o = nullptr;
	}

	for (auto g : grounds)
	{
		delete g;
	}

	for (auto w : walls)
	{
		delete w;
	}
}

void Grid::Update()
{
	this->viewPort = Rect(mCamera->x, mCamera->y, mCamera->width, mCamera->height);
	this->UpdateVisibleCells();
	this->RespawnEnemies();
}

void Grid::RespawnEnemies()
{
	auto it = respawnObjects.begin();
	while (it != respawnObjects.end())
	{
		auto o = *it;
		if (o->tag == ENEMY)
		{
			auto e = (Enemy*)o;
			if (!e->GetSpawnRect().isContain(viewPort))
			{
				e->ChangeState(STANDING);
				it = respawnObjects.erase(it);
				this->MoveObject(e, e->spawnX, e->spawnY);
				continue;
			}
		}
		++it;
	}
}

void Grid::MoveObject(Object * obj, float posX, float posY)
{
	if (obj->tag == ENEMY)
	{
		auto e = (Enemy*)obj;
		if (e->isOutScreen)
		{
			return;
		}
	}

	auto r = obj->GetRect();
	int oldLeftCell = r.x / Cell::width;
	int oldRightCell = (r.x + r.width) / Cell::width;
	int oldTopCell = r.y / Cell::height;
	int oldBottomCell = (r.y - r.height) / Cell::height;

	obj->posX = posX;
	obj->posY = posY;

	r = obj->GetRect();
	int LeftCell = r.x / Cell::width;
	int RightCell = (r.x + r.width) / Cell::width;
	int TopCell = r.y / Cell::height;
	int BottomCell = (r.y - r.height) / Cell::height;

	if (!(oldLeftCell < 0 || oldRightCell >= columns || oldTopCell >= rows || oldBottomCell < 0))
	{
		if (LeftCell < oldLeftCell)
		{
			if (oldTopCell < rows)
			{
				cells[oldTopCell][oldLeftCell]->RemoveObject(obj);
			}

			if (oldTopCell != oldBottomCell && oldBottomCell >= 0)
			{
				cells[oldBottomCell][oldLeftCell]->RemoveObject(obj);
			}
		}

		if (RightCell > oldRightCell)
		{
			if (oldTopCell < rows)
			{
				cells[oldTopCell][oldRightCell]->RemoveObject(obj);
			}

			if (oldTopCell != oldBottomCell && oldBottomCell >= 0)
			{
				cells[oldBottomCell][oldRightCell]->RemoveObject(obj);
			}
		}

		if (TopCell < oldTopCell)
		{
			if (oldLeftCell >= 0)
			{
				cells[oldTopCell][oldLeftCell]->RemoveObject(obj);
			}

			if (oldLeftCell != oldRightCell && oldRightCell < columns)
			{
				cells[oldTopCell][oldRightCell]->RemoveObject(obj);
			}
		}

		if (BottomCell > oldBottomCell)
		{
			if (oldLeftCell >= 0)
			{
				cells[oldBottomCell][oldLeftCell]->RemoveObject(obj);
			}

			if (oldLeftCell != oldRightCell && oldRightCell < columns)
			{
				cells[oldBottomCell][oldRightCell]->RemoveObject(obj);
			}
		}

		if (TopCell < rows)
		{
			if (LeftCell >= 0)
			{
				cells[TopCell][LeftCell]->objects.insert(obj);
			}

			if (LeftCell != RightCell && RightCell < columns)
			{
				cells[TopCell][RightCell]->objects.insert(obj);
			}
		}

		if (BottomCell < rows)
		{
			if (LeftCell >= 0)
			{
				cells[BottomCell][LeftCell]->objects.insert(obj);
			}

			if (LeftCell != RightCell && RightCell < columns)
			{
				cells[BottomCell][RightCell]->objects.insert(obj);
			}
		}
	}
}

void Grid::RemoveObject(Object * obj)
{
	auto r = obj->GetRect();
	int LeftCell = r.x / Cell::width;
	int RightCell = (r.x + r.width) / Cell::width;
	int TopCell = r.y / Cell::height;
	int BottomCell = (r.y - r.height) / Cell::height;

	for (int y = BottomCell; y <= TopCell; ++y)
	{
		if (y < 0 || y >= rows) continue;
		for (int x = LeftCell; x <= RightCell; ++x)
		{
			if (x < 0 || x >= columns) continue;
			else cells[y][x]->RemoveObject(obj);
		}
	}
}

void Grid::UpdateVisibleCells()
{
	visibleCells.clear();
	int left = viewPort.x / Cell::width;
	int right = ceil(viewPort.x / Cell::width) + 2;
	//int bottom = viewPort.y / Cell::height;
	//int top = floor(viewPort.y + viewPort.height) / Cell::height);

	for (int r = 0; r < rows; ++r)
	{
		for (int c = left; c < right; ++c)
		{
			visibleCells.push_back(cells[r][c]);
		}
	}
}

std::unordered_set<Object*> Grid::GetVisibleObjects()
{
	std::unordered_set<Object*> setObjects;

	for (auto c : visibleCells)
	{
		auto it = c->objects.begin();
		while (it != c->objects.end())
		{
			auto o = *it;
			if (o->IsCollide(viewPort))
			{
				switch (o->tag)
				{
				case ENEMY:
				{
					auto e = (Enemy*)o;
					if (e->isDead)
					{
						if (e->type != MINITANK)
						{
							it = c->objects.erase(it);
							respawnObjects.insert(e);
						}
						else if (e->type == MINITANK)
						{
							//e->isDead = false;
							respawnObjects.insert(e);
							setObjects.insert(e);
						}
						continue;
					}
					else if (!(e->isActive || e->isOutScreen))
					{
						if (e->type == BLUESOLDIER && e->typeAI == 0)
						{
							e->ChangeState(SITTING);
						}
						else if (e->type == ELECTRICBAT)
						{
							e->ChangeState(ACTIVE);
						}
						else if (e->type == SPLITTING_PLATFORM || e->type == MOVING_PLATFORM) {
							e->ChangeState(STANDING);
						}
						else if (e->type == BOSS2) {
							e->ChangeState(FALLING);
						}
						else if (e->type == BOSS1) {
							e->ChangeState(WAITING_TO_SPAWN);
						}
						else 
						{
							e->ChangeState(RUNNING);
						}
						/*e->DetectSpawnY(this->GetColliableGrounds(e));*/
						e->isReverse = !(player->posX < e->posX);
						e->vx = (e->isReverse ? e->speed : -e->speed);
					
					}

					if (e->isActive)
					{
						setObjects.insert(e);
					}
					break;
				}
				case HOLDER:
				{
					auto h = (Holder*)o;
					if (h->isAttacked)
					{
						h->isAttacked = false;
						if (h->maxItem > 0 && h->isCanDrop) {
							auto i = ItemManager::CreateItem(h->itemID);
							i->posX = h->posX;
							i->posY = h->posY + 10;
							i->DetectGround(this->GetVisibleGrounds());
							setObjects.insert(i);
							this->AddObject(i);
							h->maxItem--;
							h->isCanDrop = false;
						}
						setObjects.insert(h);
						++it;
						continue;
					}
					else setObjects.insert(o);
					break;
				}

				case ITEM: case BULLET:
				{
					if (o->isDead)
					{
						it = c->objects.erase(it);
						this->RemoveObject(o);
						delete o;
						continue;
					}
					else setObjects.insert(o);
					break;
				}
				}
			}

			else //Object is out of camera
			{
				switch (o->tag)
				{
				case ENEMY:
				{
					auto e = (Enemy*)o;
					if (e->isActive && e->type != MOVING_PLATFORM && e->type != MINITANK)
					{
						e->isActive = false;
						it = c->objects.erase(it);
						if (e->GetSpawnRect().isContain(viewPort))
						{
							e->isOutScreen = true;
							respawnObjects.insert(e);
						}
						else
						{
							this->MoveObject(e, e->spawnX, e->spawnY);
						}
						continue;
					}
					else if (e->type == MOVING_PLATFORM) {
						auto movingPlatform = (MovingPlatform*)e;
						setObjects.insert(movingPlatform);
					}
					break;
				}
				case ITEM: case BULLET:
				{
					it = c->objects.erase(it);
					this->RemoveObject(o);
					delete o;
					continue;
					break;
				}
				}
			}
			++it;
		}
	}
	return setObjects;
}

std::unordered_set<Wall*> Grid::GetColliableWalls(Object * obj)
{
	std::unordered_set<Wall*> walls;

	auto r = obj->GetRect();
	int LeftCell = r.x / Cell::width;
	int RightCell = (r.x + r.width) / Cell::width;
	int TopCell = r.y / Cell::height;
	int BottomCell = (r.y - r.height) / Cell::height;

	for (int y = BottomCell; y <= TopCell; ++y)
	{
		if (y < 0 || y >= rows) continue;
		for (int x = LeftCell; x <= RightCell; ++x)
		{
			if (x < 0 || x >= columns) continue;
			for (auto w : cells[y][x]->walls)
			{
				walls.insert(w);
			}
		}
	}
	return walls;
}

std::unordered_set<Platform*> Grid::GetColliableGrounds(Object * obj)
{
	std::unordered_set<Platform*> grounds;

	auto r = obj->GetRect();
	int LeftCell = r.x / Cell::width;
	int RightCell = (r.x + r.width) / Cell::width;
	int TopCell = r.y / Cell::height;
	int BottomCell = (r.y - r.height) / Cell::height;

	for (int y = BottomCell; y <= TopCell; ++y)
	{
		if (y < 0 || y >= rows) continue;
		for (int x = LeftCell; x <= RightCell; ++x)
		{
			if (x < 0 || x >= columns) continue;
			for (auto g : cells[y][x]->grounds)
			{
				grounds.insert(g);
			}
		}
	}
	return grounds;
}

std::unordered_set<Object*> Grid::GetColliableObjects(Object * obj)
{
	std::unordered_set<Object*> objs;

	auto r = obj->GetRect();
	int LeftCell = r.x / Cell::width;
	int RightCell = (r.x + r.width) / Cell::width;
	int TopCell = r.y / Cell::height;
	int BottomCell = (r.y - r.height) / Cell::height;

	for (int y = BottomCell; y <= TopCell; ++y)
	{
		if (y < 0 || y >= rows) continue;
		for (int x = LeftCell; x <= RightCell; ++x)
		{
			if (x < 0 || x >= columns) continue;
			for (auto o : cells[y][x]->objects)
			{
				switch (o->tag)
				{
				case ENEMY:
				{
					auto e = (Enemy*)o;
					if (e->isActive && e->stateName != DEAD)
					{
						objs.insert(e);
					}
					break;
				}
				case BULLET:
				{
					auto b = (Bullet*)o;
					if (b->StateName != DEAD)
					{
						objs.insert(b);
					}
					break;
				}
				default:
				{
					objs.insert(o);
					break;
				}
				}
			}
		}
	}
	return objs;
}

void Grid::AddObject(Object * obj)
{
	if (obj == NULL) return;

	auto r = obj->GetRect();
	int LeftCell = r.x / Cell::width;
	int RightCell = (r.x + r.width) / Cell::width;
	int TopCell = r.y / Cell::height;
	int BottomCell = (r.y - r.height) / Cell::height;

	for (int y = BottomCell; y <= TopCell; ++y)
	{
		for (int x = LeftCell; x <= RightCell; ++x)
		{
			cells[y][x]->objects.insert(obj);
		}
	}
}

std::unordered_set<Wall*> Grid::GetVisibleWalls()
{
	std::unordered_set<Wall*> setWalls;

	for (auto c : visibleCells)
	{
		for (auto w : c->walls)
		{
			if (w->rect.isContain(viewPort))
			{
				setWalls.insert(w);
			}
		}
	}
	return setWalls;
}

std::unordered_set<Platform*> Grid::GetVisibleGrounds()
{
	std::unordered_set<Platform*> setGrounds;

	for (auto c : visibleCells)
	{
		for (auto g : c->grounds)
		{
			if (g->rect.isContain(viewPort))
			{
				setGrounds.insert(g);
			}
		}
	}
	return setGrounds;
}