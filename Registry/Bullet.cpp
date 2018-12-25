#include "Bullet.h"
#include "map.h"



void Bullet::update(float time)
{
	if (name == "Bullet") 
	{
		switch (direction)
		{
		case 0: dx = speed; dy = 0;   break;// state = left
		case 1: dx = -speed; dy = 0;   break;// state = right
		case 2: dx = 0; dy = -speed;   break;// state = up
		case 3: dx = 0; dy = speed;   break;// state = down
		}

		if (life) {
			x += dx * time;//���� �������� ���� �� �
			y += dy * time;//�� �

			if (x <= 0) x = 10;// �������� ���� � ����� �����, ����� ��� ���������� ������ ��� �������� �� �������� �� ������ ����� � �� ���� ������ (������ ����� ���������!)
			if (y <= 0) y = 10;

			if (x >= 1024) x = 1014;// �������� ���� � ������ �����, ����� ��� ���������� ������ ��� �������� �� �������� �� ������ ����� � �� ���� ������ (������ ����� ���������!)
			if (y >= 576) y = 566;

			for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� �����
				for (int j = x / 32; j < (x + w) / 32; j++)
				{
					if (TileMap[i][j] == '0')//���� ������� ��� ������ �����, ��
						life = false;// �� ���� �������
				}
			sprite.setPosition(x + w, y);//�������� ������� ����
		}
	}
};
