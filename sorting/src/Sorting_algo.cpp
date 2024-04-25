#include "../header/game.hpp"

void Game::selectionSort()
{
	int numberOfElements = rect.size();

	for (int i = 0; i < numberOfElements; i++)
	{
		this->rect[i].setFillColor(sf::Color::Red);
		for (int j = i + 1; j < numberOfElements; j++)
		{
			this->isPause();
			if(this->isterminateSorting()) return;

			this->mtx.lock();
			this->rect[j].setFillColor(sf::Color::Red);
			if (this->rect[i].getSize().y < this->rect[j].getSize().y)
			{
				sf::Vector2f temp = this->rect[i].getSize();
				this->rect[i].setSize(this->rect[j].getSize());
				this->rect[j].setSize(temp);
			}
			this->mtx.unlock();
			std::this_thread::sleep_for(this->delay_ms); // Sleep for the specified duration
			this->rect[j].setFillColor(sf::Color::White);
		}
		this->rect[i].setFillColor(sf::Color::White);
	}
	this->sortingCompleted();
}

void Game::bubbleSort()
{
	int numberOfElements = rect.size();

	for (int i = 0; i < numberOfElements-1; i++)
	{
		for (int j = 0; j < numberOfElements-1-i; j++)
		{
			this->isPause();
			if (this->isterminateSorting()) return;

			this->mtx.lock();
			this->rect[j].setFillColor(sf::Color::Red);
			this->rect[j+1].setFillColor(sf::Color::Red);
			if (this->rect[j].getSize().y < this->rect[j+1].getSize().y)
			{
				sf::Vector2f temp = this->rect[j].getSize();
				this->rect[j].setSize(this->rect[j+1].getSize());
				this->rect[j+1].setSize(temp);
			}
			this->mtx.unlock();
			std::this_thread::sleep_for(this->delay_ms); // Sleep for the specified duration
			this->rect[j].setFillColor(sf::Color::White);
			this->rect[j+1].setFillColor(sf::Color::White);
		}
	}
	this->sortingCompleted();
}

void Game::sortingCompleted()
{
	int numberOfElements = rect.size();

	for (int i = 0; i < numberOfElements; i++)
	{
		this->rect[i].setFillColor(sf::Color::Green);
		std::this_thread::sleep_for(this->delay_ms);
	}
}

void Game::isPause()
{
	while (this->pause == 1 && this->terminateSorting == 0)
	{
		std::this_thread::sleep_for(this->delay_ms);
	}
}

bool Game::isterminateSorting()
{
	if (this->terminateSorting == 1) return true;
	return false;
}
