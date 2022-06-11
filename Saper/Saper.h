#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<vector>
#include<ctime>
#include<string>
#include<iostream>
#include<fstream>
#include<Windows.h>

class Saper
{
private:
	//Variables
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Objects
	sf::RectangleShape board;	
	sf::RectangleShape reset;
	sf::RectangleShape logo;
	sf::RectangleShape* result;	
	std::vector<sf::RectangleShape> box;

	//Textures
	sf::Texture boardTexture;
	sf::Texture resetTexture;
	sf::Texture logoTexture;
	sf::Texture resultTexture;	
	std::vector<sf::Texture> boxTexture;
	
	//Logic
	bool bomb[64];
	bool clickedBox[64];
	bool flag[64];

	//Record
	float record;
	std::fstream recordFile;

	//Mouse position
	sf::Vector2f mousePosition;

	//Timer
	sf::RectangleShape s1;
	sf::RectangleShape s2;
	sf::RectangleShape s3;
	sf::Texture s1Texture;
	sf::Texture s2Texture;
	sf::Texture s3Texture;
	sf::Clock clock;
	float dt; //count time since game start
	bool startTimer;

	//Date
	std::time_t now;
	struct std::tm date;
	/*std::tm date_in;
	std::tm date_temp;
	const std::tm* time_out;*/
	sf::Font font;
	sf::Text text1;
	sf::Text text2;
	sf::Text text3;

	//Music
	sf::Music deathSound;
	sf::Music winSound;
	sf::Music recordSound;

	//Private functions
	void initWindow();
	void initBoard();
	void drawBoard();
	void initBoxes();
	void drawBoxes();
	void bombRender();
	void initDate();
	void initMusic();
	void initRecord();

public:
	//Public functions
	Saper();
	~Saper();

	//Event functions
	const bool running() const;
	void poolEvent();	

	//Mouse functions
	void updateMousePosition();

	//Game functions
	void updateBoxes();
	void checkEmpty(int i);
	void gameLogic(int i);
	void resetGame();
	void winCheck();

	//Timer functions
	void updateTimer();
	void Timer();

	//Date functions
	void updateDate();

	//Main functions
	void update();
	void render();
};

