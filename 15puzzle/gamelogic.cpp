#include <SFML/Graphics.hpp>

using namespace sf;


void startGameScreen(RenderWindow& window, int& moveCounter, int field[][4], int drawContinue = 0);
void endGameScreen(RenderWindow &window, int movecounter);

int numGenerate(int playG[][4], const int iTemp, const int jTemp)
{
	int random = 1 + rand() % 16;
	for (int i = 0; i <= iTemp; i++)
	{
		int num = 4;
		if (i == iTemp)
		{
			num = jTemp;
		}
		for (int j = 0; j < num; j++)
		{
			if (playG[i][j] == random)
			{
				random = 1 + rand() % 16;
				i = -1;
				break;
			}
		}
	}
	return random;
}

bool gameOver(int field[][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (field[i][j] > field[i][j + 1])
			{
				return false;
			}
		}
	}
	return true;
}





int main()
{

	RenderWindow window(VideoMode(516, 516), "15-Puzzle Game!");
	window.setFramerateLimit(60);

	srand(time(NULL));

	int field[4][4];
	const int WIDTH = 129; // ширина спрайта
	Sprite sprites[16];
	int moveCounter = 0; 

	// начальное меню
	startGameScreen(window, moveCounter, field);
	
	Texture texture;
	texture.loadFromFile("texturepack/15pieces.png");


	// вырезка спрайтов
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			sprites[i * 4 + j].setTexture(texture);
			sprites[i * 4 + j].setTextureRect(IntRect(j * WIDTH, i * WIDTH, WIDTH, WIDTH));
		}
	}
	
	while (window.isOpen())
	{
		Event event;
		bool inEvent = false; // задержка на ивенты

		while (window.pollEvent(event))
		{
			// нажали esc - идем в меню
			if (Keyboard::isKeyPressed(Keyboard::Escape)){ startGameScreen(window, moveCounter, field, 1); }

			if (event.type == Event::Closed) { window.close(); }
			
			if (event.type == Event::MouseButtonPressed && !inEvent)
			{
		
				if (event.key.code == Mouse::Left)
				{
					inEvent = true;

					// переводим координаты курсора в ячейки массива
					Vector2i position = Mouse::getPosition(window);
					int x = position.x / WIDTH;
					int y = position.y / WIDTH;

					int dx = 0, dy = 0;
					bool found = false;

					// отслеживаем где пустая клетка
					if (field[y + 1][x] == 16 && y != 3 ) { dy = 1; found = true; }

					if (field[y - 1][x] == 16 && y != 0) { dy = -1; found = true; }

					if (field[y][x + 1] == 16 && x != 3) { dx = 1; found = true; }

					if (field[y][x - 1] == 16 && x != 0) { dx = -1; found = true; }

					// обмен ячеек
					int temp = field[y][x];
					field[y][x] = field[y + dy][x + dx];
					field[y + dy][x + dx] = temp;

					// если рядом белый спрайт
					if (found)
					{
						moveCounter++;

						//скорость анимации
						int speed = 13;
						
						// анимация перемещения
						sprites[15].move(-dx * WIDTH, -dy * WIDTH);
						for (int i = 0; i < WIDTH; i += speed)
						{
							sprites[temp - 1].move(dx * speed, dy * speed);
							window.draw(sprites[15]);
							window.draw(sprites[temp - 1]);
							window.display();
						}
					}
				}
			}
		}

		// отрисовка спрайтов
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				int spritePos = field[i][j] - 1;
				sprites[spritePos].setPosition(j * WIDTH, i * WIDTH);
				window.draw(sprites[spritePos]);
			}
		}

		window.display();

		// если игра окончена
		if (gameOver(field))
		{
			endGameScreen(window, moveCounter);

			// если было выбрано menu
			if (window.isOpen())
			{
				startGameScreen(window, moveCounter, field);
			}
		}

	}
	return 0;
}
