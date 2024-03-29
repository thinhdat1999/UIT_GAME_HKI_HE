﻿#include "SpriteManager.h"

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
	sprites->AddSprite(new PlayerSprite(SITTING, 205, 26, 236, 56));
	sprites->AddSprite(new PlayerSprite(JUMPING, 238, 10, 266, 56));
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
	sprites->AddSprite(new PlayerSprite(INJURED, 201, 186, 233, 232));			//23
	//sprites->AddSprite(new PlayerSprite(INJURED, 84, 186, 116, 232));			//24
	sprites->AddSprite(new PlayerSprite(ONWATER, 261, 244, 281, 260));			//24
	sprites->AddSprite(new PlayerSprite(WATER_RUNNING, 292, 243, 312, 259));	//25
	sprites->AddSprite(new PlayerSprite(WATER_FALLING, 118, 243, 138, 259));	//26
	sprites->AddSprite(new PlayerSprite(WATER_FALLING, 142, 243, 162, 259));	//27
	sprites->AddSprite(new PlayerSprite(WATER_FALLING, 166, 243, 186, 259));	//28
	sprites->AddSprite(new PlayerSprite(WATER_DIVING, 98, 243, 118, 259));		//29
	sprites->AddSprite(new PlayerSprite(WATER_DIVING, 81, 243, 101, 259));		//30
	sprites->AddSprite(new PlayerSprite(INWATER, 186, 236, 206, 252));			//31
	sprites->AddSprite(new PlayerSprite(INWATER, 206, 236, 226, 252));			//32
	sprites->AddSprite(new PlayerSprite(INWATER, 230, 236, 250, 252));			//33

	sprites->AddSprite(new PlayerSprite(SCOREBOARD, 215, 307, 225, 317));		//34 HEALTH
	sprites->AddSprite(new PlayerSprite(SCOREBOARD, 279, 302, 310, 322));		//35 EXIT
	sprites->AddSprite(new PlayerSprite(DEAD, 240, 186, 274, 233));				//36
	sprites->AddSprite(new PlayerSprite(DEAD, 282, 186, 326, 233));				//37
	sprites->AddSprite(new PlayerSprite(CLINGING, 291, 119, 313, 177));			//38
	sprites->AddSprite(new PlayerSprite(CLINGING, 323, 119, 345, 177));
	sprites->AddSprite(new PlayerSprite(CLINGING, 347, 119, 369, 177));			//40
	sprites->AddSprite(new PlayerSprite(JUMPONWALL, 247, 124, 279, 170));


	//Load Weapon
	sprites->AddSprite(new WeaponSprite(SHIELD, 90, 271, 116, 289));
	sprites->AddSprite(new WeaponSprite(SHIELD, 110, 271, 136, 289));
	sprites->AddSprite(new WeaponSprite(SHIELD, 135, 271, 161, 289));
	sprites->AddSprite(new WeaponSprite(SHIELD, 163, 279, 189, 289));

	//Load Holder
	sprites->AddSprite(new HolderSprite(STANDING, 44, 224, 60, 240));
	sprites->AddSprite(new HolderSprite(ACTIVE, 132, 205, 148, 221));

	//Load Item
	sprites->AddSprite(new ItemSprite(FIVEPOINT, 167, 305, 177, 321));			//0
	sprites->AddSprite(new ItemSprite(ENERGY, 180, 310, 196, 322));				//1
	sprites->AddSprite(new ItemSprite(ENERGYX10, 196, 309, 212, 321));			//2
	sprites->AddSprite(new ItemSprite(POWERSTONE, 87, 305, 97, 321));			//3
	sprites->AddSprite(new ItemSprite(POWERSTONE, 103, 305, 113, 321));			//4
	sprites->AddSprite(new ItemSprite(POWERSTONEX10, 121, 303, 136, 321));		//5
	sprites->AddSprite(new ItemSprite(POWERSTONEX10, 145, 303, 160, 321));		//6
	sprites->AddSprite(new ItemSprite(KEY, 232, 304, 248, 320));				//7
	sprites->AddSprite(new ItemSprite(KEY, 256, 304, 272, 320));				//8

	//ENEMY
	//Load Boss1
	sprites->AddSprite(new EnemySprite(BOSS1, 5, 12, 37, 64));					//0   STANDING
	sprites->AddSprite(new EnemySprite(BOSS1, 37, 12, 69, 64));					//1	  RUNNING
	sprites->AddSprite(new EnemySprite(BOSS1, 72, 12, 104, 64));				//2	  RUNNING
	sprites->AddSprite(new EnemySprite(BOSS1, 105, 12, 137, 64));				//3	  RUNNING
	sprites->AddSprite(new EnemySprite(BOSS1, 137, 12, 169, 64));				//4   RUNNING
	sprites->AddSprite(new EnemySprite(BOSS1, 174, 12, 206, 64));				//5   INJURED
	sprites->AddSprite(new EnemySprite(BOSS1, 219, 32, 255, 66));				//6   DEAD
	sprites->AddSprite(new EnemySprite(BOSS1, 268, 32, 304, 66));				//7   DEAD
	sprites->AddSprite(new EnemySprite(BOSS1, 16, 68, 56, 120));				//8   ATTACKING
	sprites->AddSprite(new EnemySprite(BOSS1, 64, 68, 104, 120));				//9	  ATTACKING
	sprites->AddSprite(new EnemySprite(BOSS1, 112, 68, 152, 120));				//10  ATTACKING
	sprites->AddSprite(new EnemySprite(BOSS1, 152, 68, 192, 120));				//11  ATTACKING (SHOOT)
	sprites->AddSprite(new EnemySprite(BOSS1, 47, 129, 77, 181));				//12  JUMPING
	sprites->AddSprite(new EnemySprite(BOSS1, 87, 129, 117, 181));				//13  FALLING
	sprites->AddSprite(new EnemySprite(BOSS1, 127, 129, 157, 181));				//14  ATTACKING (JUMP)
	sprites->AddSprite(new EnemySprite(BOSS1, 167, 129, 197, 181));				//15  ATTACKING (JUMP)
	//Bullet
	//Horizontal
	sprites->AddSprite(new BulletSprite(BOSS1, 244, 159, 260, 171));			//0	SMALL BULLET
	sprites->AddSprite(new BulletSprite(BOSS1, 208, 138, 224, 150));			//1	BIG BULLET
	//Vertical		
	sprites->AddSprite(new BulletSprite(BOSS1, 251, 136, 267, 152));			//2    BIG BULLET

	//Load Boss2
	sprites->AddSprite(new EnemySprite(BOSS2, 239, 24, 271, 72));			//16	STANDING
	sprites->AddSprite(new EnemySprite(BOSS2, 359, 24, 391, 72));			//17	INJURED
	sprites->AddSprite(new EnemySprite(BOSS2, 7, 24, 39, 72));				//18	RUNNING
	sprites->AddSprite(new EnemySprite(BOSS2, 47, 24, 79, 72));				//19	RUNNING
	sprites->AddSprite(new EnemySprite(BOSS2, 87, 24, 119, 72));			//20	RUNNING
	sprites->AddSprite(new EnemySprite(BOSS2, 128, 24, 160, 72));			//21	FALLING
	sprites->AddSprite(new EnemySprite(BOSS2, 429, 24, 461, 72));			//22	HOLDING BARREL
	sprites->AddSprite(new EnemySprite(BOSS2, 320, 24, 352, 72));			//23	THROWING BARREL
	sprites->AddSprite(new EnemySprite(BOSS2, 168, 24, 206, 72));			//24	SHOOTING
	//Dạng 2
	sprites->AddSprite(new EnemySprite(BOSS2, 93, 80, 129, 128));			//25	STANDING, DEAD
	sprites->AddSprite(new EnemySprite(BOSS2, 134, 80, 170, 128));			//26	RUNNING
	sprites->AddSprite(new EnemySprite(BOSS2, 178, 80, 214, 128));			//27	RUNNING
	sprites->AddSprite(new EnemySprite(BOSS2, 222, 80, 258, 128));			//28	RUNNING
	//Bullet width 16, height 14
	sprites->AddSprite(new BulletSprite(BOSS2, 216, 39, 232, 53));			//3	
	//Barrel, width 22, height 14
	sprites->AddSprite(new BulletSprite(BOSS2, 402, 42, 424, 56));			//4   
	//BlueSoldier
	sprites->AddSprite(new EnemySprite(BLUESOLDIER, 71, 13, 97, 56));				//29 RUNNING
	sprites->AddSprite(new EnemySprite(BLUESOLDIER, 102, 13, 128, 56));				//30 RUNNING
	sprites->AddSprite(new EnemySprite(BLUESOLDIER, 135, 13, 161, 56));				//31 RUNNING
	sprites->AddSprite(new EnemySprite(BLUESOLDIER, 167, 13, 193, 56));				//32 SHOOT(STAND)
	sprites->AddSprite(new EnemySprite(BLUESOLDIER, 199, 28, 225, 56));				//33 SITTING
	sprites->AddSprite(new EnemySprite(BLUESOLDIER, 231, 13, 257, 56));				//34 INJURED
		//Bullet
	sprites->AddSprite(new BulletSprite(BLUESOLDIER, 264, 33, 272, 39));			//5

	//OrangeSoldier
	sprites->AddSprite(new EnemySprite(ROCKETSOLDIER, 72, 66, 96, 112));			//35 RUNNING
	sprites->AddSprite(new EnemySprite(ROCKETSOLDIER, 104, 66, 128, 112));			//36 RUNNING
	sprites->AddSprite(new EnemySprite(ROCKETSOLDIER, 136, 66, 160, 112));			//37 RUNNING
	sprites->AddSprite(new EnemySprite(ROCKETSOLDIER, 168, 80, 192, 112));			//38 SITTING
	sprites->AddSprite(new EnemySprite(ROCKETSOLDIER, 200, 66, 224, 112));			//39 INJURED
	//Bullet
	sprites->AddSprite(new BulletSprite(ROCKETSOLDIER, 231, 71, 248, 82));			//6
	sprites->AddSprite(new BulletSprite(ROCKETSOLDIER, 254, 71, 270, 82));			//7
	sprites->AddSprite(new BulletSprite(ROCKETSOLDIER, 233, 96, 249, 112));			//8
	sprites->AddSprite(new BulletSprite(ROCKETSOLDIER, 259, 96, 275, 112));			//9
	sprites->AddSprite(new BulletSprite(ROCKETSOLDIER, 235, 82, 246, 84));			//10
	sprites->AddSprite(new BulletSprite(ROCKETSOLDIER, 259, 81, 273, 96));			//11
	sprites->AddSprite(new BulletSprite(ROCKETSOLDIER, 374, 68, 383, 86));			//12
	sprites->AddSprite(new BulletSprite(ROCKETSOLDIER, 374, 92, 383, 109));			//13
	sprites->AddSprite(new BulletSprite(ROCKETSOLDIER, 386, 89, 397, 107));			//14
	sprites->AddSprite(new BulletSprite(ROCKETSOLDIER, 386, 67, 397, 85));			//15

	//FLyingOrangeSoldier
	sprites->AddSprite(new EnemySprite(FLYINGROCKET, 35, 129, 61, 168));			//40
	sprites->AddSprite(new EnemySprite(FLYINGROCKET, 291, 129, 321, 168));			//41
	sprites->AddSprite(new EnemySprite(FLYINGROCKET, 67, 129, 93, 168));			//42
	sprites->AddSprite(new EnemySprite(FLYINGROCKET, 331, 129, 361, 168));			//43
	sprites->AddSprite(new EnemySprite(FLYINGROCKET, 99, 129, 125, 168));			//44
	sprites->AddSprite(new EnemySprite(FLYINGROCKET, 371, 129, 401, 168));			//45

	//MiniTank
	sprites->AddSprite(new EnemySprite(MINITANK, 236, 343, 252, 360));			//46
	sprites->AddSprite(new EnemySprite(MINITANK, 284, 343, 300, 360));			//47
	sprites->AddSprite(new EnemySprite(MINITANK, 332, 343, 348, 360));			//48
	sprites->AddSprite(new EnemySprite(MINITANK, 284, 343, 300, 360));			//49
	sprites->AddSprite(new EnemySprite(MINITANK, 260, 343, 276, 360));			//50
	sprites->AddSprite(new EnemySprite(MINITANK, 308, 343, 324, 360));			//51
	//ElectricBat
	//Idle1
	sprites->AddSprite(new EnemySprite(ELECTRICBAT, 114, 222, 126, 241));			//52
	//Idle2
	sprites->AddSprite(new EnemySprite(ELECTRICBAT, 43, 222, 61, 241));				//53
	//Active1
	sprites->AddSprite(new EnemySprite(ELECTRICBAT, 132, 222, 157, 241));			//54
	sprites->AddSprite(new EnemySprite(ELECTRICBAT, 164, 222, 189, 241));			//55
	//Active2
	sprites->AddSprite(new EnemySprite(ELECTRICBAT, 67, 222, 85, 241));				//56
	sprites->AddSprite(new EnemySprite(ELECTRICBAT, 91, 222, 109, 241));			//57

	sprites->AddSprite(new EnemySprite(ELECTRICBAT, 195, 222, 211, 243));			//58
	sprites->AddSprite(new EnemySprite(ELECTRICBAT, 226, 222, 252, 243));			//59
	sprites->AddSprite(new EnemySprite(ELECTRICBAT, 260, 222, 300, 243));			//60

	//Splitting Platform
	sprites->AddSprite(new EnemySprite(SPLITTING_PLATFORM, 256, 368, 288, 384));	//IDLE		61
	sprites->AddSprite(new EnemySprite(SPLITTING_PLATFORM, 232, 368, 248, 384));	//ACTIVE	62

	sprites->AddSprite(new EnemySprite(MOVING_PLATFORM, 296, 368, 328, 384));		//IDLE		63
	//Nitro
	sprites->AddSprite(new BulletSprite(MOVING_PLATFORM, 336, 367, 344, 379));		//Nitro vertical	16 
	sprites->AddSprite(new BulletSprite(MOVING_PLATFORM, 351, 371, 361, 381));		//Nitro horizontal	17

	// BOSS1
	sprites->AddSprite(new BulletSprite(BOSS1, 228, 159, 244, 171));		//18
	sprites->AddSprite(new BulletSprite(BOSS1, 213, 159, 229, 171));		//19
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
