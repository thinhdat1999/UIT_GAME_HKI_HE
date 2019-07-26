#pragma once
#include <unordered_map>
#include "Sprite.h"
#include "PlayerSprite.h"
#include "WeaponSprite.h"
#include "EnemySprite.h"
#include "ItemSprite.h"
class SpriteManager : CSprite
{
private:
	unordered_map<Tag, vector<CSprite*>> _sprites;
	static SpriteManager *_instance;
public:
	void StartUp();
	void ShutDown();

	void AddSprite(CSprite* sprite);
	static SpriteManager * GetInstance();
	CSprite* GetSprite(Tag tag, int index);
	vector<CSprite*> GetSprites(Tag tag, int firstIndex, int lastIndex);
};