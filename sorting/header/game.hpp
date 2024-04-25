#pragma once

#include "resources.hpp"
#include "ui.hpp"

class Game
{
private:
	sf::RenderWindow* winmain;
	sf::Event ev;
	sf::VideoMode videoMode;
	std::chrono::milliseconds delay_ms;

	bool pause;
	bool terminateSorting;
	int sortingAlgoUsing;

	//vector of height
	std::vector<sf::RectangleShape> rect;

	//mutex
	std::mutex mtx;

	//ui
	ui interface;

	//Private Functions
	void initializeVariables();
	void initWindow();

	//
	void sortingCompleted();

	void isPause();
	bool isterminateSorting();

public:
	//to create new thread for sorting
	std::future<void> sortingThread;
	
	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;

	//Functions
	void pollEvents();
	void update();
	void render();
	void renderUI();

	//rectangle function init
	void initRectangle(int numberOfElements);

	//Sorting algo
	void selectionSort();
	void bubbleSort();
};
