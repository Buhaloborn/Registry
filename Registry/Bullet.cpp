#include "Bullet.h"



void Bullet::update(float time)
{
	if (name == "Bullet") 
	{
		switch (direction)
		{
		case 0: dx = -speed; dy = 0;   break;// state = left
		case 1: dx = speed; dy = 0;   break;// state = right
		case 2: dx = 0; dy = -speed;   break;// state = up
		case 3: dx = 0; dy = speed;   break;// state = down
		}

		if (life) {
			x += dx * time;//���� �������� ���� �� �
			y += dy * time;//�� �

			if (x <= 0) x = 20;// �������� ���� � ����� �����, ����� ��� ���������� ������ ��� �������� �� �������� �� ������ ����� � �� ���� ������ (������ ����� ���������!)
			if (y <= 0) y = 20;

			if (x >= 1024) x = 1004;// �������� ���� � ������ �����, ����� ��� ���������� ������ ��� �������� �� �������� �� ������ ����� � �� ���� ������ (������ ����� ���������!)
			if (y >= 576) y = 556;


			

			sprite.setPosition(x + w / 2, y + h / 2);//�������� ������� ����
		}
	}
};
