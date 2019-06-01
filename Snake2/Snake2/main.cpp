#include <SFML/Graphics.hpp>
#include <time.h>
#include <sstream>
#include <iostream>
using namespace sf;

int Fruct = 0;  // ���������� ���������� �� ��� ����;
int pix = 20;  // ���������� � ����������� �������� � ����� �����. �������� = 20/20
int dir, num = 4; // ���������� ��� �������� ����������� � ������ ������ ������;
int W = 30, H = 30;  // ���������� ������, ������������ ���� ����;
int w = pix * W; // ����� ���-�� �������� �� ������. ���-�� �������� � �������� 1 ����� �� ���-�� ������ �� x;
int h = pix * H; // ���-�� �������� � �������� 1 ����� �� ��� - �� ������ �� y;
bool gamestart = false; // ���������� ��� ������� ����;
Texture t1, t2, t3; // ���������� ��� �������� �������;

struct Snake
{
	int x, y;
} s[100]; // ������, ����������� �������� �������� � � �;

struct Fruct
{
	int x, y; //  ���������� f, � ������������ �, �; 
}f;

void gameover()  // ������� ��� ���������� ����;
{
	std::cout << "�� ���������!\n��� ����: "<<Fruct<<std::endl; // ������� ��������� � ��������� � ��������� �����;
	system("PAUSE");  // �����, ����� ������� �������, ��������� ���������;
	exit(1);
}
void Move() // ������� �������� ������ � ������;
{
	for (int i = num; i > 0; --i)  // ��� i = ������ ������; i > 0; �������� i; �� ���� ���������� �� ������, � ������� ��������� �����;
	{
		s[i].x = s[i - 1].x; // ��������� ������� ������ �� � ����� �� ����� ��������������, ��� � ���� ������� �� ����� ����������, � ��;
		s[i].y = s[i - 1].y; // ��������� ������� ������ �� � ����� �� ����� ��������������, ��� � ���� ������� �� ����� ����������, � ��;
	}

	if (dir == 0) s[0].y += 1;// ���� ����������� == 0, � += 1 �� ���� �����; 
	if (dir == 1) s[0].x -= 1;// ���� ����������� == 1, x -= 1 �� ���� ������; 
	if (dir == 2) s[0].x += 1;// ���� ����������� == 2, � += 1 �� ���� �������;
	if (dir == 3) s[0].y -= 1;// ���� ����������� == 3, � -= 1 �� ���� ����;

	if ((s[0].x == f.x) && (s[0].y == f.y))// ���� � � � ���������� ������ ������ == � � � ����������� ������ ��: (��� ����� ������:)���� ������ ����������� � ������� ��:
	{
		Fruct++;  // + 1 � �������� �������
		num++;  // + 1 � ������
		f.x = rand() % W; // �������� ��������� ���������� � ��� ������
		f.y = rand() % H;  // �������� ��������� ���������� � ��� ������ 
	}

	if (s[0].x > W) s[0].x = 0;  if (s[0].x < 0) s[0].x = W; // ���� ������ ������ ����� �� ������� ����, 
	if (s[0].y > H) s[0].y = 0;  if (s[0].y < 0) s[0].y = H; // �� ������������� � �� �������������� �������;
	for (int i = 1; i < num; i++)  // ���������, ����������� �� ������ ���� � �����; 
		if (s[0].x == s[i].x && s[0].y == s[i].y) {
			gameover();
		}
}

int main()
{	
	setlocale(LC_ALL, "RUSSIAN"); // ����� ������� ����;
	std::cout << "��� ���� '������ �� SFML'!\n";
	std::cout << "�������� ���������: \n 1 : ����� \n 2 : ��������� \n 3 : ������ \n";
	int diff; // ���������� ���������;
	std::cin >> diff; // ������ ���������;
	if (diff == 1){ // ���� ��������� == "�����" ��:
        W = 15;   // ���������� ���-�� ������ �� 15/15;
        H = 15;
	    w = pix * W; // ������ ��������� ������ � ������ � ���������;
		h = pix * H;
	    gamestart = true; // �������� ����;
		 }
	 else if (diff==2)  gamestart = true; // ���� ��������� == "���������" �� �������� ����; (��� ���������� �� ��������� ����� �� ������ (���������);
	 else if (diff==3){ // �� ���� ����� ��� � � "�����", ��:
		 W = 50;  // ����� ���� 50/50 ������;
		 H = 50;
		 w = pix * W;
		 h = pix * H;
		 gamestart = true;
	 }
	 else if (diff == 123) { // ��������� ��������� ����� �� ���������� �� �������, �� ����������� �������� ������;
		 std::cout << "�� ����� ������!";
		 W = 50;
		 H = 50;
		 w = pix * W;
		 h = pix * H;
		 gamestart = true;
	 }
	 else {
		 std::cout << "������� ������ ���������!\n"; // ������� ��� ������� �������� ���������;
		 system("PAUSE");
	 }

		Font font; // ����� ���������� ��� ������;
		font.loadFromFile("arial.ttf"); // ��������� ����� �� �����;
		Text txt;  // ����� ���������� ��� ������;
		txt.setFont(font); // ���������� ����������� ����� �����;
		txt.setPosition(10, 10); // ��������� ������� ������ (����� ������� ����);
		txt.setCharacterSize(24); // ��������� ������ ������;
		txt.setStyle(Text::Bold); // ���������� ����� ������ "������";
		if (gamestart == true) {  // ���� ��������� ����: ... ;
			RenderWindow window(VideoMode(w, h), "Snake"); // ������ ���� � ������� ���������� SFML;
			switch (diff) of:{ // � ����������� �� ��������� ��������� ������ ��������;
			case 1: {
				t1.loadFromFile("images/Block 1.png"); // ������ ���� 1 (������);
				t2.loadFromFile("images/Snake 1.png"); // ������ ���� ������;
				t3.loadFromFile("images/Fruct 1.png"); // ������ ������� ������;
				break;  
		        	}
			case 2:
			   {
				t1.loadFromFile("images/Block 2.png"); // ������ ����� ��������;
				t2.loadFromFile("images/Snake 2.png");
				t3.loadFromFile("images/Fruct 2.png"); // � ������ ������;
				break;
		       }
			   case 3: {
				t1.loadFromFile("images/Block 3.png"); // ������ ������� ��������;
				t2.loadFromFile("images/Snake 3.png");
				t3.loadFromFile("images/Fruct 3.png"); // � ����� ������;
				break;
			   }
			   case 123: {
				t1.loadFromFile("images/Block 3.png"); // ������ ������� ��������;
				t2.loadFromFile("images/Snake 3.png");
				t3.loadFromFile("images/Fruct 3.png"); // � ����� ������;
				break;
			   }
			}

			Sprite sprite1(t1); //������ ������� �� ���������� ���� �������;
			Sprite sprite2(t2);
			Sprite fsprite(t3);
			Clock clock;  // ���������� �����;
			float timer = 0, delay = 0.15; // ���������� ��� �������� �������,(����������� ����); � �������� ����������; 
			if (diff == 2) delay = 0.1; // ��������� (���� �����);
			if (diff == 3) delay = 0.050; // ������;
			if (diff == 123) delay = 0.025; // ��������� ��������� Insane;
			f.x = rand() % W; // �������� ��������� ������� ��� � ������;
			f.y = rand() % H; // �������� ��������� ������� ��� y ������;

			while (window.isOpen())  // ������������ ������� ��� ���� SFML;
			{
				float time = clock.getElapsedTime().asSeconds();  // ����������� ������� � ���������� ��� �������;
				clock.restart(); // ������ �����;
				timer += time; // �������� ��������� �����;
				// ����� �������, ��������� 1 ��� � ���������� delay, ���������� ����� � �������� � ���������� time, ������������� ���� �, ��������� ��������� �����, ����� ������� ����� 1 ���;
				Event event;  // ������������ ����� � ���� SFML;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)  // ����� ��� �������� ���� � SFML;
						window.close();
				}

				if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) dir = 1;  // ��������� �������, ��������� � AWSD;
				if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D))))  dir = 2;  // ������� ��������� ����������� �����������, 
				if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) dir = 3;  // ���������� � ������� Move;
				if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::W)))) dir = 0;

				if (timer > delay) { timer = 0; Move(); }  // �������� ���������� timer, ����� ���������� ���������, � ���������� ������.

				window.clear();  // ������������ ������� ���� SFML;

				for (int i = 0; i < W; i++) // �� ���� �� ������ � ����� pix ���������� �� x;
					for (int j = 0; j < H; j++)  // �� ���� �� ������ � ����� pix ���������� �� y;
					{
						sprite1.setPosition(i*pix, j*pix);  window.draw(sprite1);  // ����� ������� ��� ������� ����������, � ������;
					}

				for (int i = 0; i < num; i++)  // ���������� �� ���� ������;
				{
					sprite2.setPosition(s[i].x*pix, s[i].y*pix);  window.draw(sprite2);  // ������ �� �������� � ������;
				}

				fsprite.setPosition(f.x*pix, f.y*pix);  // ����� ������� ��� ������� ������;
				window.draw(fsprite);  // ������ �����;
				std::ostringstream a;    // �������� ���������� ��� �������� �����;
				a << Fruct;		//������� � ��� ����� �����, �� ���� ��������� ������
				txt.setString("Score = " + a.str());//������ ������ ������ � �������� �������������� ���� ������ ������� .str() 
				window.draw(txt);  // ������ ���� �����;
				window.display();  // ������� �� �� �����;
			}
			return 0;
		}
	}