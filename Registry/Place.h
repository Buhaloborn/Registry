#pragma once
#include <SFML/Graphics.hpp> 
using namespace sf;
class Place
{
	public:
		Texture texture;
		Sprite sprite;
		float x, y;int w, h;
		float CurrentFrame;
		
		Place(Image &image, float X, float Y, int W, int H);
		
		bool isOpen;
		void update(float time);
		
		FloatRect getRect();
};
