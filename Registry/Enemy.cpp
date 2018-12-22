#include "Enemy.h"
#include "map.h"
using namespace std;

////////////////////////////Псих//////////////////////// 
void Enemy::checkCollisionWithMap(float Dx, float Dy)//ф-ция проверки столкновений с картой
{
	for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
		for (int j = x / 32; j < (x + w) / 32; j++)
		{
			if ((TileMap[i][j] == '0') or (TileMap[i][j] == 'X'))//если элемент - тайлик земли
			{
				if (Dy > 0) {
					y = i * 32 - h;  dy = -0.1;
					direction = rand() % (4); //Направление движения врага
				}//по Y 
				if (Dy < 0) {
					y = i * 32 + 32; dy = 0.1;
					direction = rand() % (4);//Направление движения врага 
				}//столкновение с верхними краями 
				if (Dx > 0) {
					x = j * 32 - w; dx = -0.1;
					direction = rand() % (4);//Направление движения врага 
				}//с правым краем карты
				if (Dx < 0) {
					x = j * 32 + 32; dx = 0.1;
					direction = rand() % (4); //Направление движения врага
				}// с левым краем карты
			}
		}
}

	void Enemy::update(float time)
	{
		if (name == "Psycho") {

			if (life) {
				switch (direction)//делаются различные действия в зависимости от состояния 
				{
				case 0: {//состояние идти вправо 
					dx = speed; dy = 0;
					CurrentFrame += 0.0065*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setScale(1, 1);
					sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 0, 40, 86));
					break;
				}
				case 1: {//состояние идти влево 
					dx = -speed; dy = 0;
					CurrentFrame += 0.0065*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setScale(-1, 1);
					sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 0, 40, 86));
					break;
				}
				case 2: {//идти вверх 
					dy = -speed; dx = 0;
					CurrentFrame += 0.0065*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 172, 40, 86));
					break;
				}
				case 3: {//идти вниз 
					dy = speed; dx = 0;
					CurrentFrame += 0.0065*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 86, 40, 86));
					break;
				}
				}

				x += dx * time; //движение по “X” 
				checkCollisionWithMap(dx, 0);//
				y += dy * time; //движение по “Y” 
				checkCollisionWithMap(0, dy);//

				sprite.setPosition(x, y); //спрайт в позиции (x, y). 

				//if (PlayerScore <= 0) { life = false; }//если жизней меньше 0, либо равно 0, то умираем 
			}
		}
	}