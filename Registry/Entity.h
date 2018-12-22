#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

////////////////////////////Абстрактная сущность//////////////////////// 
class Entity {
public:
	enum { left, right, up, down, stay } state;// тип перечисления - состояние объекта 
	float dx, dy, x, y, speed, moveTimer;
	int w, h;
	int health;
	bool life; //жизнь, логическая 
	Texture texture;//сфмл текстура 
	Sprite sprite;//сфмл спрайт 


	float CurrentFrame;//хранит текущий кадр 
	string name;//враги могут быть разные, врагов можно различать по именам 
				//каждому можно дать свое действие в update() в зависимости от имени 

	Entity(Image &image, float X, float Y, int W, int H, std::string Name);

	FloatRect getRect(); //метод получения прямоугольника. его коорд, размеры (шир,высот). 

	virtual void update(float time) = 0;
};
