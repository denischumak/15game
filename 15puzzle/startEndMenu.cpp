#include <SFML/Graphics.hpp>

using namespace sf;


int numGenerate(int playG[][4], const int iTemp, const int jTemp);

void startGameScreen(RenderWindow& window, int& moveCounter, int field[][4], int drawContinue = 0)
{
	Texture textureGrid[7];
	Sprite spritegrid[7];
	bool menuClose = false;
	Clock clock;

	textureGrid[0].loadFromFile("texturepack/logo.png");
	textureGrid[1].loadFromFile("texturepack/newgame.png");
	textureGrid[2].loadFromFile("texturepack/about.png");
	textureGrid[3].loadFromFile("texturepack/quit.png");
	textureGrid[4].loadFromFile("texturepack/logoauthor.png");
	textureGrid[5].loadFromFile("texturepack/continue.png");
	textureGrid[6].loadFromFile("texturepack/aboutin.png");

	for (int i = 0; i < 7; i++) { spritegrid[i].setTexture(textureGrid[i]); }

	spritegrid[0].setPosition(7, 12);
	spritegrid[1].setPosition(19, 218);
	spritegrid[2].setPosition(19, 306);
	spritegrid[3].setPosition(19, 401);
	spritegrid[4].setPosition(347, 489);
	spritegrid[5].setPosition(19, 131);

	while (!menuClose)
	{
		// таймер
		Time time = clock.getElapsedTime();

		window.clear(Color(51, 51, 54));
		spritegrid[5].setColor(Color(255, 135, 114));
		int menuOption = 0;
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				menuClose = true;
			}
		}

		for (int i = 1; i < 5; i++) { spritegrid[i].setColor(Color::White); }

		// кнопка continue
		if (IntRect(19, 131, 305, 60).contains(Mouse::getPosition(window)) && drawContinue)
		{
			spritegrid[5].setColor(Color(255, 153, 0));
			menuOption = 1;
		}

		// кнопка new game
		if (IntRect(19, 218, 337, 65).contains(Mouse::getPosition(window)))
		{
			spritegrid[1].setColor(Color(91, 127, 125));
			menuOption = 2;
		}
		
		// кнопка about
		if (IntRect(19, 306, 229, 67).contains(Mouse::getPosition(window)))
		{
			spritegrid[2].setColor(Color(91, 127, 125));
			menuOption = 3;
		}

		// кнопка quit
		if (IntRect(19, 401, 154, 73).contains(Mouse::getPosition(window)))
		{
			spritegrid[3].setColor(Color(91, 127, 125));
			menuOption = 4;
		}

		// пасхалка с лого
		if (IntRect(7, 12, 501, 89).contains(Mouse::getPosition(window)))
		{
			menuOption = 5;
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuOption == 1) { menuClose = true; }

			// new game - генерируем новый массив
			if (menuOption == 2)
			{
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						field[i][j] = numGenerate(field, i, j);
					}
				}

				moveCounter = 0;
				menuClose = true; 

			}

			// задержка на кнопку about
			if (menuOption == 3 && time.asSeconds() > 0.2)
			{
				window.draw(spritegrid[6]);
				window.draw(spritegrid[4]);
				window.display();
				clock.restart();
				while (!Keyboard::isKeyPressed(Keyboard::Escape)) 
				{
					if (window.pollEvent(event) && event.type == Event::Closed)
					{
						window.close(); 
						menuClose = true; 
					}
				}
			}

			if (menuOption == 4) { window.close(); menuClose = true; }

			// задержка на нажатия по лого
			if (menuOption == 5 && time.asSeconds() > 0.15)
			{
				spritegrid[0].setColor(Color(rand() % 256 , rand() % 256, rand() % 256)); 
				clock.restart();
			}
		}

		
		for (int i = 0; i < 5 + drawContinue; i++)
		{
			window.draw(spritegrid[i]);
		}

		window.display();

	}
}

void endGameScreen(RenderWindow& window, int movecounter)
{
	Texture texturegrid[6];
	Sprite spritegrid[6];
	bool menuClose = 0;

	texturegrid[0].loadFromFile("texturepack/logo.png");
	texturegrid[1].loadFromFile("texturepack/gratz.png");
	texturegrid[2].loadFromFile("texturepack/moves.png");
	texturegrid[3].loadFromFile("texturepack/menu.png");
	texturegrid[4].loadFromFile("texturepack/quit.png");
	texturegrid[5].loadFromFile("texturepack/logoauthor.png");

	Font font;
	font.loadFromFile("fonts/MachineGunk.ttf");
	Text text("", font, 50);
	text.setFillColor(Color(255, 165, 112));

	for (int i = 0; i < 6; i++)
	{
		spritegrid[i].setTexture(texturegrid[i]);
	}

	spritegrid[0].setPosition(7, 12);
	spritegrid[1].setPosition(15, 114);
	spritegrid[2].setPosition(15, 170);
	spritegrid[3].setPosition(19, 306);
	spritegrid[4].setPosition(19, 401);
	spritegrid[5].setPosition(347, 489);

	while (!menuClose)
	{
		window.clear(Color(51, 51, 54));

		Event event;
		int menuOption = 0;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				menuClose = true;
			}
		}

		// подсвечиваем menu и quit
		spritegrid[3].setColor(Color::White);
		spritegrid[4].setColor(Color::White);

		// кнопка menu
		if (IntRect(19, 306, 181, 63).contains(Mouse::getPosition(window)))
		{
			spritegrid[3].setColor(Color(91, 127, 125));
			menuOption = 1;
		}

		// кнопка quit
		if (IntRect(19, 401, 154, 73).contains(Mouse::getPosition(window)))
		{
			spritegrid[4].setColor(Color(91, 127, 125));
			menuOption = 2;

		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuOption == 1) { menuClose = 1; }

			if (menuOption == 2) { window.close(); menuClose = 1;}
		}

		// отрисовывает спрайты и счет
		for (int i = 0; i < 6; i++)
		{
			text.setString(std::to_string(movecounter));
			text.setPosition(163,156);
			window.draw(text);
			window.draw(spritegrid[i]);
		}

		window.display();

	}
}