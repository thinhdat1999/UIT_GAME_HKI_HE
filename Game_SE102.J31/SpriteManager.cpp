#include "SpriteManager.h"

SpriteManager * SpriteManager::_instance = NULL;

SpriteManager *SpriteManager::GetInstance()
{
	if (_instance == NULL) _instance = new SpriteManager();
	return _instance;
}

void SpriteManager::StartUp()
{
	auto sprites = SpriteManager::GetInstance();
	//Load Sprites
	sprites->AddSprite(new PlayerSprite(STANDING, 16, 10, 48, 56));
	sprites->AddSprite(new PlayerSprite(RUNNING, 52, 10, 77, 56));
	sprites->AddSprite(new PlayerSprite(RUNNING, 84, 10, 109, 56));
	sprites->AddSprite(new PlayerSprite(RUNNING, 116, 10, 140, 56));
	sprites->AddSprite(new PlayerSprite(RUNNING, 147, 10, 172, 56));
	sprites->AddSprite(new PlayerSprite(SHIELD_UP, 179, 10, 205, 56));
	sprites->AddSprite(new PlayerSprite(SITTING, 204, 26, 236, 56));
	sprites->AddSprite(new PlayerSprite(JUMPING, 236, 10, 267, 56));
	sprites->AddSprite(new PlayerSprite(SPINNING, 274, 27, 296, 51));
	sprites->AddSprite(new PlayerSprite(SPINNING, 311, 27, 333, 51));
	sprites->AddSprite(new PlayerSprite(ATTACKING_JUMP, 338, 22, 382, 50));
	sprites->AddSprite(new PlayerSprite(THROWING, 3, 66, 43, 112));
	sprites->AddSprite(new PlayerSprite(THROWING, 57, 66, 99, 112));
	sprites->AddSprite(new PlayerSprite(ATTACKING_STAND, 105, 66, 147, 112));
	sprites->AddSprite(new PlayerSprite(ATTACKING_STAND, 145, 66, 187, 112));
	sprites->AddSprite(new PlayerSprite(ATTACKING_SIT, 193, 82, 239, 112));
	sprites->AddSprite(new PlayerSprite(ATTACKING_SIT, 233, 82, 279, 112));
	sprites->AddSprite(new PlayerSprite(DASHING, 279, 83, 314, 113));
	sprites->AddSprite(new PlayerSprite(DASHING, 320, 83, 362, 113));
	sprites->AddSprite(new PlayerSprite(SHIELD_DOWN, 368, 83, 392, 113));
	sprites->AddSprite(new PlayerSprite(EXPLODED, 227, 265, 237, 295));			//20
	sprites->AddSprite(new PlayerSprite(EXPLODED, 237, 265, 267, 295));			//21
	sprites->AddSprite(new PlayerSprite(EXPLODED, 269, 265, 299, 295));			//22

	//Load Weapon
	sprites->AddSprite(new WeaponSprite(SHIELD, 90, 271, 116, 289));
	sprites->AddSprite(new WeaponSprite(SHIELD, 110, 271, 136, 289));
	sprites->AddSprite(new WeaponSprite(SHIELD, 135, 271, 161, 289));
	sprites->AddSprite(new WeaponSprite(SHIELD, 163, 279, 189, 289));

	//Load Item
	sprites->AddSprite(new ItemSprite(FIVEPOINT, 167, 305, 177, 321));
	sprites->AddSprite(new ItemSprite(ENERGY, 184, 310, 193, 321));
	sprites->AddSprite(new ItemSprite(POWERSTONE, 87, 305, 97, 321));
	sprites->AddSprite(new ItemSprite(POWERSTONEX10, 121, 303, 136, 321));

	//ENEMY
	//Load Boss1
	sprites->AddSprite(new EnemySprite(BOSS1, 10, 15, 32, 64));				//0
	sprites->AddSprite(new EnemySprite(BOSS1, 42, 15, 64, 64));				//1
	sprites->AddSprite(new EnemySprite(BOSS1, 73, 15, 104, 64));				//2
	sprites->AddSprite(new EnemySprite(BOSS1, 112, 15, 128, 64));				//3
	sprites->AddSprite(new EnemySprite(BOSS1, 139, 15, 168, 64));				//4
	sprites->AddSprite(new EnemySprite(BOSS1, 176, 15, 205, 64));				//5
	sprites->AddSprite(new EnemySprite(BOSS1, 48, 130, 77, 181));				//6
	sprites->AddSprite(new EnemySprite(BOSS1, 88, 130, 107, 181));		//7
	sprites->AddSprite(new EnemySprite(BOSS1, 220, 37, 253, 64));				//8
	sprites->AddSprite(new EnemySprite(BOSS1, 267, 37, 303, 64));				//9
	sprites->AddSprite(new EnemySprite(BOSS1, 128, 130, 157, 181));		//10
	sprites->AddSprite(new EnemySprite(BOSS1, 32, 74, 56, 120));		//11
	sprites->AddSprite(new EnemySprite(BOSS1, 66, 74, 104, 120));		//12
	sprites->AddSprite(new EnemySprite(BOSS1, 111, 74, 153, 121));	//13
	sprites->AddSprite(new EnemySprite(BOSS1, 160, 74, 193, 121));	//14
			//Bullet
				//Horizontal
	sprites->AddSprite(new EnemySprite(BOSS1, 247, 161, 257, 168));			//15
	sprites->AddSprite(new EnemySprite(BOSS1, 207, 139, 225, 150));			//16
	//Vertical		
	sprites->AddSprite(new EnemySprite(BOSS1, 254, 135, 265, 154));			//17

	//Load Boss2
	sprites->AddSprite(new EnemySprite(BOSS2, 239, 28, 271, 73));			//18
	sprites->AddSprite(new EnemySprite(BOSS2, 7, 32, 39, 73));				//19
	sprites->AddSprite(new EnemySprite(BOSS2, 50, 32, 76, 73));				//20
	sprites->AddSprite(new EnemySprite(BOSS2, 90, 32, 118, 73));				//21
	sprites->AddSprite(new EnemySprite(BOSS2, 359, 23, 391, 73));				//22
	sprites->AddSprite(new EnemySprite(BOSS2, 129, 23, 157, 71));				//23
	sprites->AddSprite(new EnemySprite(BOSS2, 99, 87, 125, 129));			//24
	sprites->AddSprite(new EnemySprite(BOSS2, 279, 23, 307, 73));			//25
	sprites->AddSprite(new EnemySprite(BOSS2, 319, 23, 354, 73));			//26
	sprites->AddSprite(new EnemySprite(BOSS2, 166, 28, 207, 73));		//27
	sprites->AddSprite(new EnemySprite(BOSS2, 134, 87, 171, 129));			//28
	sprites->AddSprite(new EnemySprite(BOSS2, 179, 87, 214, 129));			//29
	sprites->AddSprite(new EnemySprite(BOSS2, 222, 87, 258, 129));			//30
	//Bullet
	sprites->AddSprite(new EnemySprite(BOSS2, 214, 40, 233, 53));			//31
	//Bin
	sprites->AddSprite(new EnemySprite(BOSS2, 401, 41, 425, 57));			//32
	//BlueSoldier
	sprites->AddSprite(new EnemySprite(BLUESOLDIER, 71, 13, 97, 55));				//33
	sprites->AddSprite(new EnemySprite(BLUESOLDIER, 103, 13, 129, 55));				//34
	sprites->AddSprite(new EnemySprite(BLUESOLDIER, 135, 13, 161, 55));				//35
	sprites->AddSprite(new EnemySprite(BLUESOLDIER, 199, 28, 225, 57));				//36
	sprites->AddSprite(new EnemySprite(BLUESOLDIER, 199, 28, 225, 57));				//37
	sprites->AddSprite(new EnemySprite(BLUESOLDIER, 167, 13, 193, 55));		//38
	sprites->AddSprite(new EnemySprite(BLUESOLDIER, 231, 13, 257, 55));				//39
	sprites->AddSprite(new EnemySprite(BLUESOLDIER, 279, 28, 305, 57));			//40
	sprites->AddSprite(new EnemySprite(BLUESOLDIER, 311, 28, 337, 57));			//41
	sprites->AddSprite(new EnemySprite(BLUESOLDIER, 343, 28, 369, 57));			//42
		//Bullet
	sprites->AddSprite(new EnemySprite(BLUESOLDIER, 264, 31, 274, 41));			//43

	//OrangeSoldier
	sprites->AddSprite(new EnemySprite(ORANGESOLDIER, 72, 65, 96, 113));
	sprites->AddSprite(new EnemySprite(ORANGESOLDIER, 104, 65, 128, 113));
	sprites->AddSprite(new EnemySprite(ORANGESOLDIER, 136, 65, 160, 113));
	sprites->AddSprite(new EnemySprite(ORANGESOLDIER, 167, 80, 193, 113));
	sprites->AddSprite(new EnemySprite(ORANGESOLDIER, 167, 80, 193, 113));
	sprites->AddSprite(new EnemySprite(ORANGESOLDIER, 200, 64, 224, 112));
	sprites->AddSprite(new EnemySprite(ORANGESOLDIER, 280, 65, 304, 113));
	sprites->AddSprite(new EnemySprite(ORANGESOLDIER, 312, 65, 336, 113));
	sprites->AddSprite(new EnemySprite(ORANGESOLDIER, 344, 65, 368, 113));
	//Bullet
	sprites->AddSprite(new EnemySprite(ORANGESOLDIER, 231, 71, 248, 82));
	sprites->AddSprite(new EnemySprite(ORANGESOLDIER, 255, 71, 728, 82));
	sprites->AddSprite(new EnemySprite(ORANGESOLDIER, 235, 95, 249, 110));
	sprites->AddSprite(new EnemySprite(ORANGESOLDIER, 259, 95, 273, 110));

	//FLyingOrangeSoldier
	sprites->AddSprite(new EnemySprite(FLYINGROCKET, 35, 129, 61, 168));
	sprites->AddSprite(new EnemySprite(FLYINGROCKET, 291, 129, 321, 168));
	sprites->AddSprite(new EnemySprite(FLYINGROCKET, 67, 129, 93, 168));
	sprites->AddSprite(new EnemySprite(FLYINGROCKET, 331, 129, 361, 168));
	sprites->AddSprite(new EnemySprite(FLYINGROCKET, 99, 129, 125, 168));
	sprites->AddSprite(new EnemySprite(FLYINGROCKET, 371, 129, 401, 168));

	//MiniTank
	sprites->AddSprite(new EnemySprite(MINITANK, 236, 343, 252, 360));
	sprites->AddSprite(new EnemySprite(MINITANK, 260, 343, 276, 360));
	sprites->AddSprite(new EnemySprite(MINITANK, 284, 343, 300, 360));
	sprites->AddSprite(new EnemySprite(MINITANK, 308, 343, 324, 360));
	sprites->AddSprite(new EnemySprite(MINITANK, 332, 343, 348, 360));
	////ElectricBat
	////Idle1
	//sprites->AddSprite(new EnemySprite(IDLE, 114, 222, 126, 241));
	////Idle2
	//sprites->AddSprite(new EnemySprite(IDLE, 43, 222, 61, 241));
	////Active1
	//sprites->AddSprite(new EnemySprite(ACTIVE, 132, 222, 157, 241));
	//sprites->AddSprite(new EnemySprite(ACTIVE, 164, 222, 189, 241));
	////Active2
	//sprites->AddSprite(new EnemySprite(ACTIVE, 67, 222, 85, 241));
	//sprites->AddSprite(new EnemySprite(ACTIVE, 91, 222, 109, 241));

	//sprites->AddSprite(new EnemySprite(ATTACKING, 195, 222, 211, 243));
	//sprites->AddSprite(new EnemySprite(ATTACKING, 226, 222, 252, 243));
	//sprites->AddSprite(new EnemySprite(ATTACKING, 260, 222, 300, 243));
}


CSprite* SpriteManager::GetSprite(Tag tag, int index)
{
	return _sprites[tag][index];
}

// Lấy các Sprite (dùng cho tạo Animation) theo Tag từ vị trí first->last
std::vector<CSprite*> SpriteManager::GetSprites(Tag tag, int firstIndex, int lastIndex)
{
	auto first = _sprites[tag].begin() + firstIndex;
	auto last = _sprites[tag].begin() + lastIndex;
	return std::vector<CSprite*>(first, last + 1);
}

void SpriteManager::AddSprite(CSprite* sprite)
{
	_sprites[sprite->tag].push_back(sprite);
}
