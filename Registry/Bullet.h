#pragma once
#include "entity.h"

class Bullet :public Entity {//класс пули
public:
	int direction;
	float xpos, ypos;
	Bullet(Image &image, float X, float Y, int W, int H, std::string  Name, int dir) :Entity(image, X, Y, W, H, Name) {
		if (name == "Bullet") {
			x = X; 
			y = Y;
			direction = dir;
			speed = 0.15;
			w = h = 16;
			life = true;
		}
	}

	void update(float time, float xpos, float ypos);
};