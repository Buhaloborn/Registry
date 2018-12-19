#pragma once
#include <SFML/Graphics.hpp> 

using namespace sf;
using namespace std;


////////////////////////////Абстрактная сущность//////////////////////// 
class Entity {
public:
	enum { left, right, up, down, stay } state;// тип перечисления - состояние объекта 
	float dx, dy, x, y, speed, moveTimer;
	int w, h, health; //хп игрока 
	bool life; //жизнь, логическая 
	Texture texture;//сфмл текстура 
	Sprite sprite;//сфмл спрайт 
	float CurrentFrame;//хранит текущий кадр 
	string name;//враги могут быть разные, врагов можно различать по именам 
				//каждому можно дать свое действие в update() в зависимости от имени 

	Entity(Image &image, float X, float Y, int W, int H, std::string Name) {
		x = X; y = Y; //координата появления спрайта 
		w = W; h = H;
		name = Name;
		moveTimer = 0;
		dx = 0; dy = 0;
		speed = 0;
		CurrentFrame = 0;
		health = 100;
		life = true; //сущность жива
		texture.loadFromImage(image); //заносим изображение в текстуру 
		sprite.setTexture(texture); //заливаем спрайт текстурой 
	}

	FloatRect getRect() {//метод получения прямоугольника. его коорд, размеры (шир,высот). 
		FloatRect FR(x, y, w, h);
		return FR;
	}
	virtual void update(float time) = 0;
};
