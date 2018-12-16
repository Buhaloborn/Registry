#include <SFML\Graphics.hpp>
#include "Entity.h"

using namespace sf;
using namespace std;

////////////////////////////�����//////////////////////// 
class Player :public Entity {
public:
	int playerScore;//��� ���������� ����� ���� ������ � ������ 

	Player(Image &image, float X, float Y, int W, int H, string Name) :Entity(image, X, Y, W, H, Name) {
		playerScore = 0;
		state = stay;
		if (name == "Player1") {
			//������ ������� ���� ������������� ��� ������ ������ ������. IntRect � ��� ���������� ����� 
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

	void update(float time) //����� "���������/����������" ������� ������. 
	{
		if (life) {//���������, ��� �� ����� 
			control();//������� ���������� ���������� 
			switch (state)//�������� ��������� �������� � ����������� �� ��������� 
			{
			case right: {//��������� ���� ������ 
				dx = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
				break;
			}
			case left: {//��������� ���� ����� 
				dx = -speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));
				break;
			}
			case up: {//���� ����� 
				dy = -speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));
				break;
			}
			case down: {//���� ���� 
				dy = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
				break;
			}
			case stay: {//����� 
				dy = speed;
				dx = speed;
				break;
			}
			}

			x += dx * time; //�������� �� �X� 
			y += dy * time; //�������� �� �Y� 

			speed = 0; //�������� ��������, ����� �������� �����������. 
			state = stay; //��������� - ����� 

			sprite.setPosition(x, y); //������ � ������� (x, y). 

			if (health <= 0) { life = false; }//���� ������ ������ 0, ���� ����� 0, �� ������� 
		}
	}
};
