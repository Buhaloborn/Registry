#include "Place.h"
#include <cstdlib>
#include "Entity.h"
//////////////////////////////////////////////////////
Place::Place(Image &image, float X, float Y, int W, int H)
{
	x = X; y = Y; //координата появления спрайта 
	w = W; h = H;
	CurrentFrame = rand() % (3);
	sprite.setTextureRect(IntRect(0, 0, w, h));
	texture.loadFromImage(image); //заносим изображение в текстуру 
	sprite.setTexture(texture); //заливаем спрайт текстурой 
	sprite.setPosition(x, y);
}

void Place::update(float time)
{
	//act();
	CurrentFrame += (0.0002)*(rand()%(10))*time;
	if (CurrentFrame > 2) CurrentFrame -= 2;
	sprite.setTextureRect(IntRect(60 * int(CurrentFrame), 0, 60, 75));
	if (int(CurrentFrame) % 2 == 0) 
		isOpen = true; //окно открыто
	else
		isOpen = false; //окно закрыто
}

FloatRect Place::getRect(){//метод получения прямоугольника. его коорд, размеры (шир,высот). 
	FloatRect FR(x, y, w, h);
	return FR;
}