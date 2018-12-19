#include "Enemy.h"

////////////////////////////ѕсих//////////////////////// 
	void Enemy::update(float time)
	{
		if (name == "Psycho") {

			if (life) {
				switch (direction)//делаютс€ различные действи€ в зависимости от состо€ни€ 
				{
				case 0: {//состо€ние идти вправо 
					dx = speed; dy = 0;
					CurrentFrame += 0.0065*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setScale(1, 1);
					sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 0, 40, 86));
					break;
				}
				case 1: {//состо€ние идти влево 
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

				x += dx * time; //движение по УXФ 
				y += dy * time; //движение по УYФ 

				sprite.setPosition(x, y); //спрайт в позиции (x, y). 

				if (health <= 0) { life = false; }//если жизней меньше 0, либо равно 0, то умираем 
			}
		}
	}