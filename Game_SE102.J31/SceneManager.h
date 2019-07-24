#pragma once
#include "Scene.h"
#include <unordered_map>

class SceneManager
{
private:
	Scene * _curScene;
	static SceneManager * _instance;
	//unordered_map<int, Scene> scenes;
public:
	SceneManager();
	~SceneManager() {};

	void StartUp();
	void ShutDown();

	void ReplaceScene(Scene* scene);			// Thay thế Scene hiện có bằng Scene khác (dùng cho chuyển cảnh)
	Scene* GetCurScene();						// Get Scene hiện tại
	static SceneManager* GetInstance();
};