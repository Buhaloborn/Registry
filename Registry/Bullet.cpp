#include "Bullet.h"
#include "map.h"



void Bullet::update(float time)
{
	if (name == "Bullet") 
	{
		switch (direction)
		{
		case 0: dx = speed; dy = 0;   break;// state = left
		case 1: dx = -speed; dy = 0;   break;// state = right
		case 2: dx = 0; dy = -speed;   break;// state = up
		case 3: dx = 0; dy = speed;   break;// state = down
		}

		if (life) {
			x += dx * time;//само движение пули по х
			y += dy * time;//по у

			if (x <= 0) x = 10;// задержка пули в левой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки (сервер может тормозить!)
			if (y <= 0) y = 10;

			if (x >= 1024) x = 1014;// задержка пули в правой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки (сервер может тормозить!)
			if (y >= 576) y = 566;

			for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
				for (int j = x / 32; j < (x + w) / 32; j++)
				{
					if (TileMap[i][j] == '0')//если элемент наш тайлик земли, то
						life = false;// то пуля умирает
				}
			sprite.setPosition(x + w, y);//задается позицию пули
		}
	}
};
