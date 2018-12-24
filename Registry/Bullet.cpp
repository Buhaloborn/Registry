#include "Bullet.h"



void Bullet::update(float time)
{
	if (name == "Bullet") 
	{
		switch (direction)
		{
		case 0: dx = -speed; dy = 0;   break;// state = left
		case 1: dx = speed; dy = 0;   break;// state = right
		case 2: dx = 0; dy = -speed;   break;// state = up
		case 3: dx = 0; dy = speed;   break;// state = down
		}

		if (life) {
			x += dx * time;//само движение пули по х
			y += dy * time;//по у

			if (x <= 0) x = 20;// задержка пули в левой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки (сервер может тормозить!)
			if (y <= 0) y = 20;

			if (x >= 1024) x = 1004;// задержка пули в правой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки (сервер может тормозить!)
			if (y >= 576) y = 556;


			

			sprite.setPosition(x + w / 2, y + h / 2);//задается позицию пули
		}
	}
};
