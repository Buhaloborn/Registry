#include "Entity.h"
using namespace sf;

////////////////////////////Абстрактная сущность//////////////////////// 
	Entity::Entity(Image &image, float X, float Y, int W, int H, string Name) {
		x = X; y = Y; 
		w = W; h = H;
		health = 100;
		name = Name;
		moveTimer = 0;
		dx = 0; dy = 0;
		speed = 0;
		CurrentFrame = 0;
		life = true; //сущность жива
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}

	FloatRect Entity::getRect() {
		FloatRect FR(x, y, w, h);
		return FR;
	}