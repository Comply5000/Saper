#include "Saper.h"

//Private functions
void Saper::initWindow() //zdefiniowanie okna
{
	this->videoMode.width = 1116;
	this->videoMode.height = 784;
	this->window = new sf::RenderWindow(this->videoMode, "Saper", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Saper::initBoard() //zdefiniowanie planszy
{
	this->board.setPosition(0.f, 0.f);
	this->board.setSize(sf::Vector2f(816.f, 784.f));
	this->boardTexture.loadFromFile("Textures/board.png");
	this->board.setTexture(&boardTexture);

	this->reset.setPosition(870.f, 400.f);
	this->reset.setSize(sf::Vector2f(180.f, 90.f));
	this->resetTexture.loadFromFile("Textures/reset.png");
	this->reset.setTexture(&resetTexture);

	this->logo.setPosition(835.f, 45.f);
	this->logo.setSize(sf::Vector2f(256.f, 144.f));
	this->logoTexture.loadFromFile("Textures/logo.png");
	this->logo.setTexture(&logoTexture);

	this->result = new sf::RectangleShape;

	//Timer boxes
	this->s1.setPosition(835.f, 240.f);
	this->s1.setSize(sf::Vector2f(80.f, 120.f));
	this->s1Texture.loadFromFile("Textures/Timer/0.png");
	this->s1.setTexture(&s1Texture);
	//this->s1.setFillColor(sf::Color::Red);

	this->s2.setPosition(920.f, 240.f);
	this->s2.setSize(sf::Vector2f(80.f, 120.f));
	this->s2Texture.loadFromFile("Textures/Timer/0.png");
	this->s2.setTexture(&s2Texture);
	//this->s2.setFillColor(sf::Color::Red);

	this->s3.setPosition(1005.f, 240.f);
	this->s3.setSize(sf::Vector2f(80.f, 120.f));
	this->s3Texture.loadFromFile("Textures/Timer/0.png");
	this->s3.setTexture(&s3Texture);
	//this->s3.setFillColor(sf::Color::Red);
}

void Saper::drawBoard()
{
	this->window->draw(board);
	this->window->draw(reset);
	this->window->draw(logo);
	this->window->draw(s1);
	this->window->draw(s2);
	this->window->draw(s3);
}

void Saper::initBoxes() //zdefiniowanie pól
{
	this->boxTexture.resize(64);
	for (int i = 0;i < 64;i++)
	{
		this->boxTexture[i].loadFromFile("Textures/def.png");
	}	
	this->box.resize(64);	

	int x;
	int y;
	for (int i = 0;i < 64;i++)
	{	
		if (i == 0)
		{
			x = 8.f;
			y = 8.f;
		}
		if (i == 8)
		{
			y = 105.f;
			x = 8.f;
		}
		if (i == 16)
		{
			y = 202.f;
			x = 8.f;
		}	
		if (i == 24)
		{
			y = 299.f;
			x = 8.f;
		}
		if (i == 32)
		{
			y = 396.f;
			x = 8.f;
		}
		if (i == 40)
		{
			y = 493.f;
			x = 8.f;
		}
		if (i == 48)
		{
			y = 590.f;
			x = 8.f;
		}
		if (i == 56)
		{
			y = 687.f;
			x = 8.f;
		}
		this->box[i].setPosition(x, y);
		this->box[i].setSize(sf::Vector2f(92.f, 88.f));
		this->box[i].setTexture(&boxTexture[i]);
		x += 101;
	}	
}

void Saper::drawBoxes() 
{
	for(int i = 0;i<64;i++)
		this->window->draw(box[i]);	
}

void Saper::bombRender() //rozmieszczenie bomb
{
	int i = 0;
	while(i<10)
	{
		int a = rand() % 64;
		if (!bomb[a])
		{
			bomb[a] = true;
			i++;
		}			
	}	
}

void Saper::initDate() //zdefiniowanie tekstu z dat¹
{
	this->font.loadFromFile("Fonts/arial.ttf");

	this->text1.setFont(this->font);
	this->text1.setCharacterSize(48);
	this->text1.setPosition(sf::Vector2f(868.f, 540.f));
	//this->text1.setString("00:00:34");

	this->text2.setFont(this->font);
	this->text2.setCharacterSize(48);
	this->text2.setPosition(sf::Vector2f(840.f, 600.f));
	//this->text2.setString("10.12.2021");	
}

void Saper::initMusic() //zdefinowanie muzyki
{
	this->deathSound.openFromFile("Audio/death_sound.ogg");
	this->deathSound.setVolume(100);	

	this->winSound.openFromFile("Audio/win.ogg");
	this->winSound.setVolume(100);

	this->recordSound.openFromFile("Audio/record.wav");
	this->recordSound.setVolume(100);
}

void Saper::initRecord() //pobranie rekordu z pliku
{
	this->recordFile.open("record.txt", std::ios::in);
	std::string line;
	if (this->recordFile.good())
	{
		std::getline(recordFile, line);
		this->record = std::stof(line);
	}
	else
		this->record = 1000;
		
	this->recordFile.close();
}


//Public functions
Saper::Saper() //konstruktor
{
	this->initWindow();
	this->initBoard();
	this->initBoxes();
	this->bombRender();
	this->initDate();
	this->initMusic();
	this->initRecord();
}

Saper::~Saper() //destruktor
{
	//zapisanie wartoœæi rekordu do pliku przy wyjœciu z gry
	this->recordFile.open("record.txt", std::ios::out);
	this->recordFile << this->record;
	this->recordFile.close();

	delete this->window;
}

const bool Saper::running() const //sprawdzenie czy okno jest otwarte
{
	return this->window->isOpen();
}

void Saper::poolEvent() //eventy odpowiedzialne za zamykanie okna
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Saper::updateMousePosition() //aktualizacja pozycji myszy wzglêcem okna
{
	this->mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void Saper::updateBoxes() //aktualizacja ikon przycisków
{
	//odkrycie pola
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (int i = 0;i < 64;i++)
		{
			if (this->box[i].getGlobalBounds().contains(this->mousePosition) && !clickedBox[i] && !flag[i])
			{
				if (!startTimer) //uruchomienie stopera jeœli klikniêty zosta³ 1 przycisk
				{
					this->dt = this->clock.restart().asSeconds();
					startTimer = true;
				}
				Saper::gameLogic(i);
			}
		}
	}
	
	//oflagowanie pola
	static bool pressed = false;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		for (int i = 0;i < 64;i++)
		{
			if (this->box[i].getGlobalBounds().contains(this->mousePosition) && !clickedBox[i] && !pressed)
			{
				pressed = true;
				if (!startTimer)//uruchomienie stopera jeœli klikniêty zosta³ 1 przycisk
				{
					this->dt = this->clock.restart().asSeconds();
					startTimer = true;
				}
				if (!flag[i])
				{
					this->boxTexture[i].loadFromFile("Textures/flag.png");
					flag[i] = true;
				}			
				else
				{
					this->boxTexture[i].loadFromFile("Textures/def.png");
					flag[i] = false;
				}
					
			}
		}
	}
	if (this->ev.type == sf::Event::MouseButtonReleased)
		if (this->ev.mouseButton.button == sf::Mouse::Right)
			pressed = false;
}

void Saper::gameLogic(int i)
{
	if (bomb[i]) //jeœli zosta³a klikniêta bomba
	{
		for (int i = 0;i < 64;i++)
		{
			this->clickedBox[i] = true;
			if (this->bomb[i])
				this->boxTexture[i].loadFromFile("Textures/bomb.png");
		}
		this->result->setPosition(49.f, 287.f);
		this->result->setSize(sf::Vector2f(718.f, 210.f));
		this->resultTexture.loadFromFile("Textures/died.png");
		this->result->setTexture(&resultTexture);
		this->deathSound.play();

		this->startTimer = false;
	}	
	else
	{
		Saper::checkEmpty(i);
	}
}

void Saper::checkEmpty(int i)
{
	this->clickedBox[i] = true;
	int x = 0; //iloœæ bomb obok pola
	if (i == 0)
	{
		//zliczanie bomb obok klikniêteg pola
		if (bomb[i + 1]) x++;
		if (bomb[i + 8]) x++;
		if (bomb[i + 9]) x++;
		std::string t = "Textures/" + std::to_string(x) + ".png";
		this->boxTexture[i].loadFromFile(t);
		//ponowne wykonanie funkcji przy s¹siennich polach jeœli obok obecnego pola nie by³o bomb
		if (x == 0)
		{
			if(!clickedBox[i+1]) Saper::checkEmpty(i+1);
			if(!clickedBox[i + 8]) Saper::checkEmpty(i+8);
			if (!clickedBox[i + 9])Saper::checkEmpty(i+9);
		}
	}
	else if (i == 7)
	{
		if (bomb[i - 1]) x++;
		if (bomb[i + 7]) x++;
		if (bomb[i + 8]) x++;
		std::string t = "Textures/" + std::to_string(x) + ".png";
		this->boxTexture[i].loadFromFile(t);
		if (x == 0)
		{
			if (!clickedBox[i - 1]) Saper::checkEmpty(i - 1);
			if (!clickedBox[i + 7]) Saper::checkEmpty(i + 7);
			if (!clickedBox[i + 8])Saper::checkEmpty(i + 8);
		}
	}
	else if (i == 56)
	{
		if (bomb[i - 8]) x++;
		if (bomb[i - 7]) x++;
		if (bomb[i + 1]) x++;
		std::string t = "Textures/" + std::to_string(x) + ".png";
		this->boxTexture[i].loadFromFile(t);
		if (x == 0)
		{
			if (!clickedBox[i - 8]) Saper::checkEmpty(i - 8);
			if (!clickedBox[i - 7]) Saper::checkEmpty(i - 7);
			if (!clickedBox[i + 1])Saper::checkEmpty(i + 1);
		}
	}
	else if (i == 63)
	{
		if (bomb[i - 9]) x++;
		if (bomb[i - 8]) x++;
		if (bomb[i - 1]) x++;
		std::string t = "Textures/" + std::to_string(x) + ".png";
		this->boxTexture[i].loadFromFile(t);
		if (x == 0)
		{
			if (!clickedBox[i - 9]) Saper::checkEmpty(i - 9);
			if (!clickedBox[i - 8]) Saper::checkEmpty(i - 8);
			if (!clickedBox[i - 1])Saper::checkEmpty(i - 1);
		}
	}
	else if (i % 8 == 0 && i != 0 && i != 56)
	{
		if (bomb[i - 8]) x++;
		if (bomb[i - 7]) x++;
		if (bomb[i + 1]) x++;
		if (bomb[i + 8]) x++;
		if (bomb[i + 9]) x++;
		std::string t = "Textures/" + std::to_string(x) + ".png";
		this->boxTexture[i].loadFromFile(t);
		if (x == 0)
		{
			if (!clickedBox[i - 8]) Saper::checkEmpty(i - 8);
			if (!clickedBox[i - 7]) Saper::checkEmpty(i - 7);
			if (!clickedBox[i + 1])Saper::checkEmpty(i + 1);
			if (!clickedBox[i + 8])Saper::checkEmpty(i + 8);
			if (!clickedBox[i + 9])Saper::checkEmpty(i + 9);
		}
	}
	else if ((i - 7) % 8 == 0 && i != 7 && i != 63)
	{
		if (bomb[i - 9]) x++;
		if (bomb[i - 8]) x++;
		if (bomb[i - 1]) x++;
		if (bomb[i + 7]) x++;
		if (bomb[i + 8]) x++;
		std::string t = "Textures/" + std::to_string(x) + ".png";
		this->boxTexture[i].loadFromFile(t);
		if (x == 0)
		{
			if (!clickedBox[i - 9]) Saper::checkEmpty(i - 9);
			if (!clickedBox[i - 8]) Saper::checkEmpty(i - 8);
			if (!clickedBox[i - 1])Saper::checkEmpty(i - 1);
			if (!clickedBox[i + 7])Saper::checkEmpty(i + 7);
			if (!clickedBox[i + 8])Saper::checkEmpty(i + 8);
		}
	}
	else if (i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 6)
	{
		if (bomb[i - 1]) x++;
		if (bomb[i + 1]) x++;
		if (bomb[i + 7]) x++;
		if (bomb[i + 8]) x++;
		if (bomb[i + 9]) x++;
		std::string t = "Textures/" + std::to_string(x) + ".png";
		this->boxTexture[i].loadFromFile(t);
		if (x == 0)
		{
			if (!clickedBox[i - 1]) Saper::checkEmpty(i - 1);
			if (!clickedBox[i + 1]) Saper::checkEmpty(i + 1);
			if (!clickedBox[i + 7])Saper::checkEmpty(i + 7);
			if (!clickedBox[i + 8])Saper::checkEmpty(i + 8);
			if (!clickedBox[i + 9])Saper::checkEmpty(i + 9);
		}
	}
	else if (i == 57 || i == 58 || i == 59 || i == 60 || i == 61 || i == 62)
	{
		if (bomb[i - 9]) x++;
		if (bomb[i - 8]) x++;
		if (bomb[i - 7]) x++;
		if (bomb[i - 1]) x++;
		if (bomb[i + 1]) x++;
		std::string t = "Textures/" + std::to_string(x) + ".png";
		this->boxTexture[i].loadFromFile(t);
		if (x == 0)
		{
			if (!clickedBox[i - 9]) Saper::checkEmpty(i - 9);
			if (!clickedBox[i - 8]) Saper::checkEmpty(i - 8);
			if (!clickedBox[i - 7])Saper::checkEmpty(i - 7);
			if (!clickedBox[i - 1])Saper::checkEmpty(i - 1);
			if (!clickedBox[i + 1])Saper::checkEmpty(i + 1);
		}
	}
	else
	{
		if (bomb[i - 9]) x++;
		if (bomb[i - 8]) x++;
		if (bomb[i - 7]) x++;
		if (bomb[i - 1]) x++;
		if (bomb[i + 1]) x++;
		if (bomb[i + 7]) x++;
		if (bomb[i + 8]) x++;
		if (bomb[i + 9]) x++;
		std::string t = "Textures/" + std::to_string(x) + ".png";
		this->boxTexture[i].loadFromFile(t);
		if (x == 0)
		{
			if (!clickedBox[i - 9]) Saper::checkEmpty(i - 9);
			if (!clickedBox[i - 8]) Saper::checkEmpty(i - 8);
			if (!clickedBox[i - 7])Saper::checkEmpty(i - 7);
			if (!clickedBox[i - 1])Saper::checkEmpty(i - 1);
			if (!clickedBox[i + 1])Saper::checkEmpty(i + 1);
			if (!clickedBox[i + 7])Saper::checkEmpty(i + 7);
			if (!clickedBox[i + 8])Saper::checkEmpty(i + 8);
			if (!clickedBox[i + 9])Saper::checkEmpty(i + 9);
		}
	}
	Saper::winCheck(); //sprawdzenie warunków zwyciêstwa
}

void Saper::resetGame() //reset gry (wszystkich zmiennych i tekstur)
{
	static bool pressed = false;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->reset.getGlobalBounds().contains(this->mousePosition) && !pressed)
	{
		pressed = true;
		for (int i = 0;i < 64;i++)
		{
			this->boxTexture[i].loadFromFile("Textures/def.png");
			this->bomb[i] = false;
			this->clickedBox[i] = false;
			this->flag[i] = false;
		}	
		delete this->result;
		this->result = new sf::RectangleShape;
		Saper::bombRender();
		this->dt = 0;
		this->startTimer = false;
		this->deathSound.stop();		
		this->winSound.stop();
		this->recordSound.stop();
	}

	if (this->ev.type == sf::Event::MouseButtonReleased)
		if (this->ev.mouseButton.button == sf::Mouse::Left)
			pressed = false;

}

void Saper::winCheck()
{
	//zliczenie odkrytych pól
	int x = 0;
	for (int i = 0;i < 64;i++)
		if (clickedBox[i])
			x++;

	//wszystkie pola poza bombami zosta³y odkryte
	if (x == 54)
	{
		this->startTimer = false;
		this->result->setPosition(49.f, 287.f);
		this->result->setSize(sf::Vector2f(718.f, 210.f));

		if (this->dt < this->record)
		{			
			this->resultTexture.loadFromFile("Textures/record.png");
			this->result->setTexture(&resultTexture);
			this->recordSound.play();
			this->record = this->dt;
		}

		else
		{
			this->resultTexture.loadFromFile("Textures/win.png");
			this->result->setTexture(&resultTexture);
			this->winSound.play();
		}
			
		for (int i = 0;i < 64;i++)
			if (bomb[i])
				boxTexture[i].loadFromFile("Textures/bomb.png");
	}	
}

void Saper::updateTimer() //aktualizacja czasu do stopera
{
	if (startTimer)
	{
		this->dt = this->clock.getElapsedTime().asSeconds();
	}	
}

void Saper::Timer() //wyœwietlenie czasu stopera (podmiana textur)
{	
	std::string s1 = std::to_string((int)dt / 100);
	std::string s2;
	std::string s3;
	if (dt >= 100)
	{
		s2 = std::to_string(((int)dt / 10)%10);
		s3 = std::to_string(((int)dt % 10) % 10);
	}
	else if (dt < 100 && dt>=10)
	{
		s2 = std::to_string((int)dt / 10);
		s3 = std::to_string((int)dt % 10);
	}
	else if (dt < 10)
	{
		s2 = "0";
		s3 = std::to_string((int)dt);
	}

	std::string t1 = "Textures/Timer/" + s1+".png";
	std::string t2 = "Textures/Timer/" + s2+".png";
	std::string t3 = "Textures/Timer/" + s3+".png";
	
	this->s1Texture.loadFromFile(t1);
	this->s2Texture.loadFromFile(t2);
	this->s3Texture.loadFromFile(t3);
}

void Saper::updateDate() //aktualizacja daty i godziny
{
	this->now = time(0);
	localtime_s(&date, &now);
	std::string hour;
	std::string minute;
	std::string second;
	std::string day;
	std::string month;
	std::string year = std::to_string(this->date.tm_year + 1900);

	if (date.tm_hour < 10)
		hour = "0" + std::to_string(this->date.tm_hour);
	else
		hour = std::to_string(this->date.tm_hour);

	if (date.tm_min < 10)
		minute = "0" + std::to_string(this->date.tm_min);
	else
		minute = std::to_string(this->date.tm_min);

	if (date.tm_sec < 10)
		second = "0" + std::to_string(this->date.tm_sec);
	else
		second = std::to_string(this->date.tm_sec);

	if (date.tm_mday < 10)
		day = "0" + std::to_string(this->date.tm_mday);
	else
		day = std::to_string(this->date.tm_mday);

	if (date.tm_mon+1 < 10)
		month = "0" + std::to_string(this->date.tm_mon+1);
	else
		month = std::to_string(this->date.tm_mon+1);

	std::string t1 = hour + ":" + minute + ":" + second;
	std::string t2 = day + "." + month + "." + year;

	this->text1.setString(t1);
	this->text2.setString(t2);
}

void Saper::update()
{
	this->poolEvent();
	this->updateMousePosition();
	this->updateTimer();
	this->Timer();
	this->updateBoxes();
	this->resetGame();
	this->updateDate();
}

void Saper::render()
{
	this->window->clear();
	this->drawBoard();
	this->drawBoxes();
	this->window->draw(*result);
	this->window->draw(text1);
	this->window->draw(text2);
	this->window->display();
}
