#include <SFML\Graphics.hpp>
#include "Entity.h"

using namespace sf;
using namespace std;

////////////////////////////»грок//////////////////////// 
class Player :public Entity {
public:
	int playerScore;//эта переменна€ может быть только у игрока 

	Player(Image &image, float X, float Y, int W, int H, string Name) :Entity(image, X, Y, W, H, Name) {
		playerScore = 0;
		state = stay;
		if (name == "Player1") {
			//«адаем спрайту один пр€моугольник дл€ вывода одного игрока. IntRect Ц дл€ приведени€ типов 
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
	}

	void control() {
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			state = left;
			speed = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			state = right;
			speed = 0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			state = up;
			speed = 0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			state = down;
			speed = 0.1;
		}
	}

	void update(float time) //метод "оживлени€/обновлени€" объекта класса. 
	{
		if (life) {//провер€ем, жив ли герой 
			control();//функци€ управлени€ персонажем 
			switch (state)//делаютс€ различные действи€ в зависимости от состо€ни€ 
			{
			case right: {//состо€ние идти вправо 
				dx = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
				break;
			}
			case left: {//состо€ние идти влево 
				dx = -speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));
				break;
			}
			case up: {//идти вверх 
				dy = -speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));
				break;
			}
			case down: {//идти вниз 
				dy = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
				break;
			}
			case stay: {//стоим 
				dy = speed;
				dx = speed;
				break;
			}
			}

			x += dx * time; //движение по УXФ 
			y += dy * time; //движение по УYФ 

			speed = 0; //обнул€ем скорость, чтобы персонаж остановилс€. 
			state = stay; //состо€ние - стоим 

			sprite.setPosition(x, y); //спрайт в позиции (x, y). 

			if (health <= 0) { life = false; }//если жизней меньше 0, либо равно 0, то умираем 
		}
	}
};
