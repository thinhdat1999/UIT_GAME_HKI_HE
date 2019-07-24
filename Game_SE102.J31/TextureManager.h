#pragma once
#include <unordered_map>
#include "d3dx9.h"
#include "GameGlobal.h"

using namespace std;

class TextureManager
{
private:
	static TextureManager * _instance;
	unordered_map<Tag, LPDIRECT3DTEXTURE9> textures;
public:
	void StartUp();
	void ShutDown();
	void AddTexture(Tag tag, LPCSTR filePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 GetTexture(Tag tag);
	static TextureManager * GetInstance();
};