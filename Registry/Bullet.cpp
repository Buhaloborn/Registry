#include "Bullet.h"
#include "map.h"

void Bullet::update(float time, float xpos, float ypos) 

{
	if (name == "Bullet")
	{
		if (life)
		{
			//////////////////проверка координат игрока//////////////////
			if (xpos > x)
			{
				if (ypos > y)
					direction = 3;  //south east
				else
					if (ypos == y)
					direction = 2;  //east
					else direction = 1;  //north east
			}
			else 
			{
				if (ypos > y)
					direction = 5;  //south west
				else
					if (ypos == y)
						direction = 6;  //west
					else direction = 7; //north west
			}

			if (xpos == x) 
				if (ypos > y)
					direction = 0;  //north
				else direction = 4; //south
		////////в зависимости от положения игрока, тапки будут на него наводиться////////

		////////присвоение dx и dy в зависимости от направления

			switch (direction)
			{
			case 0: dx = 0; dy = -speed;
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 8)
					CurrentFrame -= 8;
				sprite.setTextureRect(IntRect(210 - 30 * int(CurrentFrame), 0, 30, 30));
				break;// north
			
			case 1: dx = speed; dy = -speed; 
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 8)
					CurrentFrame -= 8;
				sprite.setTextureRect(IntRect(210 - 30 * int(CurrentFrame), 0, 30, 30));
			    break;// north east
			
			case 2: dx = speed; dy = 0; 
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 8)
					CurrentFrame -= 8;
				sprite.setTextureRect(IntRect(210 - 30 * int(CurrentFrame), 0, 30, 30));
				break;// east
			
			case 3: dx = speed; dy = speed;  
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 8)
					CurrentFrame -= 8;
				sprite.setTextureRect(IntRect(210 - 30 * int(CurrentFrame), 0, 30, 30));
				break;// south east
			
			case 4: dx = 0; dy = speed;
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 8)
					CurrentFrame -= 8;
				sprite.setTextureRect(IntRect(210 - 30 * int(CurrentFrame), 0, 30, 30));
				break;// south
			
			case 5: dx = -speed; dy = speed;
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 8)
					CurrentFrame -= 8;
				sprite.setTextureRect(IntRect(210 - 30 * int(CurrentFrame), 0, 30, 30));
				break;// south west
			
			case 6: dx = -speed; dy = 0;
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 8)
					CurrentFrame -= 8;
				sprite.setTextureRect(IntRect(210 - 30 * int(CurrentFrame), 0, 30, 30));
				break;// west
			
			case 7: dx = -speed; dy = -speed;
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 8)
					CurrentFrame -= 8;
				sprite.setTextureRect(IntRect(210 - 30 * int(CurrentFrame), 0, 30, 30));
				break;// north west
			}

				
				
					x += dx * time;//само движение пули по х
					y += dy * time;//по у

					if (x <= 0) x = 10;// задержка пули в левой стене, чтобы при проседании кадров она случайно
					if (y <= 0) y = 10;// не вылетела за предел карты и не было ошибки (сервер может тормозить!)

					if (x >= 1024) x = 1004;//задержка пули в правой стене, чтобы при проседании кадров она случайно
					if (y >= 576) y = 566;  //не вылетела за предел карты и не было ошибки (сервер может тормозить!)

					for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
						for (int j = x / 32; j < (x + w) / 32; j++)
						{
							if (TileMap[i][j] == '0' || time > 30 + rand()%(15))//если пуля пересекается с краем карты или
								life = false;									//не успевает долететь до игрока, то умирает
						}
					sprite.setPosition(x + w, y);//задается позиция пули
				
		}
	}
};
