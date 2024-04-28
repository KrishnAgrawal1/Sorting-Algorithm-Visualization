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
			sound.play(0.5 + (j*0.01));
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

			sound.play(0.5 + (j * 0.01));

			std::this_thread::sleep_for(this->delay_ms); // Sleep for the specified duration
			this->rect[j].setFillColor(sf::Color::White);
			this->rect[j+1].setFillColor(sf::Color::White);
		}
	}
	this->sortingCompleted();
}



void Game::insertionSort()
{
	int numberOfElements = rect.size();
	int j;
	sf::Vector2f key;
	for (int i = 1; i < numberOfElements; i++) 
	{
		key = this->rect[i].getSize();
		j = i - 1;

		while (j >= 0 && this->rect[j].getSize().y < key.y) 
		{
			this->isPause();
			if (this->isterminateSorting()) return;

			this->rect[j + 1].setFillColor(sf::Color::Red);

			sound.play(0.5 + (j * 0.01));
			std::this_thread::sleep_for(this->delay_ms);

			this->rect[j+1].setSize(this->rect[j].getSize());

			this->rect[j + 1].setFillColor(sf::Color::White);

			j = j - 1;
					
		}

		this->rect[j+1].setSize(key);
	}
	this->sortingCompleted();
}



void Game::mergeSort()
{
	int numberOfElements = this->rect.size();
	this->helperMergeSort(0,numberOfElements-1);

	this->isPause();
	if (this->isterminateSorting()) return;

	this->sortingCompleted();
}

void Game::helperMergeSort(int begin, int end)
{
	if (begin >= end) return;

	int mid = begin + (end - begin) / 2;
	this->helperMergeSort(begin, mid);
	this->helperMergeSort(mid+1, end);

	this->isPause();
	if (this->isterminateSorting()) return;

	this->helperMerge(begin, mid, end);
}

void Game::helperMerge(int begin, int mid, int end)
{
	int i, j, k;
	int n1 = mid - begin + 1;
	int n2 = end - mid;

	int x = this->rect[1].getSize().x;

	std::vector<int> left(n1);
	std::vector<int> right(n2);

	for (i = 0; i < n1; i++)
	{
		this->isPause();
		if (this->isterminateSorting()) return;

		this->rect[begin + i].setFillColor(sf::Color::Red);
		sound.play(0.5 + (i * 0.01));
		std::this_thread::sleep_for(this->delay_ms);

		left[i] = this->rect[begin + i].getSize().y;
		this->rect[begin + i].setFillColor(sf::Color::White);

	}
	for (j = 0; j < n2; j++)
	{
		this->isPause();
		if (this->isterminateSorting()) return;

		this->rect[mid + j + 1].setFillColor(sf::Color::Red);
		sound.play(0.5 + (j * 0.01));
		std::this_thread::sleep_for(this->delay_ms);

		right[j] = this->rect[mid + j + 1].getSize().y;
		this->rect[mid + j + 1].setFillColor(sf::Color::White);

	}

	i = 0;
	j = 0;
	k = begin;

	while (i < n1 && j < n2)
	{
		this->isPause();
		if (this->isterminateSorting()) return;

		if (left[i] > right[j])
			this->rect[k++].setSize(sf::Vector2f(x,left[i++]));
		else
			this->rect[k++].setSize(sf::Vector2f(x,right[j++]));

		this->rect[k-1].setFillColor(sf::Color::Red);
		sound.play(0.5 + (k * 0.01));
		std::this_thread::sleep_for(this->delay_ms);
		this->rect[k-1].setFillColor(sf::Color::White);

	}

	while (i < n1)
	{
		this->isPause();
		if (this->isterminateSorting()) return;

		this->rect[k++].setSize(sf::Vector2f(x, left[i++]));

		this->rect[k - 1].setFillColor(sf::Color::Red);
		sound.play(0.5 + (i * 0.01));
		std::this_thread::sleep_for(this->delay_ms);
		this->rect[k - 1].setFillColor(sf::Color::White);
	}

	while (j < n2)
	{
		this->isPause();
		if (this->isterminateSorting()) return;

		this->rect[k++].setSize(sf::Vector2f(x, right[j++]));

		this->rect[k - 1].setFillColor(sf::Color::Red);
		sound.play(0.5 + (j * 0.01));
		std::this_thread::sleep_for(this->delay_ms);
		this->rect[k - 1].setFillColor(sf::Color::White);
	}
}




void Game::QuickSort()
{
	int numberOfElements = this->rect.size();
	this->helperQuickSort(0, numberOfElements - 1);

	this->isPause();
	if (this->isterminateSorting()) return;

	this->sortingCompleted();
}

void Game::helperQuickSort(int begin, int end)
{
	if (begin >= end) return;

	int piviot = partition(begin, end);

	this->isPause();
	if (this->isterminateSorting()) return;

	helperQuickSort(begin, piviot - 1);
	helperQuickSort(piviot + 1, end);
}

int Game::partition(int begin, int end)
{
	int piviot = this->rect[end].getSize().y;

	int i = begin;

	for (int j = begin; j <= end; j++)
	{
		//this->isPause();
		//if (this->isterminateSorting()) return -1;

		this->rect[i].setFillColor(sf::Color::Red);
		this->rect[j].setFillColor(sf::Color::Red);

		sound.play(0.5 + (j * 0.01));
		std::this_thread::sleep_for(this->delay_ms);

		if (this->rect[j].getSize().y > piviot)
		{
			sf::Vector2f temp = this->rect[i].getSize();
			this->rect[i].setSize(this->rect[j].getSize());
			this->rect[j].setSize(temp);

			this->rect[i].setFillColor(sf::Color::White);
			i++;
		}
				
		this->rect[j].setFillColor(sf::Color::White);
	}
	this->rect[end].setFillColor(sf::Color::Red);
	this->rect[i].setFillColor(sf::Color::Red);

	sf::Vector2f temp = this->rect[i].getSize();
	this->rect[i].setSize(this->rect[end].getSize());
	this->rect[end].setSize(temp);

	std::this_thread::sleep_for(this->delay_ms);
	this->rect[i].setFillColor(sf::Color::White);
	this->rect[end].setFillColor(sf::Color::White);

	return i;
}



void Game::sortingCompleted()
{
	int numberOfElements = rect.size();

	for (int i = 0; i < numberOfElements; i++)
	{
		this->rect[i].setFillColor(sf::Color::Green);
		std::this_thread::sleep_for(this->delay_ms);
		sound.play(0.5 + (i * 0.01));
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
