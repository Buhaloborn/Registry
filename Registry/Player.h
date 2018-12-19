#pragma once
#include "Entity.h"

////////////////////////////Игрок//////////////////////// 
class Player :public Entity {
public:
	int playerScore;//эта переменная может быть только у игрока 
	Player(Image &image, float X, float Y, int W, int H, string Name) :Entity(image, X, Y, W, H, Name)
	{
		playerScore = 0;
		state = stay;
		if (name == "Player1")
		{
			//Задаем спрайту один прямоугольник для вывода одного игрока. IntRect – для приведения типов 
			sprite.setTextureRect(IntRect(40, 172, w, h));
		}
	}
	void control();
	void update(float time); //метод "оживления/обновления" объекта класса. 
};
