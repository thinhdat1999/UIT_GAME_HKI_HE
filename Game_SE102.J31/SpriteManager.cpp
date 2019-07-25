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
	sprites->AddSprite(new PlayerSprite(STANDING, 20, 10, 43, 58));
	sprites->AddSprite(new PlayerSprite(RUNNING, 52, 10, 77, 58));
	sprites->AddSprite(new PlayerSprite(RUNNING, 84, 10, 109, 58));
	sprites->AddSprite(new PlayerSprite(RUNNING, 116, 10, 140, 58));
	sprites->AddSprite(new PlayerSprite(RUNNING, 147, 10, 172, 58));
	sprites->AddSprite(new PlayerSprite(SHIELD_UP, 179, 10, 205, 58));
	sprites->AddSprite(new PlayerSprite(SITTING, 204, 26, 236, 56));
	sprites->AddSprite(new PlayerSprite(JUMPING, 242, 10, 267, 58));
	sprites->AddSprite(new PlayerSprite(SPINNING, 274, 27, 296, 51));
	sprites->AddSprite(new PlayerSprite(SPINNING, 311, 27, 333, 51));
	sprites->AddSprite(new PlayerSprite(ATTACKING_JUMP, 338, 22, 382, 50));
	sprites->AddSprite(new PlayerSprite(THROWING, 8, 73, 45, 113));
	sprites->AddSprite(new PlayerSprite(THROWING, 56, 73, 97, 113));
	sprites->AddSprite(new PlayerSprite(ATTACKING_STAND, 104, 70, 145, 113));
	sprites->AddSprite(new PlayerSprite(ATTACKING_STAND, 153, 70, 185, 113));
	sprites->AddSprite(new PlayerSprite(ATTACKING_SIT, 194, 82, 232, 112));
	sprites->AddSprite(new PlayerSprite(ATTACKING_SIT, 234, 82, 272, 112));
	sprites->AddSprite(new PlayerSprite(DASHING, 279, 83, 314, 113));
	sprites->AddSprite(new PlayerSprite(DASHING, 320, 83, 362, 113));
	sprites->AddSprite(new PlayerSprite(SHIELD_DOWN, 368, 83, 392, 113));

	//Load Weapon
	sprites->AddSprite(new WeaponSprite(SHIELD, 99, 271, 108, 289));
	sprites->AddSprite(new WeaponSprite(SHIELD, 115, 271, 132, 289));
	sprites->AddSprite(new WeaponSprite(SHIELD, 140, 271, 157, 289));
	sprites->AddSprite(new WeaponSprite(SHIELD, 164, 279, 189, 289));

	//Load Item
	sprites->AddSprite(new ItemSprite(FIVEPOINT, 167, 305, 177, 321));
	sprites->AddSprite(new ItemSprite(ENERGY, 184, 310, 193, 321));
	sprites->AddSprite(new ItemSprite(POWERSTONE, 87, 305, 97, 321));
	sprites->AddSprite(new ItemSprite(POWERSTONEX10, 121, 303, 136, 321));
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
