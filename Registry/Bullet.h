#pragma once
#include "entity.h"

class Bullet :public Entity {//����� ����
public:
	int direction;//����������� ����
				  //�� ��� ��, ������ ����� � ����� ��������� ������ (int dir) 
				  //��� ������� ����������� ����� ����
	Bullet(Image &image, float X, float Y, int W, int H, std::string  Name, int dir) :Entity(image, X, Y, W, H, Name) {
		if (name == "Bullet") {
			x = X;
			y = Y;
			direction = dir;
			speed = 0.4;
			w = h = 16;
			life = true;
		}
		//���� ������������� � ������������

	}

	void update(float time);
};