#pragma once

#include "resources.hpp"

class ui
{
private:
	sf::Font font;

public:
	sf::Text titalHead;
	sf::Text algoHead;

	sf::RectangleShape startBtShape;
	sf::Text startBtText;

	sf::RectangleShape pauesBtShape;
	sf::Text pauseBtText;

	sf::RectangleShape resetBtShape;
	sf::Text resetBtText;

	sf::RectangleShape exitBtShape;
	sf::Text exitBtText;

	sf::RectangleShape selectionSortBt;
	sf::Text selectionSortText;

	sf::RectangleShape bubbleSortBt;
	sf::Text bubbleSortText;

	//sf::RectangleShape exitBtShape;
	//sf::Text exitBtText;
	//sf::RectangleShape exitBtShape;
	//sf::Text exitBtText;
	//sf::RectangleShape exitBtShape;
	//sf::Text exitBtText;

	void loadAssetes();

	void title();
	void startButton();
	void pauseButton();
	void resetButton();
	void exitButton();

	void selectionSortButton();
	void bubbleSortButton();
};