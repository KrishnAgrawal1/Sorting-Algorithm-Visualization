#pragma once

#include "resources.hpp"
#include "ui.hpp"
#include "audio.hpp"

class Game
{
private:
	sf::RenderWindow* winmain;
	sf::Event ev;
	sf::VideoMode videoMode;
	std::chrono::milliseconds delay_ms;
	sf::Image icon;

	bool pause;
	bool terminateSorting;
	int sortingAlgoUsing;

	//vector of height
	std::vector<sf::RectangleShape> rect;

	//mutex
	std::mutex mtx;

	//ui
	ui interface;
	Audio sound;

	//Private Functions
	void initializeVariables();
	void initWindow();

	void sortingCompleted();

	void isPause();
	bool isterminateSorting();

	void changeSortingAlgo(int prev, int curr);

	//Sorting algo
	void selectionSort();
	void bubbleSort();
	void insertionSort();
	void mergeSort();
	void QuickSort();

	void helperMergeSort(int begin, int end);
	void helperMerge(int begin, int mid, int end);

	void helperQuickSort(int begin, int end);
	int partition(int begin, int end);

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
};

