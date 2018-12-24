#include <sstream>
#include <iostream>
#include <list>
#include "Player.h"
#include "Enemy.h"
#include "Place.h"
#include "map.h"
#include "bullet.h"

int main()
{ 
	VideoMode desktop = VideoMode::getDesktopMode();
	RenderWindow window(VideoMode(1024, 576, desktop.bitsPerPixel), "Registry");

	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	
	Image heroImage;
	heroImage.loadFromFile("images/hero.png");

	Image BulletImage;
	BulletImage.loadFromFile("images/bullet.png");


	Image EnemyImage;
	EnemyImage.loadFromFile("images/enemy.png");

	Image WindowImage;
	WindowImage.loadFromFile("images/window.png");

	Player p(heroImage, 600, 300, 40, 86, "Player");
	Enemy psycho(EnemyImage, 500, 400, 40, 86, "Psycho");
	Place w1(WindowImage, 50, 50, 60, 75), w2(WindowImage, 500, 500, 60, 75);
	
	
	std::list<Entity*>  Bullets; //список пуль
	std::list<Entity*>::iterator it;


	Clock clock, test;
	Clock gameTimeClock;
	float gameTime = 0; int testTime = gameTime;
	// Основной (бесконечный) цикл 
	while (window.isOpen())
	{
		int time = clock.getElapsedTime().asMicroseconds();

		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds(); 
		testTime = test.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;
		Event event; 
		while (window.pollEvent(event)) //Опрос событий 
		{
			if (event.type == Event::Closed)
				window.close();//Закрываем окно, если событие “Closed” 

			if (event.type == rand())
			{
				if (event.key.code == rand())
				{
					//добавляем в список Bullets пулю
					Bullets.push_back(new Bullet(BulletImage, p.x, p.y, 16, 16, "Bullet", p.state));
				}
			}

		}

		p.update(time);
		psycho.update(time);
		w1.update(time);

		for (it = Bullets.begin(); it != Bullets.end(); it++)
		{
			(*it)->update(time); //запускаем метод update()
		}

		
		for (it = Bullets.begin(); it != Bullets.end(); )//говорим что проходимся от начала до конца
		{// если этот объект мертв, то удаляем его
			if ((*it)->life == false) { it = Bullets.erase(it); }
			else
				it++; //и идем курсором (итератором) к след объекту.
		}


		window.clear(); 

		Font font;
		font.loadFromFile("GothaProMed.otf");
		Text text("", font, 20);//создаем объект текст. Помещаем в объект текст-строку, шрифт, размер
								// шрифта(в пикселях)
		//покрасили текст в красный.
								  //если убрать эту строку, то по умолчанию текст белый


		//////////Карта///////////
		for (int i = 0; i < Height_Map; i++)
			for (int j = 0; j < Width_Map; j++)
			{
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(0, 0, 32, 32));//если встретили 0, то рисуем 1й квадратик 

				if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(32, 0, 32, 32)); //если встретили пробел, то рисуем 2й квадратик 

				if ((TileMap[i][j] == 'X')) s_map.setTextureRect(IntRect(96, 0, 32, 32));//если встретили X, то рисуем 4й квадратик (дверь)

				s_map.setPosition(j * 32, i * 32);//раскладываем квадратики в карту. 

				window.draw(s_map);//рисуем квадратики на экран 
			}

		window.draw(w1.sprite);
		window.draw(p.sprite);
		window.draw(psycho.sprite);

		
		for (it = Bullets.begin(); it != Bullets.end(); it++)
		{
			window.draw((*it)->sprite); //рисуем enemies объекты
		}


		ostringstream playerScoreString; // объявили переменную
		playerScoreString << p.health; //занесли в нее число очков, то есть формируем строку
		text.setString("Points: " + playerScoreString.str()); //задаем строку тексту и вызываем
																	 //сформированную выше строку методом .str()
		text.setPosition(500, 500);//задаем позицию текста
		window.draw(text);//рисуем этот текст
		
		window.display();  
	}

	return 0;
}