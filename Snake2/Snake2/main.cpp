#include <SFML/Graphics.hpp>
#include <time.h>
#include <sstream>
#include <iostream>
using namespace sf;

int Fruct = 0;  // Переменная отвечающая за наш счёт;
int pix = 20;  // Переменная с количеством пикселей в ондом блоке. Текстуры = 20/20
int dir, num = 4; // Переменные для хранения направления и длинны хврсиа змейки;
int W = 30, H = 30;  // Количество блоков, составляющих наше поле;
int w = pix * W; // Общее кол-во пикселей на экране. Кол-во пикселей в текстуре 1 блока на кол-во блоков по x;
int h = pix * H; // Кол-во пикселей в текстуре 1 блока на кол - во блоков по y;
bool gamestart = false; // Переменная для запуска игры;
Texture t1, t2, t3; // Переменные для будующих текстур;

struct Snake
{
	int x, y;
} s[100]; // массив, координатой которого являются х и у;

struct Fruct
{
	int x, y; //  Переменная f, с координатами х, у; 
}f;

void gameover()  // Функция для завершения игры;
{
	std::cout << "ВЫ ПРОИГРАЛИ!\nВаш счёт: "<<Fruct<<std::endl; // Выводит сообщение о проигрыше и набранных очках;
	system("PAUSE");  // Затем, после нажатия клавиши, заркывает программу;
	exit(1);
}
void Move() // Функция движения змейки и логики;
{
	for (int i = num; i > 0; --i)  // для i = длинна хвоста; i > 0; отнимаем i; то есть проходимся по змейке, и двигаем поочереди хвост;
	{
		s[i].x = s[i - 1].x; // Последний элемент хвоста по х встаёт на место предпоследнего, тот в свою очередб на место следующего, и тд;
		s[i].y = s[i - 1].y; // Последний элемент хвоста по у встаёт на место предпоследнего, тот в свою очередб на место следующего, и тд;
	}

	if (dir == 0) s[0].y += 1;// Если направление == 0, у += 1 то есть Вверх; 
	if (dir == 1) s[0].x -= 1;// Если направление == 1, x -= 1 то есть Налево; 
	if (dir == 2) s[0].x += 1;// Если направление == 2, х += 1 то есть Направо;
	if (dir == 3) s[0].y -= 1;// Есди направление == 3, у -= 1 то есть Вниз;

	if ((s[0].x == f.x) && (s[0].y == f.y))// Если х и у координаты головы змейки == х и у координатам фрукта то: (Или проще говоря:)Если голова столкнулась с фруктом то:
	{
		Fruct++;  // + 1 К счётчику фруктов
		num++;  // + 1 К хвосту
		f.x = rand() % W; // Рандомим следующую координату х для фрукта
		f.y = rand() % H;  // Рандомим следующую координату у для фрукта 
	}

	if (s[0].x > W) s[0].x = 0;  if (s[0].x < 0) s[0].x = W; // Если голова змейки вышла за пределы поля, 
	if (s[0].y > H) s[0].y = 0;  if (s[0].y < 0) s[0].y = H; // то телепортируем её на противооложную сторону;
	for (int i = 1; i < num; i++)  // Проверяем, столкнулась ли змейка сама с собой; 
		if (s[0].x == s[i].x && s[0].y == s[i].y) {
			gameover();
		}
}

int main()
{	
	setlocale(LC_ALL, "RUSSIAN"); // Задаём русский язык;
	std::cout << "Это игра 'Змейка на SFML'!\n";
	std::cout << "Выберите сложность: \n 1 : Легко \n 2 : Нормально \n 3 : Сложно \n";
	int diff; // Переменная сложности;
	std::cin >> diff; // Вводим сложность;
	if (diff == 1){ // Если сложность == "Легко" то:
        W = 15;   // Указывыаем кол-во блоков на 15/15;
        H = 15;
	    w = pix * W; // Заново указываем ширину и высоту в впикселях;
		h = pix * H;
	    gamestart = true; // Стартуем игру;
		 }
	 else if (diff==2)  gamestart = true; // Если сложность == "Нормально" то стартуем игру; (Все переменные по умолчанию стоят на уровне (Нормально);
	 else if (diff==3){ // Всё тоже самое что и в "Легко", но:
		 W = 50;  // Задаём поле 50/50 блоков;
		 H = 50;
		 w = pix * W;
		 h = pix * H;
		 gamestart = true;
	 }
	 else if (diff == 123) { // Секретная сложность ничем не отличается от сложной, за исключением скорости змейки;
		 std::cout << "Вы нашли секрет!";
		 W = 50;
		 H = 50;
		 w = pix * W;
		 h = pix * H;
		 gamestart = true;
	 }
	 else {
		 std::cout << "Неверно задана сложность!\n"; // Условие для неверно введённой сложности;
		 system("PAUSE");
	 }

		Font font; // Задаём переменную для шрифта;
		font.loadFromFile("arial.ttf"); // Загружаем шрифт из папки;
		Text txt;  // Задаём переменную для текста;
		txt.setFont(font); // Выставляем загруженный ранее шрифт;
		txt.setPosition(10, 10); // Указываем позицию текста (Левый верхний угол);
		txt.setCharacterSize(24); // Указываем размер текста;
		txt.setStyle(Text::Bold); // Выставляем стиль текста "Жирный";
		if (gamestart == true) {  // Если запустили игру: ... ;
			RenderWindow window(VideoMode(w, h), "Snake"); // Создаём окно с помошью библиотеки SFML;
			switch (diff) of:{ // В зависимотси от сложности загрудаем разные текстуры;
			case 1: {
				t1.loadFromFile("images/Block 1.png"); // Грузим блок 1 (Зелёный);
				t2.loadFromFile("images/Snake 1.png"); // Грузим Тело Змейки;
				t3.loadFromFile("images/Fruct 1.png"); // Грузим красные фруткы;
				break;  
		        	}
			case 2:
			   {
				t1.loadFromFile("images/Block 2.png"); // Грузим жёлтые текстуры;
				t2.loadFromFile("images/Snake 2.png");
				t3.loadFromFile("images/Fruct 2.png"); // И зелёные фрукты;
				break;
		       }
			   case 3: {
				t1.loadFromFile("images/Block 3.png"); // Грузим красные текстуры;
				t2.loadFromFile("images/Snake 3.png");
				t3.loadFromFile("images/Fruct 3.png"); // И жёлтые фркуты;
				break;
			   }
			   case 123: {
				t1.loadFromFile("images/Block 3.png"); // Грузим красные текстуры;
				t2.loadFromFile("images/Snake 3.png");
				t3.loadFromFile("images/Fruct 3.png"); // И жёлтые фркуты;
				break;
			   }
			}

			Sprite sprite1(t1); //Делаем спрайты из загруженых выше текстур;
			Sprite sprite2(t2);
			Sprite fsprite(t3);
			Clock clock;  // Переменная часов;
			float timer = 0, delay = 0.15; // Переменная для хранения времени,(Понадобится ниже); и скорости обновления; 
			if (diff == 2) delay = 0.1; // Нормально (Выше Легко);
			if (diff == 3) delay = 0.050; // Сложно;
			if (diff == 123) delay = 0.025; // Секретная сложность Insane;
			f.x = rand() % W; // Рандомим стартовую позицию для х фрукта;
			f.y = rand() % H; // Рандомим стартовую позицию для y фрукта;

			while (window.isOpen())  // Обязательное условие для окна SFML;
			{
				float time = clock.getElapsedTime().asSeconds();  // Вовзращение времени в переменную как секунды;
				clock.restart(); // Рестрт часов;
				timer += time; // Сохраяет прошедшее время;
				// Таким образом, указываем 1 шаг в переменной delay, возвращаем время в секундах в переменную time, перезапускаем часы и, сохраняем прошедшее время, таким образом делая 1 шаг;
				Event event;  // Обязательный ивент в окне SFML;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)  // Нужно для создания окна в SFML;
						window.close();
				}

				if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) dir = 1;  // Считываем нажатия, стрелочек и AWSD;
				if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D))))  dir = 2;  // Задавая пременной направления направление, 
				if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) dir = 3;  // Расписаное в функции Move;
				if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::W)))) dir = 0;

				if (timer > delay) { timer = 0; Move(); }  // Обнуляем переменную timer, чтобы продолжать двигаться, и подключаем логику.

				window.clear();  // Обязательная функция окна SFML;

				for (int i = 0; i < W; i++) // От нуля до ширины с шагом pix квадратики по x;
					for (int j = 0; j < H; j++)  // От нуля до высоты с шагом pix квадратики по y;
					{
						sprite1.setPosition(i*pix, j*pix);  window.draw(sprite1);  // Задаём позицию для каждого квадратика, и риусем;
					}

				for (int i = 0; i < num; i++)  // Проходимся по всей змейке;
				{
					sprite2.setPosition(s[i].x*pix, s[i].y*pix);  window.draw(sprite2);  // Придаём ей текстуру и рисуем;
				}

				fsprite.setPosition(f.x*pix, f.y*pix);  // Задаём позицию для спрайта фрукта;
				window.draw(fsprite);  // Рисуем фрукт;
				std::ostringstream a;    // объявили переменную для Счётчика очков;
				a << Fruct;		//занесли в нее число очков, то есть формируем строку
				txt.setString("Score = " + a.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
				window.draw(txt);  // Рисуем этот текст;
				window.display();  // Выводим всё на экран;
			}
			return 0;
		}
	}