#pragma once
#include "entity.h"

class Bullet :public Entity {//����� ����
public:
	int direction;//����������� ����
				  //�� ��� ��, ������ ����� � ����� ��������� ������ (int dir) 
				  //��� ������� ����������� ����� ����
	Bullet(Image &image, float X, float Y, int W, int H, std::string  Name, int dir) :Entity(image, X, Y, W, H, Name) {
		x = X;
		y = Y;
		direction = dir;
		speed = 0.8;
		w = h = 16;
		life = true;
		//���� ������������� � ������������

	}

	void update(float time);
};