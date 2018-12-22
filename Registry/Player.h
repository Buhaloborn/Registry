#pragma once
#include "Entity.h"



////////////////////////////Игрок//////////////////////// 
class Player : public Entity {
public:
	int PlayerScore;//эта переменная может быть только у игрока 
	Player(Image &image, float X, float Y, int W, int H, string Name) :Entity(image, X, Y, W, H, Name)
	{
		PlayerScore = 1000;
		state = stay;
		if (name == "Player")
		{
			//Задаем спрайту один прямоугольник для вывода одного игрока. IntRect – для приведения типов 
			sprite.setTextureRect(IntRect(40, 172, w, h));
		}
	}

	void checkCollisionWithMap(float Dx, float Dy);
	void control();
	void update(float time); //метод "оживления обновления" объекта класса. 
};