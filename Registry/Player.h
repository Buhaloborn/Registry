#pragma once
#include "Entity.h"

////////////////////////////�����//////////////////////// 
class Player :public Entity {
public:
	int playerScore;//��� ���������� ����� ���� ������ � ������ 
	Player(Image &image, float X, float Y, int W, int H, string Name) :Entity(image, X, Y, W, H, Name)
	{
		playerScore = 0;
		state = stay;
		if (name == "Player1")
		{
			//������ ������� ���� ������������� ��� ������ ������ ������. IntRect � ��� ���������� ����� 
			sprite.setTextureRect(IntRect(40, 172, w, h));
		}
	}
	void control();
	void update(float time); //����� "���������/����������" ������� ������. 
};
