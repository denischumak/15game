#include <SFML/Graphics.hpp>

using namespace sf;


void startGameScreen(RenderWindow& window, int& moveCounter, int field[][4], int drawContinue = 0);
void endGameScreen(RenderWindow &window, int movecounter);

// генерирует случайное число
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

// проверка на окончание игры
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
	const int WIDTH = 129; // øèðèíà ñïðàéòà
	Sprite sprites[16];
	int moveCounter = 0; 

	// íà÷àëüíîå ìåíþ
	startGameScreen(window, moveCounter, field);
	
	Texture texture;
	texture.loadFromFile("texturepack/15pieces.png");


	// âûðåçêà ñïðàéòîâ
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
		bool inEvent = false; // çàäåðæêà íà èâåíòû

		while (window.pollEvent(event))
		{
			// íàæàëè esc - èäåì â ìåíþ
			if (Keyboard::isKeyPressed(Keyboard::Escape)){ startGameScreen(window, moveCounter, field, 1); }

			if (event.type == Event::Closed) { window.close(); }
			
			if (event.type == Event::MouseButtonPressed && !inEvent)
			{
		
				if (event.key.code == Mouse::Left)
				{
					inEvent = true;

					// ïåðåâîäèì êîîðäèíàòû êóðñîðà â ÿ÷åéêè ìàññèâà
					Vector2i position = Mouse::getPosition(window);
					int x = position.x / WIDTH;
					int y = position.y / WIDTH;

					int dx = 0, dy = 0;
					bool found = false;

					// îòñëåæèâàåì ãäå ïóñòàÿ êëåòêà
					if (field[y + 1][x] == 16 && y != 3 ) { dy = 1; found = true; }

					if (field[y - 1][x] == 16 && y != 0) { dy = -1; found = true; }

					if (field[y][x + 1] == 16 && x != 3) { dx = 1; found = true; }

					if (field[y][x - 1] == 16 && x != 0) { dx = -1; found = true; }

					// îáìåí ÿ÷ååê
					int temp = field[y][x];
					field[y][x] = field[y + dy][x + dx];
					field[y + dy][x + dx] = temp;

					// åñëè ðÿäîì áåëûé ñïðàéò
					if (found)
					{
						moveCounter++;

						//ñêîðîñòü àíèìàöèè
						int speed = 13;
						
						// àíèìàöèÿ ïåðåìåùåíèÿ
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

		// îòðèñîâêà ñïðàéòîâ
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

		// åñëè èãðà îêîí÷åíà
		if (gameOver(field))
		{
			endGameScreen(window, moveCounter);

			// åñëè áûëî âûáðàíî menu
			if (window.isOpen())
			{
				startGameScreen(window, moveCounter, field);
			}
		}

	}
	return 0;
}
