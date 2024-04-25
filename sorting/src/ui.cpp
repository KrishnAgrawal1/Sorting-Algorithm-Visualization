#include "../header/ui.hpp"


	void ui::loadAssetes()
	{
		this->font.loadFromFile("assets\\font.ttf");

		this->title();
		this->startButton();
		this->pauseButton();
		this->resetButton();
		this->exitButton();

		this->selectionSortButton();
		this->bubbleSortButton();
	}

	void ui::title()
	{
		titalHead.setFont(font);
		titalHead.setString("Sorting Algorithm Visualization");
		titalHead.setCharacterSize(24);
		titalHead.setFillColor(sf::Color::White);
		//titalHead.setStyle(sf::Text::Bold);
		titalHead.setPosition(750,10);

		algoHead.setFont(font);
		algoHead.setString("Algorithm");
		algoHead.setCharacterSize(24);
		algoHead.setFillColor(sf::Color::White);
		//algoHead.setStyle(sf::Text::Bold);
		algoHead.setPosition(50, 100);
	}

	void ui::startButton()
	{
		startBtShape.setPosition(sf::Vector2f(50, 25));
		startBtShape.setSize(sf::Vector2f(100, 50));
		startBtShape.setFillColor(sf::Color::Green);

		startBtText.setFont(font);
		startBtText.setString("Start");
		startBtText.setCharacterSize(24);
		startBtText.setFillColor(sf::Color::Red);
		//startBtText.setStyle(sf::Text::Bold);
		startBtText.setPosition(50+13, 25+10);
	}

	void ui::pauseButton()
	{
		pauesBtShape.setPosition(sf::Vector2f(200, 25));
		pauesBtShape.setSize(sf::Vector2f(100, 50));
		pauesBtShape.setFillColor(sf::Color::Green);

		pauseBtText.setFont(font);
		pauseBtText.setString("Pause");
		pauseBtText.setCharacterSize(24);
		pauseBtText.setFillColor(sf::Color::Red);
		//stopBtText.setStyle(sf::Text::Bold);
		pauseBtText.setPosition(200 + 13, 25 + 10);
	}

	void ui::resetButton()
	{
		resetBtShape.setPosition(sf::Vector2f(350, 25));
		resetBtShape.setSize(sf::Vector2f(100, 50));
		resetBtShape.setFillColor(sf::Color::Green);

		resetBtText.setFont(font);
		resetBtText.setString("Reset");
		resetBtText.setCharacterSize(24);
		resetBtText.setFillColor(sf::Color::Red);
		//stopBtText.setStyle(sf::Text::Bold);
		resetBtText.setPosition(350 + 13, 25 + 10);
	}

	void ui::exitButton()
	{
		exitBtShape.setPosition(sf::Vector2f(1800, 25));
		exitBtShape.setSize(sf::Vector2f(100, 50));
		exitBtShape.setFillColor(sf::Color::Black);

		exitBtText.setFont(font);
		exitBtText.setString("Exit");
		exitBtText.setCharacterSize(24);
		exitBtText.setFillColor(sf::Color::White);
		//exitBtText.setStyle(sf::Text::Bold);
		exitBtText.setPosition(1800 + 20, 25 + 10);
	}

	void ui::selectionSortButton()
	{
		selectionSortBt.setPosition(sf::Vector2f(50, 150));
		selectionSortBt.setSize(sf::Vector2f(220, 40));
		selectionSortBt.setFillColor(sf::Color::Green);

		selectionSortText.setFont(font);
		selectionSortText.setString("Selection Sort");
		selectionSortText.setCharacterSize(24);
		selectionSortText.setFillColor(sf::Color::Red);
		//exitBtText.setStyle(sf::Text::Bold);
		selectionSortText.setPosition(50+8, 150 + 5);
	}

	void ui::bubbleSortButton()
	{
		bubbleSortBt.setPosition(sf::Vector2f(320, 150));
		bubbleSortBt.setSize(sf::Vector2f(220, 40));
		bubbleSortBt.setFillColor(sf::Color::White);

		bubbleSortText.setFont(font);
		bubbleSortText.setString("Bubble Sort");
		bubbleSortText.setCharacterSize(24);
		bubbleSortText.setFillColor(sf::Color::Black);
		//bubbleSortText.setStyle(sf::Text::Bold);
		bubbleSortText.setPosition(320 + 28, 150 + 5);
	}

