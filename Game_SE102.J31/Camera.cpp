#include "Camera.h"

Camera* Camera::instance = NULL;

Camera* Camera::GetInstance()
{
	if (instance == NULL)
		instance = new Camera();
	return instance;
}

Camera::Camera()
{
	this->width = SCREEN_WIDTH;
	this->height = SCREEN_HEIGHT;
}

Rect Camera::GetRect()
{
	return Rect(x, y, width, height);
}

void Camera::Update(Rect mapRect)
{
	// Camera về phần trái của map
	if (this->x <= 0)
	{
		this->x = 0;
	}

	// Camera về phần phải của map
	else if (this->x >= mapRect.width - this->width)
	{
		this->x = mapRect.width - this->width;
	}
	// Camera đi về phần trên
	if (this->y >= mapRect.height) {
		this->worldY = 0;
		this->y = mapRect.height;
	}
	// Camera đi về phần dưới 
	else if (mapRect.height - this->y >= mapRect.height - this->height) {
		this->worldY = mapRect.height - this->height;
		this->y = this->height;
	}
	// Chuyển đổi tọa độ bottom-left về góc tọa độ top-left để vẽ 
	else {
		this->worldY = mapRect.height - this->y;
	}

}