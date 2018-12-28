#include "Player.h"
#include "map.h"

using namespace std;

///////////Управление////////////////
	void Player::control() 
	{
		if (Keyboard::isKeyPressed(Keyboard::Left)) 
		{
			state = left;
			speed = 0.2;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) 
		{
			state = right;
			speed = 0.2;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) 
		{
			state = up;
			speed = 0.2;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) 
		{
			state = down;
			speed = 0.2;
		}
	};

	void Player::update(float time, float xpos, float ypos) //метод "оживления/обновления" объекта класса. 
	{
		if (life)
		{//проверяем, жив ли герой 
			control();//функция управления персонажем 
			switch (state)
			{
			case right: {//идти вправо 
				dx = speed; dy = 0;
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 87, 40, 86));
				break;
				}
			case left: {//идти влево 
				dx = -speed; dy = 0;
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 0, 40, 86));
				break;
				}
			case up: {//идти вверх 
				dy = -speed; dx = 0;
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 259, 40, 86));
				break;
				}
			case down: {//идти вниз 
				dy = speed; dx = 0;
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 173, 40, 86));
				break;
				}
			case stay: {//стоим 
				dy = speed;
				dx = speed;
				break;
				}
			}

			x += dx * time; //движение по “X” 
			checkCollisionWithMap(dx, 0);
			y += dy * time; //движение по “Y” 
			checkCollisionWithMap(0, dy);

			speed = 0; //обнуляем скорость, чтобы персонаж остановился. 
			state = stay; //состояние - стоим 

			sprite.setPosition(x, y); //спрайт в позиции (x, y). 
		}
	}

	void Player::checkCollisionWithMap(float Dx, float Dy) { //проверка столкновений с элементами карты
		
		for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				if ((TileMap[i][j] == '0') or (TileMap[i][j] == 'X')) //если cтена
				{
					if (Dy > 0) { y = i * 32 - h;  dy = 0;}//с нижним краем
					if (Dy < 0) { y = i * 32 + 40; dy = 0;}//с верхним краем
					if (Dx > 0) { x = j * 32 - w; dx = 0;}//с правым краем карты
					if (Dx < 0) { x = j * 32 + 40; dx = 0;}// с левым краем карты
				}
			}
	};
