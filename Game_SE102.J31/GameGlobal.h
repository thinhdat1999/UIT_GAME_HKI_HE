#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <WinUser.h>
#include <unordered_map>

#define SCREEN_WIDTH 256			// Chiều dài cửa sổ
#define SCREEN_HEIGHT 224	// Chiều cao cửa sổ
#define MAX_FRAME_RATE 120				// FPS
#define WIN_NAME "Captain America and The Avengers"
#define WIN_TITLE "Captain America and The Avengers"
#define KEYBOARD_BUFFER_SIZE 1024
#define DEFAULT_TPF 120
#define TILE_SIZE 16
extern LPD3DXSPRITE spriteHandler; 
extern LPDIRECT3DDEVICE9 d3ddev;
extern LPDIRECT3DSURFACE9 backBuffer; // Back buffer
extern LPDIRECT3DSURFACE9 surface;
extern bool isGameRunning;
extern std::unordered_map<int, bool> keyCode;

#define mCamera Camera::GetInstance()
#define player Player::GetInstance()

// ===== CÁC THÔNG SỐ CHO HOLDERS & ITEM ====
#define HOLDER_WIDTH 16
#define HOLDER_HEIGHT 16
#define ITEM_EXISTS_TIME 4000
#define ITEM_WIDTH 10
#define ITEM_HEIGHT 10
#define ITEM_SPEED 0.07f
// ===== Thông số cho Weapon ======
#define WEAPON_SHIELD_SPEED 0.6f
#define WEAPON_SHIELD_MAX_DISTANCEX 4.5f
#define WEAPON_SHIELD_REVERSE_ACCELERATEX 0.02f
#define WEAPON_SHIELD_WIDTH 16
#define WEAPON_SHIELD_HEIGHT 10
// ===== Thông số Captain =====
#define PLAYER_RUNNING_SPEED 0.15f
#define PLAYER_JUMPING_SPEED 0.235f
#define PLAYER_FALLING_SPEED 0.25f
#define PLAYER_WIDTH 20
#define PLAYER_STANDING_HEIGHT 40
#define PLAYER_SITTING_HEIGHT 23
#define GRAVITY_SPEED 0.014f	
// ====== Thông số Wizard  ======
#define ENEMY_BOSS_WIDTH 28
#define ENEMY_BOSS_HEIGHT 45
#define ENEMY_BOSS_HEALTH 16
#define ENEMY_BOSS_DELAY_DEATH 3000
#define ENEMY_BOSS_DELAY_HIT 400
#define ENEMY_BOSS_DELAY_JUMP 1200
#define ENEMY_BOSS_LEFT 20
#define ENEMY_BOSS_RIGHT 230
#define ENEMY_BOSS_JUMP_SPEED 0.2f
#define ENEMY_BOSS_SPEED 0.175f

// ====== ENUM của Object  ======
extern enum Tag
{
	PLAYER,
	PLAYERFLASHING,
	ITEM,
	WEAPON,
	GROUND,
	MAP1,
	MAP2,
	MAP3,
	FONT,
	ENEMY,
	WIZARD,
	MINIBOSS,
	HOLDER,
	BULLET,
	MENUSCENE,
	CHANGESCENE,
	INTROSCENE,
	ENDSCENE,
};

// ====== Type Object ======
extern enum Type
{
	NONE,
	SHIELD,
	BOSS1,
	BOSS2,
	BLUESOLDIER,
	FLYINGROCKET,
	ROCKETSOLDIER,
	MINITANK,
	FIVEPOINT,
	ENERGY,
	ENERGYX10,
	POWERSTONE,
	POWERSTONEX10,
	KEY,
};

extern enum State
{
	STANDING,
	LOWHP_STANDING,
	RUNNING,
	LOWHP_ATTACKING,
	SHIELD_UP,
	SHIELD_DOWN,
	DASHING,
	JUMPING,
	SPINNING,
	FALLING,
	SITTING,
	ATTACKING,
	ATTACKING_JUMP,
	ATTACKING_STAND,
	ATTACKING_SIT,
	THROWING,
	CLINGING,
	ACTIVE,
	DEAD,
	INJURED,
	FLASHING,
	EXPLODED,
};

struct Rect {
	float x, y;
	float width, height;
	Rect() {}
	Rect(float x, float y, float width, float height)
	{
		//Bottom-left
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
	bool isContain(Rect r)
	{
		return !((x + width < r.x) || (x > r.x + r.width) || (y < r.y - r.height) || (y - height > r.y));
	}
};
struct Platform {
	Rect rect;
	int type;
	Platform() {}
	Platform(float x, float y, float width, float height, int type) {
		this->rect.x = x;
		this->rect.y = y;
		this->rect.width = width;
		this->rect.height = height;
		this->type = type;
	}
};
struct Wall
{
	Rect rect;

	Wall() {}
	Wall(float x, float y, float width, float height)
	{
		this->rect.x = x;
		this->rect.y = y;
		this->rect.width = width;
		this->rect.height = height;
	}
};