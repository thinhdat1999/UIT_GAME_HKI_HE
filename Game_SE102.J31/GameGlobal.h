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
#define NUMBER_MAP_LEVEL 6
#define BACK_COLOR D3DCOLOR_XRGB(0, 0, 0)

extern LPD3DXSPRITE spriteHandler; 
extern LPDIRECT3DDEVICE9 d3ddev;
extern LPDIRECT3DSURFACE9 backBuffer; // Back buffer
extern LPDIRECT3DSURFACE9 surface;
extern bool isGameRunning;;
extern bool isEndGame;
extern float delayEnd, delayStart;
extern int gameLevel;
extern std::unordered_map<int, bool> keyCode;

#define mCamera Camera::GetInstance()
#define player Player::GetInstance()
#define scoreboard ScoreBoard::GetInstance()

// ===== Các thông số cho Scene =====
#define SCENE_DELAY_START 3000
#define SCENE_DELAY_END 2000
#define SCENE_DELAY_RESTART 2500

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
#define WEAPON_STANDING_SHIELD_WIDTH 8
#define WEAPON_STANDING_SHIELD_HEIGHT 16
#define WEAPON_SHIELD_UP_WIDTH 18
#define WEAPON_SHIELD_UP_HEIGHT 10
// ===== Thông số Captain =====
#define PLAYER_RUNNING_SPEED 0.08f
#define PLAYER_ONWATER_SPEED -0.015f
#define PLAYER_JUMPING_SPEED 0.2f
#define PLAYER_FALLING_SPEED 0.25f
#define PLAYER_WIDTH 16
#define PLAYER_STANDING_HEIGHT 40
#define PLAYER_SITTING_HEIGHT 24
#define GRAVITY_SPEED 0.014f	
// ====== Thông số Wizard  ======
#define ENEMY_BOSS_WIDTH 28
#define ENEMY_BOSS_HEIGHT 46
#define ENEMY_BOSS_HEALTH 16
#define ENEMY_BOSS_DELAY_DEATH 3000
#define ENEMY_BOSS_DELAY_HIT 400
#define ENEMY_BOSS_DELAY_JUMP 1200
#define ENEMY_BOSS_LEFT 20
#define ENEMY_BOSS_RIGHT 230
#define ENEMY_BOSS_JUMP_SPEED 0.2f
#define ENEMY_BOSS_SPEED 0.175f
// ====== Thông số cho Enemy ======
#define ENEMY_FROZEN_TIME 3000
#define ENEMY_FROZEN_TIME_COUNT 3

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
	MAP4,
	MAP5,
	MAP6,
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
	LIGHTCONTROL,
	BLUESOLDIER,
	FLYINGROCKET,
	ROCKETSOLDIER,
	ELECTRICBAT,
	MINITANK,
	SPLITTING_PLATFORM,
	MOVING_PLATFORM,
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
	ONWATER,
	WATER_RUNNING,
	WATER_DIVING,
	WATER_FALLING,
	INWATER,
	SCOREBOARD,
	WAITING_TO_SPAWN,
	//MINITANK
	TOP,TOPLEFT,LEFT,BOTLEFT,BOT,BOTRIGHT,RIGHT,TOPRIGHT,
	SPINNING_LEFT, SPINNING_RIGHT,
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
//Type platform:
// 0: có thể nhảy xuyên qua
// 1: Không thể nhảy xuyên qua
// 2: Nước
// 3: Moving platform
// 4: Split  platform
// 5: Gai
struct Platform {
	Rect rect;
	int type;
	float dx, dy;
	Platform() {}
	Platform(float x, float y, float width, float height, int type, float dx = 0, float dy = 0) {
		this->rect.x = x;
		this->rect.y = y;
		this->rect.width = width;
		this->rect.height = height;
		this->type = type;
		this->dx = dx;
		this->dy = dy;
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