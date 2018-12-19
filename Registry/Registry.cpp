//тестовый код урока №1 
#include <SFML/Graphics.hpp> 
#include <sstream>
#include <iostream>
#include "map.h"

using namespace sf;
using namespace std;

////////////////////////////Абстрактная сущность//////////////////////// 
class Entity {
public:
	enum { left, right, up, down, stay } state;// тип перечисления - состояние объекта 
	float dx, dy, x, y, speed, moveTimer; 
	int w, h, health; //хп игрока 
	bool life; //жизнь, логическая 
	Texture texture;//сфмл текстура 
	Sprite sprite;//сфмл спрайт 
	float CurrentFrame;//хранит текущий кадр 
	string name;//враги могут быть разные, врагов можно различать по именам 
	//каждому можно дать свое действие в update() в зависимости от имени 

	Entity(Image &image, float X, float Y, int W, int H, std::string Name) {
		x = X; y = Y; //координата появления спрайта 
		w = W; h = H;
		name = Name;
		moveTimer = 0;
		dx = 0; dy = 0;
		speed = 0;
		CurrentFrame = 0;
		health = 100;
		life = true; //сущность жива
		texture.loadFromImage(image); //заносим изображение в текстуру 
		sprite.setTexture(texture); //заливаем спрайт текстурой 
	}

	FloatRect getRect() {//метод получения прямоугольника. его коорд, размеры (шир,высот). 
		FloatRect FR(x, y, w, h); 
		return FR;
	}
	virtual void update(float time) = 0;
};

////////////////////////////Игрок//////////////////////// 
class Player :public Entity {
public:
	int playerScore;//эта переменная может быть только у игрока 

	Player(Image &image, float X, float Y, int W, int H, string Name) :Entity(image, X, Y, W, H, Name) {
		playerScore = 0;
		state = stay;
		if (name == "Player1") {
			//Задаем спрайту один прямоугольник для вывода одного игрока. IntRect – для приведения типов 
			sprite.setTextureRect(IntRect(40, 172, w, h));
		}
	}

	void control() {
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			state = left;
			speed = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			state = right;
			speed = 0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			state = up;
			speed = 0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			state = down;
			speed = 0.1;
		}
	}


	void update(float time) //метод "оживления/обновления" объекта класса. 
	{
		if (life) {//проверяем, жив ли герой 
			control();//функция управления персонажем 
			switch (state)//делаются различные действия в зависимости от состояния 
			{
			case right: {//состояние идти вправо 
				dx = speed; dy = 0;
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setScale(1, 1);
				sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 0, 40, 86));
				break;
			 }
			case left: {//состояние идти влево 
				dx = -speed; dy = 0;
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setScale(-1, 1);
				sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 0, 40, 86));
				break;
			 }
			case up: {//идти вверх 
				dy = -speed; dx = 0;
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 172, 40, 86));
				break;
			 }
			case down: {//идти вниз 
				dy = speed; dx = 0;
				CurrentFrame += 0.0065*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 86, 40, 86));
				break;
			 }
			case stay: {//стоим 
				dy = speed;
				dx = speed;
				break;
			 }
			}

			x += dx * time; //движение по “X” 
			y += dy * time; //движение по “Y” 

			speed = 0; //обнуляем скорость, чтобы персонаж остановился. 
			state = stay; //состояние - стоим 

			sprite.setPosition(x, y); //спрайт в позиции (x, y). 

			if (health <= 0) { life = false; }//если жизней меньше 0, либо равно 0, то умираем 
		}
	}
};

////////////////////////////Псих//////////////////////// 
class Enemy :public Entity {
public:
	int direction;//направление движения врага 
	Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name) {
		if (name == "Psycho") {
			//Задаем спрайту один прямоугольник для 
			//вывода одного игрока. IntRect – для приведения типов 
			sprite.setTextureRect(IntRect(0, 0, w, h));
			direction = rand() % (3); //Направление движения врага задаём случайным образом через генератор случайных чисел 
			speed = 0.1;//этот объект всегда двигается 
			dx = speed;
		}
	}

	void update(float time)
	{
		if (name == "Psycho") {

			if (life) {
				switch (direction)//делаются различные действия в зависимости от состояния 
				{
					case 0: {//состояние идти вправо 
						dx = speed; dy = 0;
						CurrentFrame += 0.0065*time;
						if (CurrentFrame > 4) CurrentFrame -= 4;
						sprite.setScale(1,1);
						sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 0, 40, 86));
						break;
					}
					case 1: {//состояние идти влево 
						dx = -speed; dy = 0;
						CurrentFrame += 0.0065*time;
						if (CurrentFrame > 4) CurrentFrame -= 4;
						sprite.setScale(-1, 1);
						sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 0, 40, 86));
						break;
					}
					case 2: {//идти вверх 
						dy = -speed; dx = 0;
						CurrentFrame += 0.0065*time;
						if (CurrentFrame > 4) CurrentFrame -= 4;
						sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 172, 40, 86));
						break;
					}
					case 3: {//идти вниз 
						dy = speed; dx = 0;
						CurrentFrame += 0.0065*time;
						if (CurrentFrame > 4) CurrentFrame -= 4;
						sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 86, 40, 86));
						break;
					}
				}

				x += dx * time; //движение по “X” 
				y += dy * time; //движение по “Y” 

				sprite.setPosition(x, y); //спрайт в позиции (x, y). 

				if (health <= 0) { life = false; }//если жизней меньше 0, либо равно 0, то умираем 
			}
		}
	}
};




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

	Image EnemyImage;
	EnemyImage.loadFromFile("images/enemy.png");

	Player p(heroImage, 600, 300, 40, 86, "Player1");
	Enemy psycho(EnemyImage, 150, 150, 40, 86, "Psycho");

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
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(0, 0, 32, 32));//если встретили 0, то рисуем 1й квадратик 

				if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(32, 0, 32, 32)); //если встретили пробел, то рисуем 2й квадратик 

				if ((TileMap[i][j] == 'X')) s_map.setTextureRect(IntRect(96, 0, 32, 32));//если встретили X, то рисуем 4й квадратик (дверь)

				s_map.setPosition(j * 32, i * 32);//раскладываем квадратики в карту. 

				window.draw(s_map);//рисуем квадратики на экран 
			}

		window.draw(p.sprite);
		window.draw(psycho.sprite);

		window.display();  
	}

	return 0;
}