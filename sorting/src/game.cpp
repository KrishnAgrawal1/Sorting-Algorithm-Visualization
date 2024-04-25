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
	this->winmain = new sf::RenderWindow(this->videoMode, "Sorting", sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen);

	this->winmain->setFramerateLimit(60);
	this->delay_ms = std::chrono::milliseconds(1);

	this->interface.loadAssetes();
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
				this->winmain->close();
				break;

			case sf::Event::KeyPressed:
				if(this->ev.key.code == sf::Keyboard::Escape) this->winmain->close();
				break;

			case sf::Event::MouseButtonReleased:
				sf::Vector2f mousePosition(ev.mouseButton.x, ev.mouseButton.y);

				if (this->interface.exitBtShape.getGlobalBounds().contains(mousePosition)) this->winmain->close();

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
					this->sortingAlgoUsing = 1;

					this->interface.selectionSortBt.setFillColor(sf::Color::Green);
					this->interface.selectionSortText.setFillColor(sf::Color::Red);

					this->interface.bubbleSortBt.setFillColor(sf::Color::White);
					this->interface.bubbleSortText.setFillColor(sf::Color::Black);
				}

				if (this->interface.bubbleSortBt.getGlobalBounds().contains(mousePosition))
				{
					this->sortingAlgoUsing = 2;

					this->interface.selectionSortBt.setFillColor(sf::Color::White);
					this->interface.selectionSortText.setFillColor(sf::Color::Black);

					this->interface.bubbleSortBt.setFillColor(sf::Color::Green);
					this->interface.bubbleSortText.setFillColor(sf::Color::Red);
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
		sf::Vector2f rectanglePosition((widthOfRacta * i) + padding.x, WINDOW_SIZE.y);

		r.setPosition(rectanglePosition);
		r.setSize(sf::Vector2f(widthOfRacta, -1 * numbers[i] * heightMultiplier));
		r.setFillColor(sf::Color::White);
		r.setOutlineColor(sf::Color::Cyan);
		r.setOutlineThickness(widthOfRacta / 10);

		this->rect.push_back(r);
	}
}


