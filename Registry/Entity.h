#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

////////////////////////////����������� ��������//////////////////////// 
class Entity {
public:
	enum { left, right, up, down, stay } state;// ��� ������������ - ��������� ������� 
	float dx, dy, x, y, speed, moveTimer;
	int w, h;
	int health;
	bool life; //�����, ���������� 
	Texture texture;//���� �������� 
	Sprite sprite;//���� ������ 


	float CurrentFrame;//������ ������� ���� 
	string name;//����� ����� ���� ������, ������ ����� ��������� �� ������ 
				//������� ����� ���� ���� �������� � update() � ����������� �� ����� 

	Entity(Image &image, float X, float Y, int W, int H, std::string Name);

	FloatRect getRect(); //����� ��������� ��������������. ��� �����, ������� (���,�����). 

	virtual void update(float time) = 0;
};
