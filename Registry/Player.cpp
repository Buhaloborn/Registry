#include "Player.h"
#include "map.h"

using namespace std;

////////////////////////////�����//////////////////////// 
	void Player::control() 
	{
		if (Keyboard::isKeyPressed(Keyboard::Left)) 
		{
			state = left;
			speed = 0.2;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) 
		{
			state = right;
			speed = 0.2;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) 
		{
			state = up;
			speed = 0.2;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) 
		{
			state = down;
			speed = 0.2;
		}
	};


	void Player::update(float time) //����� "���������/����������" ������� ������. 
	{
		if (life)
		{//���������, ��� �� ����� 
			control();//������� ���������� ���������� 
			switch (state)//�������� ��������� �������� � ����������� �� ��������� 
			{
			case right: {//��������� ���� ������ 
				dx = speed; dy = 0;
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setScale(1, 1);
				sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 0, 40, 86));
				break;
			}
			case left: {//��������� ���� ����� 
				dx = -speed; dy = 0;
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setScale(-1, 1);
				sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 0, 40, 86));
				break;
			}
			case up: {//���� ����� 
				dy = -speed; dx = 0;
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 172, 40, 86));
				break;
			}
			case down: {//���� ���� 
				dy = speed; dx = 0;
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 86, 40, 86));
				break;
			}
			case stay: {//����� 
				dy = speed;
				dx = speed;
				break;
			}
			}

			x += dx * time; //�������� �� �X� 
			checkCollisionWithMap(dx, 0);
			y += dy * time; //�������� �� �Y� 
			checkCollisionWithMap(0, dy);

			speed = 0; //�������� ��������, ����� �������� �����������. 
			state = stay; //��������� - ����� 

			sprite.setPosition(x, y); //������ � ������� (x, y). 

			if (PlayerScore <= 0) { life = false; }//���� ������ ������ 0, ���� ����� 0, �� ������� 
		}
	}

	void Player::checkCollisionWithMap(float Dx, float Dy) {
		
		for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� �����
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				if ((TileMap[i][j] == '0') or (TileMap[i][j] == 'X')) //���� c����
				{
					if (Dy > 0) { y = i * 32 - h;  dy = 0;}//�� Y 
					if (Dy < 0) { y = i * 32 + 40; dy = 0;}//������������ � �������� ������ �����
					if (Dx > 0) { x = j * 32 - w; dx = 0;}//� ������ ����� �����
					if (Dx < 0) { x = j * 32 + 40; dx = 0;}// � ����� ����� �����
				}
			}
	};
