#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

////////////////////////////Абстрактная сущность//////////////////////// 
class Entity {
public:
	enum { left, right, up, down, stay } state;//состояния объекта 
	float dx, dy, x, y, speed, moveTimer;
	int w, h;
	float health;
	bool life; //жизнь, логическая 
	Texture texture;
	Sprite sprite;

	float CurrentFrame;//хранит текущий кадр 
	string name;

	Entity(Image &image, float X, float Y, int W, int H, std::string Name);

	FloatRect getRect();

	virtual void update(float time, float xpos, float ypos) = 0;
};
