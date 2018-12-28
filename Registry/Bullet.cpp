#include "Bullet.h"
#include "map.h"



void Bullet::update(float time, float xpos, float ypos)
{
	if (name == "Bullet")
	{
		if (life)
		{
			if (xpos > x)
			{
				if (ypos > y)
					direction = 3;
				else
					if (ypos == y)
					direction = 2;
					else direction = 1;
			}
			else 
			{
				if (ypos > y)
					direction = 5;
				else
					if (ypos == y)
						direction = 6;
					else direction = 7;
			}

			if (xpos == x) 
				if (ypos > y)
					direction = 0;
				else direction = 4;
		
			switch (direction)
			{
			case 0: dx = 0; dy = -speed;
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 8) CurrentFrame -= 8;
				sprite.setScale(-1, 1);
				sprite.setTextureRect(IntRect(210 - 30 * int(CurrentFrame), 0, 30, 30));
				break;// state = right
			case 1: dx = speed; dy = -speed; 
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 8) CurrentFrame -= 8;
				sprite.setScale(1, 1);
				sprite.setTextureRect(IntRect(210 - 30 * int(CurrentFrame), 0, 30, 30));
			    break;// state = left
			case 2: dx = speed; dy = 0; 
				CurrentFrame += 0.0065*time;
				sprite.setScale(1, 1);
				if (CurrentFrame > 8) CurrentFrame -= 8;
				sprite.setTextureRect(IntRect(30 * int(CurrentFrame), 0, 30, 30));
				break;// state = up
			case 3: dx = speed; dy = speed;  
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 8) CurrentFrame -= 8;
				sprite.setScale(-1, 1);
				sprite.setTextureRect(IntRect(30 * int(CurrentFrame), 0, 30, 30));
				break;// state = down
			case 4: dx = 0; dy = speed;
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 8) CurrentFrame -= 8;
				sprite.setScale(-1, 1);
				sprite.setTextureRect(IntRect(30 * int(CurrentFrame), 0, 30, 30));
				break;// state = down
			case 5: dx = -speed; dy = speed;
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 8) CurrentFrame -= 8;
				sprite.setScale(-1, 1);
				sprite.setTextureRect(IntRect(210 - 30 * int(CurrentFrame), 0, 30, 30));
				break;// state = right
			case 6: dx = -speed; dy = 0;
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 8) CurrentFrame -= 8;
				sprite.setScale(1, 1);
				sprite.setTextureRect(IntRect(210 - 30 * int(CurrentFrame), 0, 30, 30));
				break;// state = left
			case 7: dx = -speed; dy = -speed;
				CurrentFrame += 0.0065*time;
				sprite.setScale(1, 1);
				if (CurrentFrame > 8) CurrentFrame -= 8;
				sprite.setTextureRect(IntRect(30 * int(CurrentFrame), 0, 30, 30));
				break;// state = up
			}

				
				
					x += dx * time;//само движение пули по х
					y += dy * time;//по у

					if (x <= 0) x = 10;// задержка пули в левой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки (сервер может тормозить!)
					if (y <= 0) y = 10;

					if (x >= 1024) x = 1004;// задержка пули в правой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки (сервер может тормозить!)
					if (y >= 576) y = 566;

					for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
						for (int j = x / 32; j < (x + w) / 32; j++)
						{
							if (TileMap[i][j] == '0' || time > 30 + rand()%(15))//если элемент наш тайлик земли, то
								life = false;// то пуля умирает
						}
					sprite.setPosition(x + w, y);//задается позицию пули
				
		}
	}
};
