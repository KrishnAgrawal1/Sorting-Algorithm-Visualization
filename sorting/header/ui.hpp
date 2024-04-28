#pragma once

#include "resources.hpp"

class ui
{
private:
	sf::Font font;

public:
	sf::Color buttonBorderSelected;
	sf::Color buttonTextSelected;

	sf::Color buttonBorder;
	sf::Color buttonText;

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


	//Sorting algo button
	sf::RectangleShape selectionSortBt;
	sf::Text selectionSortText;

	sf::RectangleShape bubbleSortBt;
	sf::Text bubbleSortText;

	sf::RectangleShape insertionBtShape;
	sf::Text insertionBtText;

	sf::RectangleShape mergeBtShape;
	sf::Text mergeBtText;

	sf::RectangleShape quickBtShape;
	sf::Text quickBtText;

	void loadAssetes();

	void title();
	void startButton();
	void pauseButton();
	void resetButton();
	void exitButton();

	void selectionSortButton();
	void bubbleSortButton();
	void insertionSortButton();
	void mergeSortButton();
	void quickSortButton();
};