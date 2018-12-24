#include "Place.h"
#include <cstdlib>
#include "Entity.h"
//////////////////////////////////////////////////////
Place::Place(Image &image, float X, float Y, int W, int H)
{
	x = X; y = Y; //���������� ��������� ������� 
	w = W; h = H;
	CurrentFrame = 0;
	sprite.setTextureRect(IntRect(0, 0, w, h));
	texture.loadFromImage(image); //������� ����������� � �������� 
	sprite.setTexture(texture); //�������� ������ ��������� 
	sprite.setPosition(x, y);
}

void Place::update(float time)
{
	//act();
	CurrentFrame += (0.0002)*time;
	if (CurrentFrame > 2) CurrentFrame -= 2;
	sprite.setTextureRect(IntRect(60 * int(CurrentFrame), 0, 60, 75));
	if (int(CurrentFrame) % 2 == 0) 
		isOpen = true; //���� �������
	else
		isOpen = false; //���� �������
}