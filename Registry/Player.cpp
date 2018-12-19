#include "Player.h"
using namespace std;

////////////////////////////�����//////////////////////// 
	void Player::control() 
	{
		if (Keyboard::isKeyPressed(Keyboard::Left)) 
		{
			state = left;
			speed = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) 
		{
			state = right;
			speed = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) 
		{
			state = up;
			speed = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) 
		{
			state = down;
			speed = 0.1;
		}
	}


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
			y += dy * time; //�������� �� �Y� 

			speed = 0; //�������� ��������, ����� �������� �����������. 
			state = stay; //��������� - ����� 

			sprite.setPosition(x, y); //������ � ������� (x, y). 

			if (health <= 0) { life = false; }//���� ������ ������ 0, ���� ����� 0, �� ������� 
		}
	}