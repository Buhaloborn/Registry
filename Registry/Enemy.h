#include <SFML/Graphics.hpp>
#include "Entity.h"

using namespace sf;
using namespace std;

////////////////////////////ѕсих//////////////////////// 
class Enemy :public Entity {
public:
	int direction;//направление движени€ врага 
	Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name) {
		if (name == "Psycho") {
			//«адаем спрайту один пр€моугольник дл€ 
			//вывода одного игрока. IntRect Ц дл€ приведени€ типов 
			sprite.setTextureRect(IntRect(0, 0, w, h));
			direction = rand() % (3); //Ќаправление движени€ врага задаЄм случайным образом через генератор случайных чисел 
			speed = 0.1;//этот объект всегда двигаетс€ 
			dx = speed;
		}
	}

	void update(float time)
	{
		if (name == "Psycho") {

			if (life) {
				switch (direction)//делаютс€ различные действи€ в зависимости от состо€ни€ 
				{
				case 0: {//состо€ние идти вправо 
					dx = speed;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 3) CurrentFrame -= 3;
					sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
					break;
				}
				case 1: {//состо€ние идти влево 
					dx = -speed;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 3) CurrentFrame -= 3;
					sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));
					break;
				}
				case 2: {//идти вверх 
					dy = -speed;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 3) CurrentFrame -= 3;
					sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));
					break;
				}
				case 3: {//идти вниз 
					dy = speed;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 3) CurrentFrame -= 3;
					sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
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
};