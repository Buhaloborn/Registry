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
	BulletImage.loadFromFile("images/sandal.png");


	Image EnemyImage;
	EnemyImage.loadFromFile("images/enemy.png");

	Image WindowImage;
	WindowImage.loadFromFile("images/window.png");

	Player p(heroImage, 364, 453, 40, 86, "Player");
		
	list<Enemy*>  Enemies; //список врагов
	list<Enemy*>::iterator ite;
	list<Bullet*>  Bullets; //список пуль
	list<Bullet*>::iterator itr;
	list <Place*> windows;
	list <Place*>::iterator it;

	const int W_COUNT = 6; //максимальное количество окон в игре
	int wCount = 0; //текущее количество окон в игре
	const int E_COUNT = 6; //максимальное количество врагов в игре
	int eCount = 0;

	for (int i = 0; i < E_COUNT; i++)
	{
		float xr = 150 + rand() % 500; //случайная координата врага на поле игры по оси “x”
		float yr = 150 + rand() % 350; //случайная координата врага на поле игры по оси “y”
		Enemies.push_back(new Enemy(EnemyImage, xr, yr, 40, 86, "Psycho")); //создаем врагов и помещаем в список
		eCount += 1; //увеличили счётчик врагов
	}

	for (int i = 0;i < W_COUNT;i++)
	{
		float xr = 50 + 122 * i;
		float yr = 50; //задаём позицию окон
		windows.push_back(new Place(WindowImage, xr, yr, 60, 75)); //вносим их в список
		wCount++;
	}

	Clock clock, test,enemyclock;
	Clock gameTimeClock;

	float gameTime = 0; 
	float createBullet = 0;
	// Основной (бесконечный) цикл 

	while (window.isOpen())
	{
		int time = clock.getElapsedTime().asMicroseconds();

		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();
		clock.restart();
		time = time / 800;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();//Закрываем окно, если событие “Closed” 
		}

		///////////////////////////////////Оживление объектов/////////////////////////////////////
		p.update(time, p.x, p.y); //Игрока

		for (ite = Enemies.begin(); ite != Enemies.end(); ite++) //Врагов
		{
			(*ite)->update(time, p.x, p.y); //запускаем метод update()
		}

		for (it = windows.begin(); it != windows.end(); it++) //Окон
		{
			(*it)->update(time);//применяем метод update(time) класса Place для объектов из списка
		}
		
		for (itr = Bullets.begin(); itr != Bullets.end(); itr++) //Пуль

		{
			(*itr)->update(time, p.x, p.y); //запускаем метод update() для пуль 
		}

		/////////////////Смена направления///////////		
		for (ite = Enemies.begin(); ite != Enemies.end(); ite++)
		{
			float switchdir;
			switchdir = rand() % 50;
			if (switchdir > 48)
			{
				(*ite)->direction = rand() % 3;
			}
		}

		/////////////Генерация выстрелов/////////////////////////////////////////

		if (p.PlayerScore > 0)
		{
			int testTime = test.getElapsedTime().asSeconds();
			if (createBullet < 300) {
				createBullet += testTime;
			}
			else
			{
				for (ite = Enemies.begin(); ite != Enemies.end(); ite++)
				{	
					int switchdirbul = rand() % 10;
					if (switchdirbul > 3)
					Bullets.push_back(new Bullet(BulletImage, (*ite)->x, (*ite)->y, 16, 16, "Bullet",rand()%(7))); //добавляем в список Bullets пулю

				}
				createBullet = 0;
				test.restart();
			}
		}

		///////////////////////////////////// Пересечения/////////////////////////////////////////////////////////
		////////////////////////С окнами////////////////////////////
		for (it = windows.begin(); it != windows.end(); it++) //С окнами//
			if (p.getRect().intersects((*it)->getRect()) && (*it)->isOpen)
			{																	//проверка пересечения игрока с окном
				p.PlayerScore += 80;											//начисление очков, если окно открыто
				(*it)->CurrentFrame = 1;										//закрытие окна после получения очков
			}
		/////////////////////////Игрока со снарядами //////////////////////////////////
		if (p.life == true) {												//если игрок жив
			for (itr = Bullets.begin(); itr != Bullets.end(); itr++) {						//бежим по списку врагов
				if ((*itr)->getRect().intersects(p.getRect()) && ((*itr)->name == "Bullet"))
				{
					p.PlayerScore -= 50; //снятие очков
					(*itr)->life = false;
				}
			}
		}
		///////////////Врага и игрока/////////////// 
		if (p.life == true) //если игрок жив
		{															
			int ToW = enemyclock.getElapsedTime().asMilliseconds();
			if (ToW < 300) {
			}
				else
				{
					for (ite = Enemies.begin(); ite != Enemies.end(); ite++) //бежим по списку врагов
					{
						if ((p.getRect().intersects((*ite)->getRect())) && ((*ite)->name == "Psycho") && p.invinc == false)
						{
							p.PlayerScore -= 100; //забираем очки
							p.invinc = true; //даем временную неуязвимость
						}
					}
					enemyclock.restart();
				}
				p.invinc = false;
		}


		////////////////Очистка контейнера с пулями/////////////
		for (itr = Bullets.begin(); itr != Bullets.end(); )				//проходимся от начала до конца
		{																//если этот объект мертв, то удаляем его
			Bullet *t = *itr;
			t->update(time,p.x,p.y);
			if (t->life == false)
			{
				itr = Bullets.erase(itr);
				delete t;
			}
				else
				itr++; //и идем итератором к след объекту.
		}
	
		window.clear(); 

		Font font1, font2;
		font1.loadFromFile("Fonts/GothaProBla.otf");
		font2.loadFromFile("Fonts/GothaProMed.otf");
		Text bigtext("", font1, 80),//создаем объект текст. Помещаем в объект текст-строку, шрифт, размер
			smalltext("", font2, 40),//шрифта(в пикселях)
			rule1("", font2, 25), rule2("", font2, 25), rule3("", font2, 25), //big text
			ruleOne("", font1, 80), ruleTwo("", font1, 80), ruleThree("", font1, 80); //small text

		//////////////////////////////////Карта//////////////////////////////////////////
		for (int i = 0; i < Height_Map; i++)
			for (int j = 0; j < Width_Map; j++)
			{
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(0, 0, 32, 32));//если встретили 0, то рисуем 1й квадратик 
				if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(32, 0, 32, 32)); //если встретили пробел, то рисуем 2й квадратик 

				if ((TileMap[i][j] == '-')) s_map.setTextureRect(IntRect(64, 0, 32, 32));//если встретили -, то рисуем черноту

				if ((TileMap[i][j] == 'E')) s_map.setTextureRect(IntRect(96, 0, 32, 32));// рисуем EXIT
				if ((TileMap[i][j] == 'X')) s_map.setTextureRect(IntRect(128, 0, 32, 32));//
				if ((TileMap[i][j] == 'I')) s_map.setTextureRect(IntRect(160, 0, 32, 32));//
				if ((TileMap[i][j] == 'T')) s_map.setTextureRect(IntRect(192, 0, 32, 32));//
				
				s_map.setPosition(j * 32, i * 32);											//раскладываем квадратики в карту. 
				window.draw(s_map);													
			}
		
		///////////////////////////////Отрисовка объектов///////////////////////////////////////////////
		

		for (it = windows.begin();it != windows.end();it++) //окна
		{
			window.draw((*it)->sprite);
		}

		for (ite = Enemies.begin(); ite != Enemies.end(); ite++)
		{
			window.draw((*ite)->sprite); //рисуем enemies объекты
		}
		window.draw(p.sprite); //игрок

		///////////////////////////////draw bullets//////////////////////////////////


		for (itr = Bullets.begin(); itr != Bullets.end(); itr++)
		{
			if ((*itr)->life) //если пули живы
				window.draw((*itr)->sprite); //рисуем объекты
		}
		

		/////////Снятие очков со временем/////
		if (p.PlayerScore > 0)
			p.PlayerScore -= 0.02;	//со временем очки сгорают, если счёт дойдет до нуля, игра окончена
		if (p.PlayerScore < 0)
			p.PlayerScore = 0;

		////// Конец игры/////////
		ostringstream playerScoreString, timeString; // объявили переменную

		if (p.PlayerScore <= 0) 
		{
			p.life = false;
			for (ite = Enemies.begin(); ite != Enemies.end(); ite++)
			(*ite)->life = false;
			for (itr = Bullets.begin(); itr != Bullets.end(); itr++)
				(*itr)->life = false;
			for (it = windows.begin();it != windows.end();it++)
			{
				(*it)->CurrentFrame = 1;
			}
		}
		

		playerScoreString << int (p.PlayerScore); //занесли в нее число очков, то есть формируем строку
		
		bigtext.setString(playerScoreString.str()); //задаем строку тексту и вызываем
		smalltext.setString("POINTS");              //сформированную выше строку методом .str()
		
		bigtext.setPosition(800, 20);//задаем позицию текста
		smalltext.setPosition(800, 100);
		
		window.draw(bigtext);//рисуем этот текст
		window.draw(smalltext);
		
		rule1.setString("SANDAL"); rule2.setString("WINDOW"), rule3.setString("ENEMY");
		ruleOne.setString("-50"); ruleTwo.setString("+80"); ruleThree.setString("-100");
		ruleOne.setPosition(800, 270);  window.draw(ruleOne);
		ruleTwo.setPosition(800, 370);  window.draw(ruleTwo);
		ruleThree.setPosition(800, 470);  window.draw(ruleThree);
		rule1.setPosition(800, 260);  window.draw(rule1);
		rule2.setPosition(800, 360);  window.draw(rule2);
		rule3.setPosition(800, 460);  window.draw(rule3);

		window.display();  
	}
	return 0;
}