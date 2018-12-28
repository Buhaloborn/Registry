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

	Player p(heroImage, 492, 453, 40, 86, "Player");
		
	
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
									   //создаем врагов и помещаем в список
		Enemies.push_back(new Enemy(EnemyImage, xr, yr, 40, 86, "Psycho"));
		eCount += 1; //увеличили счётчик врагов
	}

	for (int i = 0;i < W_COUNT;i++)
	{
		float xr = 50 + 172 * i;
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
		while (window.pollEvent(event)) //Опрос событий 
		{
			if (event.type == Event::Closed)
				window.close();//Закрываем окно, если событие “Closed” 
		}

		/////////////////////////////////////////Прорисовка выстрелов////////////////////////////////////////////////////////////




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


		/////////////Рандомные выстрелы/////////////////////////////////////////

		if (p.PlayerScore > 0)
		{
			int testTime = test.getElapsedTime().asSeconds();
			//	cout << testTime <<"       " << createBullet << endl;
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
		///////////////////////////////////Player download/////////////////////////////////////
		p.update(time, p.x, p.y);

		for (ite = Enemies.begin(); ite != Enemies.end(); ite++)
		{
			(*ite)->update(time, p.x, p.y); //запускаем метод update()
		}

		//рисуем врагов
		for (ite = Enemies.begin(); ite != Enemies.end(); ite++)
		{
			window.draw((*ite)->sprite); //рисуем enemies объекты
		}

		/////////////////////////////////////////////Загрузка пули/////////////////////////////
		for (itr = Bullets.begin(); itr != Bullets.end(); itr++)

		{
			(*itr)->update(time, p.x, p.y); //запускаем метод update() для пуль 
		}


		///////////////////////////////////// Windoows actions/////////////////////////////////////////////////////////
		for (it = windows.begin(); it != windows.end(); it++)
		{
			(*it)->update(time);//применяем метод update(time) класса Place для объектов из списка
		}

		if (p.PlayerScore > 0)
			p.PlayerScore -= 0.02;	//со временем очки сгорают, если счёт дойдет до нуля, игра окончена
		if (p.PlayerScore < 0)
			p.PlayerScore = 0;

		////////////////////////////////пересечение с окном//////////////////////////////////
		for (it = windows.begin(); it != windows.end(); it++)
			if (p.getRect().intersects((*it)->getRect()) && (*it)->isOpen)

			{																	//проверка пересечения игрока с окном
				p.PlayerScore += 80;											//начисление очков, если окно открыто
				(*it)->CurrentFrame = 1;										//закрытие окна после получения очков
			}
		//////////////////////////////////Проверка пересечения ИГрока с тапками /////////////////////////////////////////////////

		if (p.life == true) {												//если игрок жив
			for (itr = Bullets.begin(); itr != Bullets.end(); itr++) {						//бежим по списку врагов
				if ((*itr)->getRect().intersects(p.getRect()) && ((*itr)->name == "Bullet"))
				{
					p.PlayerScore -= 50;
					(*itr)->life = false;

				}
			}
		}
		/////////////// на пересечение врага и перса 
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
							p.PlayerScore -= 100;
							p.invinc = true;
						}
					}
					enemyclock.restart();
				}
				p.invinc = false;
		}
		for (itr = Bullets.begin(); itr != Bullets.end(); )				//говорим что проходимся от начала до конца
		{																// если этот объект мертв, то удаляем его
			Bullet *t = *itr;
			t->update(time,p.x,p.y);

			if (t->life == false)
			{
				itr = Bullets.erase(itr);
				delete t;
			}
				else
				itr++;													//и идем курсором (итератором) к след объекту.
		}
		///////////////////////////////////////////////////////////////////////////////////
		window.clear(); 

		Font font;
		font.loadFromFile("Fonts/GothaProMed.otf");
		Text text("", font, 20);												//создаем объект текст. Помещаем в объект текст-строку, шрифт, размер
																				//шрифта(в пикселях)


		//////////////////////////////////Карта//////////////////////////////////////////
		for (int i = 0; i < Height_Map; i++)
			for (int j = 0; j < Width_Map; j++)
			{
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(0, 0, 32, 32));//если встретили 0, то рисуем 1й квадратик 

				if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(32, 0, 32, 32)); //если встретили пробел, то рисуем 2й квадратик 

				if ((TileMap[i][j] == 'X')) s_map.setTextureRect(IntRect(96, 0, 32, 32));//если встретили X, то рисуем 4й квадратик (дверь)

				s_map.setPosition(j * 32, i * 32);											//раскладываем квадратики в карту. 

				window.draw(s_map);															//рисуем квадратики на экран 
			}
		//////////////////////////////////////////////////////////////////////////////

		for (it = windows.begin();it != windows.end();it++)
		{
			window.draw((*it)->sprite);
		}
		
		window.draw(p.sprite);
		///////////////////////////////////////////рисуем врагов/////////////////////


		for (ite = Enemies.begin(); ite != Enemies.end(); ite++)
		{
			window.draw((*ite)->sprite); //рисуем enemies объекты
		}
		///////////////////////////////draw bullets//////////////////////////////////

		
		for (itr = Bullets.begin(); itr != Bullets.end(); itr++)
		{
			if ((*itr)->life) //если пули живы
				window.draw((*itr)->sprite); //рисуем объекты
		}
		
		////// stop moving
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
		
		ostringstream playerScoreString; // объявили переменную

		playerScoreString << int (p.PlayerScore); //занесли в нее число очков, то есть формируем строку
		text.setString("Points: " + playerScoreString.str()); //задаем строку тексту и вызываем
																	 //сформированную выше строку методом .str()
		text.setPosition(500, 500);//задаем позицию текста
		window.draw(text);//рисуем этот текст
		
		window.display();  
	}

	return 0;
}