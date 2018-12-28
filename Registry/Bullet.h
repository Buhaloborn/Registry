#pragma once
#include "entity.h"

class Bullet :public Entity {//класс пули
public:
	int direction;//направление пули
	float xpos, ypos;
	Bullet(Image &image, float X, float Y, int W, int H, std::string  Name, int dir) :Entity(image, X, Y, W, H, Name) {
		if (name == "Bullet") {
			x = X; 
			y = Y;
			direction = dir;
			speed = 0.2;
			w = h = 16;
			life = true;
	/*		if (xpos > x)
			{
				if (ypos > y)
					direction = 3;
				else
					if (ypos == y)
						direction = 2;
					else direction = 1;
			}
			else
			{
				if (ypos > y)
					direction = 5;
				else
					if (ypos == y)
						direction = 6;
					else direction = 7;
			}

			if (xpos == x)
				if (ypos > y)
					direction = 0;
				else direction = 4;
	*/	
		}
		//выше инициализация в конструкторе

	}

	void update(float time, float xpos, float ypos);
};