#pragma once
#include "Entity.h"

////////////////////////////����//////////////////////// 
class Enemy : public Entity {
public:
	int direction;//����������� �������� ����� 
	Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name) {
		if (name == "Psycho") {
			//������ ������� ���� ������������� ��� 
			//������ ������ ������. IntRect � ��� ���������� ����� 
			sprite.setTextureRect(IntRect(0, 0, w, h));
			direction = rand() % (4); //����������� �������� ����� ����� ��������� ������� ����� ��������� ��������� ����� 
			speed = 0.1;//���� ������ ������ ��������� 
			dx = speed;
		}
	}
	void checkCollisionWithMap(float Dx, float Dy);
	void update(float time);
};