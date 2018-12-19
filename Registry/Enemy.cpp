#include "Enemy.h"

////////////////////////////����//////////////////////// 
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
				y += dy * time; //�������� �� �Y� 

				sprite.setPosition(x, y); //������ � ������� (x, y). 

				if (health <= 0) { life = false; }//���� ������ ������ 0, ���� ����� 0, �� ������� 
			}
		}
	}