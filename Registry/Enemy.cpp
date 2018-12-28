#include "Enemy.h"
#include "map.h"
#include <iostream>
using namespace std;
using namespace sf;

////////////////////////////����//////////////////////// 
void Enemy::checkCollisionWithMap(float Dx, float Dy)//�-��� �������� ������������ � ������
{
	for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� �����
		for (int j = x / 32; j < (x + w) / 32; j++)
		{
			if ((TileMap[i][j] == '0') or (TileMap[i][j] == 'X'))
			{
				if (Dy > 0) {
					y = i * 32 - h;  dy = -0.1;
					direction = 2;
				}//�� Y 
				if (Dy < 0) {
					y = i * 32 + 32; dy = 0.1;
					direction = 3;
				}//������������ � �������� ������ 
				if (Dx > 0) {
					x = j * 32 - w; dx = -0.1;
					direction = 1;
				}//� ������ ����� �����
				if (Dx < 0) {
					x = j * 32 + 32; dx = 0.1;
					direction = 0; //� ����� ����� �����
				}
			}
		}
}

	void Enemy::update(float time, float xpos, float ypos)
	{
		if (name == "Psycho") {

			if (life) {
				switch (direction)//�������� ��������� �������� � ����������� �� ��������� 
				{
				case 0: {//��������� ���� ������ 
					dx = speed; dy = 0;
					CurrentFrame += 0.0065*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 87, 40, 86));
					break;
					}
				case 1: {//��������� ���� ����� 
					dx = -speed; dy = 0;
					CurrentFrame += 0.0065*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 1, 40, 86));
					break;
					}
				case 2: {//���� ����� 
					dy = -speed; dx = 0;
					CurrentFrame += 0.0065*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 259, 40, 86));
					break;
					}
				case 3: {//���� ���� 
					dy = speed; dx = 0;
					CurrentFrame += 0.0065*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 173, 40, 86));
					break;
					}
				}

				x += dx * time; //�������� �� �X� 
				checkCollisionWithMap(dx, 0);//
				y += dy * time; //�������� �� �Y� 
				checkCollisionWithMap(0, dy);//
				
				sprite.setPosition(x, y); //������ � ������� (x, y). 
			}
		}
	}