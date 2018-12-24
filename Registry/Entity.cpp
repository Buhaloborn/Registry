#include "Entity.h"
using namespace sf;
////////////////////////////јбстрактна€ сущность//////////////////////// 


	Entity::Entity(Image &image, float X, float Y, int W, int H, string Name) {
		x = X; y = Y; //координата по€влени€ спрайта 
		w = W; h = H;
		health = 100;
		name = Name;
		moveTimer = 0;
		dx = 0; dy = 0;
		speed = 0;
		CurrentFrame = 0;
		life = true; //сущность жива
		texture.loadFromImage(image); //заносим изображение в текстуру 
		sprite.setTexture(texture); //заливаем спрайт текстурой 
	}

	FloatRect Entity::getRect() {//метод получени€ пр€моугольника. его коорд, размеры (шир,высот). 
		FloatRect FR(x, y, w, h);
		return FR;
	}