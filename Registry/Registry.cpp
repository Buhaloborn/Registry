﻿//тестовый код урока №1 
#include <SFML/Graphics.hpp> 
#include <sstream>
#include <iostream>
#include "map.h"
#include "Player.h"
#include "Enemy.h"

using namespace sf;
using namespace std;

int main()
{ 
	VideoMode desktop = VideoMode::getDesktopMode();
	RenderWindow window(VideoMode(1280, 608, desktop.bitsPerPixel), "Registry");

	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	
	Image heroImage;
	heroImage.loadFromFile("images/hero.png");

	Image EnemyImage;
	EnemyImage.loadFromFile("images/enemy.png");

	Player p(heroImage, 600, 300, 96, 96, "Player1");
	Enemy psycho(EnemyImage, 150, 150, 96, 96, "Psycho");

	Clock clock;
	Clock gameTimeClock;
	int gameTime = 0;
	// Основной (бесконечный) цикл 
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();

		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();

		clock.restart();
		time = time / 800;
		Event event; 
		while (window.pollEvent(event)) //Опрос событий 
		{
			if (event.type == Event::Closed)
				window.close();//Закрываем окно, если событие “Closed” 
		}

		p.update(time);
		psycho.update(time);

		window.clear(); 

		//////////Карта///////////
		for (int i = 0; i < Height_Map; i++)
			for (int j = 0; j < Width_Map; j++)
			{
				if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(0, 0, 32, 32)); //если встретили пробел, то рисуем 1-й квадратик 
				 
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));//если встретили 0, то рисуем 3й квадратик 

				s_map.setPosition(j * 32, i * 32);//раскладываем квадратики в карту. 

				window.draw(s_map);//рисуем квадратики на экран 
			}

		window.draw(p.sprite);
		window.draw(psycho.sprite);

		window.display();  
	}

	return 0;
}