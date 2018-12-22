#include "Enemy.h"
#include "map.h"
using namespace std;

////////////////////////////����//////////////////////// 
void Enemy::checkCollisionWithMap(float Dx, float Dy)//�-��� �������� ������������ � ������
{
	for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� �����
		for (int j = x / 32; j < (x + w) / 32; j++)
		{
			if ((TileMap[i][j] == '0') or (TileMap[i][j] == 'X'))//���� ������� - ������ �����
			{
				if (Dy > 0) {
					y = i * 32 - h;  dy = -0.1;
					direction = rand() % (4); //����������� �������� �����
				}//�� Y 
				if (Dy < 0) {
					y = i * 32 + 32; dy = 0.1;
					direction = rand() % (4);//����������� �������� ����� 
				}//������������ � �������� ������ 
				if (Dx > 0) {
					x = j * 32 - w; dx = -0.1;
					direction = rand() % (4);//����������� �������� ����� 
				}//� ������ ����� �����
				if (Dx < 0) {
					x = j * 32 + 32; dx = 0.1;
					direction = rand() % (4); //����������� �������� �����
				}// � ����� ����� �����
			}
		}
}

	void Enemy::update(float time)
	{
		if (name == "Psycho") {

			if (life) {
				switch (direction)//�������� ��������� �������� � ����������� �� ��������� 
				{
				case 0: {//��������� ���� ������ 
					dx = speed; dy = 0;
					CurrentFrame += 0.0065*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setScale(1, 1);
					sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 0, 40, 86));
					break;
				}
				case 1: {//��������� ���� ����� 
					dx = -speed; dy = 0;
					CurrentFrame += 0.0065*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setScale(-1, 1);
					sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 0, 40, 86));
					break;
				}
				case 2: {//���� ����� 
					dy = -speed; dx = 0;
					CurrentFrame += 0.0065*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 172, 40, 86));
					break;
				}
				case 3: {//���� ���� 
					dy = speed; dx = 0;
					CurrentFrame += 0.0065*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 86, 40, 86));
					break;
				}
				}

				x += dx * time; //�������� �� �X� 
				checkCollisionWithMap(dx, 0);//
				y += dy * time; //�������� �� �Y� 
				checkCollisionWithMap(0, dy);//

				sprite.setPosition(x, y); //������ � ������� (x, y). 

				//if (PlayerScore <= 0) { life = false; }//���� ������ ������ 0, ���� ����� 0, �� ������� 
			}
		}
	}