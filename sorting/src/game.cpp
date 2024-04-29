#include "../header/game.hpp"

//Private Functions
void Game::initializeVariables()
{
	this->winmain = nullptr;
}

void Game::initWindow()
{
	this->pause = 0;
	this->terminateSorting = 0;
	this->sortingAlgoUsing = 1;

	this->videoMode = sf::VideoMode::getDesktopMode();
	//this->videoMode.height -= 10;
	//this->videoMode.width -= 10;
	//sf::Style::Fullscreen
	this->winmain = new sf::RenderWindow(this->videoMode, "Sorting", sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen);

	this->winmain->setFramerateLimit(60);
	this->delay_ms = std::chrono::milliseconds(10);

	this->interface.loadAssetes();

	//this->icon = sf::Image{};
	//this->icon.loadFromFile("icon.png");
	//this->winmain->setIcon(this->icon.getSize().x, this->icon.getSize().y, this->icon.getPixelsPtr());
}

//Constructor
Game::Game()
{
	this->initializeVariables();
	this->initWindow();
}

//Destructor
Game::~Game()
{
	delete this->winmain;
}


//Accessors
const bool Game::running() const
{
	return this->winmain->isOpen();
}


//Functions
void Game::pollEvents()
{
	while (this->winmain->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
			case sf::Event::Closed:
				this->terminateSorting = 1;
				this->winmain->close();
				break;

			case sf::Event::KeyPressed:
				if (this->ev.key.code == sf::Keyboard::Escape)
				{
					this->terminateSorting = 1;
					this->winmain->close();
				}
				break;

			case sf::Event::MouseButtonReleased:
				sf::Vector2f mousePosition(ev.mouseButton.x, ev.mouseButton.y);

				if (this->interface.exitBtShape.getGlobalBounds().contains(mousePosition))
				{
					this->terminateSorting = 1;
					this->winmain->close();
				}

				if (this->interface.startBtShape.getGlobalBounds().contains(mousePosition) && !this->sortingThread.valid())
				{
					switch (this->sortingAlgoUsing)
					{
						case 1:
							sortingThread = std::async(std::launch::async, &Game::selectionSort, this);
							break;

						case 2:
							sortingThread = std::async(std::launch::async, &Game::bubbleSort, this);
							break;

						case 3:
							sortingThread = std::async(std::launch::async, &Game::insertionSort, this);
							break;

						case 4:
							sortingThread = std::async(std::launch::async, &Game::mergeSort, this);
							break;

						case 5:
							sortingThread = std::async(std::launch::async, &Game::QuickSort, this);
							break;

					}
				}

				if (this->interface.pauesBtShape.getGlobalBounds().contains(mousePosition) && this->sortingThread.valid())
					this->pause = this->pause == 0 ? 1 : 0;

				if (this->interface.resetBtShape.getGlobalBounds().contains(mousePosition))
				{
					this->terminateSorting = 1;
					this->rect.clear();
					this->initRectangle(100);
					if (this->sortingThread.valid())
					{
						this->sortingThread.wait();
						this->sortingThread.get(); // Retrieve any potential exceptions thrown by the thread
						this->sortingThread = std::future<void>(); // Reset the future object
					}
					this->terminateSorting = 0;
					this->pause = 0;
				}

				if (this->interface.selectionSortBt.getGlobalBounds().contains(mousePosition))
				{
					this->changeSortingAlgo(this->sortingAlgoUsing,1);
					this->sortingAlgoUsing = 1;
				}

				if (this->interface.bubbleSortBt.getGlobalBounds().contains(mousePosition))
				{
					this->changeSortingAlgo(this->sortingAlgoUsing, 2);
					this->sortingAlgoUsing = 2;
				}

				if (this->interface.insertionBtShape.getGlobalBounds().contains(mousePosition))
				{
					this->changeSortingAlgo(this->sortingAlgoUsing, 3);
					this->sortingAlgoUsing = 3;
				}

				if (this->interface.mergeBtShape.getGlobalBounds().contains(mousePosition))
				{
					this->changeSortingAlgo(this->sortingAlgoUsing, 4);
					this->sortingAlgoUsing = 4;
				}

				if (this->interface.quickBtShape.getGlobalBounds().contains(mousePosition))
				{
					this->changeSortingAlgo(this->sortingAlgoUsing, 5);
					this->sortingAlgoUsing = 5;
				}

 				break;
		}
	}
}

void Game::update()
{
	this->pollEvents();
}

void Game::render()
{
	this->winmain->clear(sf::Color());

	this->renderUI();

	//Dreaw game objects
	mtx.lock();
	for (auto it : rect) this->winmain->draw(it);
	mtx.unlock();

	this->winmain->display();
}

void Game::changeSortingAlgo(int prev, int curr)
{
	switch (prev)
	{
		case 1:
			this->interface.selectionSortBt.setFillColor(this->interface.buttonBorder);
			this->interface.selectionSortText.setFillColor(this->interface.buttonText);
			break;

		case 2:
			this->interface.bubbleSortBt.setFillColor(this->interface.buttonBorder);
			this->interface.bubbleSortText.setFillColor(this->interface.buttonText);
			break;

		case 3:
			this->interface.insertionBtShape.setFillColor(this->interface.buttonBorder);
			this->interface.insertionBtText.setFillColor(this->interface.buttonText);
			break;

		case 4:
			this->interface.mergeBtShape.setFillColor(this->interface.buttonBorder);
			this->interface.mergeBtText.setFillColor(this->interface.buttonText);
			break;

		case 5:
			this->interface.quickBtShape.setFillColor(this->interface.buttonBorder);
			this->interface.quickBtText.setFillColor(this->interface.buttonText);
			break;
	}

	switch (curr)
	{
	case 1:
		this->interface.selectionSortBt.setFillColor(this->interface.buttonBorderSelected);
		this->interface.selectionSortText.setFillColor(this->interface.buttonTextSelected);
		break;

	case 2:
		this->interface.bubbleSortBt.setFillColor(this->interface.buttonBorderSelected);
		this->interface.bubbleSortText.setFillColor(this->interface.buttonTextSelected);
		break;

	case 3:
		this->interface.insertionBtShape.setFillColor(this->interface.buttonBorderSelected);
		this->interface.insertionBtText.setFillColor(this->interface.buttonTextSelected);
		break;

	case 4:
		this->interface.mergeBtShape.setFillColor(this->interface.buttonBorderSelected);
		this->interface.mergeBtText.setFillColor(this->interface.buttonTextSelected);
		break;

	case 5:
		this->interface.quickBtShape.setFillColor(this->interface.buttonBorderSelected);
		this->interface.quickBtText.setFillColor(this->interface.buttonTextSelected);
		break;
	}
}

void Game::renderUI()
{
	this->winmain->draw(this->interface.titalHead);
	this->winmain->draw(this->interface.algoHead);

	this->winmain->draw(this->interface.startBtShape);
	this->winmain->draw(this->interface.startBtText);

	this->winmain->draw(this->interface.pauesBtShape);
	this->winmain->draw(this->interface.pauseBtText);

	this->winmain->draw(this->interface.resetBtShape);
	this->winmain->draw(this->interface.resetBtText);

	this->winmain->draw(this->interface.exitBtShape);
	this->winmain->draw(this->interface.exitBtText);

	this->winmain->draw(this->interface.selectionSortBt);
	this->winmain->draw(this->interface.selectionSortText);

	this->winmain->draw(this->interface.bubbleSortBt);
	this->winmain->draw(this->interface.bubbleSortText);

	this->winmain->draw(this->interface.insertionBtShape);
	this->winmain->draw(this->interface.insertionBtText);

	this->winmain->draw(this->interface.mergeBtShape);
	this->winmain->draw(this->interface.mergeBtText);

	this->winmain->draw(this->interface.quickBtShape);
	this->winmain->draw(this->interface.quickBtText);
}

//rectangle function init
void Game::initRectangle(int numberOfElements)
{
	std::vector<int> numbers(numberOfElements);

	for (int i = 0; i < numberOfElements; ++i) {
		numbers[i] = i + 1;
	}

	// Shuffle the vector
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(numbers.begin(), numbers.end(), gen);

	sf::Vector2u WINDOW_SIZE(videoMode.width, videoMode.height);
	sf::Vector2u padding{ 100,100 };
	int verticalGap = 200;

	float widthOfRacta = (WINDOW_SIZE.x - padding.x - padding.y) / numberOfElements;
	float heightMultiplier = (WINDOW_SIZE.y - verticalGap) / numberOfElements;

	for (int i = 0; i < numberOfElements; i++)
	{
		sf::RectangleShape r;
		sf::Vector2f rectanglePosition((widthOfRacta * i) + padding.x, WINDOW_SIZE.y-50);

		r.setPosition(rectanglePosition);
		r.setSize(sf::Vector2f(widthOfRacta, -1 * numbers[i] * heightMultiplier));
		r.setFillColor(sf::Color::White);
		r.setOutlineColor(sf::Color::Cyan);
		r.setOutlineThickness(widthOfRacta / 10);

		this->rect.push_back(r);
	}
}


