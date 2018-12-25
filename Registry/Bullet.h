#pragma once
#include "entity.h"

class Bullet :public Entity {//класс пули
public:
	int direction;//направление пули
				  //всё так же, только взяли в конце состояние игрока (int dir) 
				  //для задания направления полёта пули
	Bullet(Image &image, float X, float Y, int W, int H, std::string  Name, int dir) :Entity(image, X, Y, W, H, Name) {
		if (name == "Bullet") {
			x = X;
			y = Y;
			direction = dir;
			speed = 0.4;
			w = h = 16;
			life = true;
		}
		//выше инициализация в конструкторе

	}

	void update(float time);
};