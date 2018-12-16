#include <SFML/Graphics.hpp>
#include "Entity.h"

using namespace sf;
using namespace std;

////////////////////////////����//////////////////////// 
class Enemy :public Entity {
public:
	int direction;//����������� �������� ����� 
	Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name) {
		if (name == "Psycho") {
			//������ ������� ���� ������������� ��� 
			//������ ������ ������. IntRect � ��� ���������� ����� 
			sprite.setTextureRect(IntRect(0, 0, w, h));
			direction = rand() % (3); //����������� �������� ����� ����� ��������� ������� ����� ��������� ��������� ����� 
			speed = 0.1;//���� ������ ������ ��������� 
			dx = speed;
		}
	}

	void update(float time)
	{
		if (name == "Psycho") {

			if (life) {
				switch (direction)//�������� ��������� �������� � ����������� �� ��������� 
				{
				case 0: {//��������� ���� ������ 
					dx = speed;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 3) CurrentFrame -= 3;
					sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
					break;
				}
				case 1: {//��������� ���� ����� 
					dx = -speed;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 3) CurrentFrame -= 3;
					sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));
					break;
				}
				case 2: {//���� ����� 
					dy = -speed;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 3) CurrentFrame -= 3;
					sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));
					break;
				}
				case 3: {//���� ���� 
					dy = speed;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 3) CurrentFrame -= 3;
					sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
					break;
				}
				}

				x += dx * time; //�������� �� �X� 
				y += dy * time; //�������� �� �Y� 

				sprite.setPosition(x, y); //������ � ������� (x, y). 

				if (health <= 0) { life = false; }//���� ������ ������ 0, ���� ����� 0, �� ������� 
			}
		}
	}
};