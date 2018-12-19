#pragma once
#include "Entity.h"

////////////////////////////Псих//////////////////////// 
class Enemy :public Entity {
public:
	int direction;//направление движения врага 
	Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name) {
		if (name == "Psycho") {
			//Задаем спрайту один прямоугольник для 
			//вывода одного игрока. IntRect – для приведения типов 
			sprite.setTextureRect(IntRect(0, 0, w, h));
			direction = rand() % (3); //Направление движения врага задаём случайным образом через генератор случайных чисел 
			speed = 0.1;//этот объект всегда двигается 
			dx = speed;
		}
	}
	void update(float time);
};