#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

////////////////////////////�����//////////////////////// 
class Player : public Entity {
public:
	float PlayerScore;//��� ���������� ����� ���� ������ � ������ 
	bool invinc ;
	Player(Image &image, float X, float Y, int W, int H, string Name) :Entity(image, X, Y, W, H, Name)
	{
		invinc = false;
		PlayerScore = 1000;
		state = stay;
		if (name == "Player")
		{
			//������ ������� ���� ������������� ��� ������ ������ ������. IntRect � ��� ���������� ����� 
			sprite.setTextureRect(IntRect(40, 172, w, h));
		}
	}

	void checkCollisionWithMap(float Dx, float Dy);
	void control();
	void update(float time); //����� "��������� ����������" ������� ������. 
};
#endif