#include "platek.h"

platek::platek(bool * switcher, unsigned char * gimmeArray, unsigned int * sleepingTime, unsigned int x, unsigned int y) : x_(x), y_(y), arr(gimmeArray)
{

	dontStopMe = switcher;
	sleepingTime_ = sleepingTime;
	startingX = x;
	saveNewToArray();
}

std::mutex platek::mtx;

bool platek::dealWithMovement()
{
	if (!getLow())
	{
		if (!WhereDoYouGo())
			return false;
	}
	else
		randomlyMoveLeftorRight();
	return true;
}

void platek::makeTheSnowStartsFalling()
{
	iMovesLikeaJagger = new std::thread(&platek::youSpinMeRoundTheThread, this);
}

void platek::eraseFromArray()
{
	*(arr + (y_ * xsize) + x_) = ' ';
}
void platek::saveNewToArray()
{
	*(arr + (y_ * xsize) + x_) = 'x';
}

void platek::gotxy(UINT x, UINT y)
{
	COORD coord;
	coord.X = static_cast<SHORT>(x);
	coord.Y = static_cast<SHORT>(y);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void platek::randomlyMoveLeftorRight()
{
	srand(time(nullptr));
	if (80 < (rand() % 101)) // 20% szans na poruszenie
	{
		if (*(arr + (y_ * xsize) + x_ + 1) != 'x' && *(arr + (y_ * xsize) + x_ - 1) != 'x')
		{
			if ((rand() % 3) == 1)
			{
				moveToTheLeft();
			}
			else
			{
				moveToTheRight();
			}
		}
		else if (*(arr + (y_ * xsize) + x_ + 1) != 'x')
			moveToTheRight();
		else
			moveToTheLeft();
	}
}

bool platek::WhereDoYouGo()
{
	bool howDoYouDo = false;
	if (y_ < ysize)
	{
		if (*(arr + ((y_ + 1) * xsize) + x_ - 1) != 'x' && *(arr + ((y_ + 1) * xsize) + x_ + 1) != 'x' && x_ > 1 && x_ < xsize)
		{
			if ((rand() % 3) == 1)
			{
				howDoYouDo = moveToTheLeft();
			}
			else
			{
				howDoYouDo = moveToTheRight();
			}
		}
		else if (*(arr + ((y_ + 1) * xsize) + x_ - 1) != 'x' && x_ > 1)
			howDoYouDo = moveToTheLeft();
		else if (*(arr + ((y_ + 1) * xsize) + x_ + 1) != 'x' && x_ < xsize)
			howDoYouDo = moveToTheRight();
	}
	return howDoYouDo;
}


bool platek::moveToTheRight()
{
	mtx.lock();
	if (x_ < xsize - 1 && *(arr + (y_ * xsize) + x_ + 1) != 'x')
	{
		eraseFromArray();
		gotxy(x_, y_);
		std::cout << ' ';
		x_++;
		gotxy(x_, y_);
		std::cout << 'x';
		saveNewToArray();
		mtx.unlock();
		return true;

	}
	mtx.unlock();
	return false;
}
bool platek::moveToTheLeft()
{
	mtx.lock();
	if (x_ > 1 && *(arr + (y_ * xsize) + x_ - 1) != 'x')
	{
		eraseFromArray();
		gotxy(x_, y_);
		std::cout << ' ';
		x_--;
		gotxy(x_, y_);
		std::cout << 'x';
		saveNewToArray();
		mtx.unlock();
		return true;

	}
	mtx.unlock();
	return false;
}
bool platek::getLow()
{
	mtx.lock();
	if (*(arr + ((y_ + 1) * xsize) + x_) != 'x' && y_ < ysize)
	{
		eraseFromArray();
		gotxy(x_, y_);
		std::cout << " ";
		y_++;
		saveNewToArray();
		gotxy(x_, y_);
		std::cout << "x";
		Sleep(30);
		mtx.unlock();
		return true;
	}
	mtx.unlock();
	return false;
}

void platek::spawnNewBeautifulPieceOfSnow()
{
	mtx.lock();
	y_ = 0;
	x_ = startingX;
	saveNewToArray();
	mtx.unlock();

}

void platek::youSpinMeRoundTheThread()
{
	while (!*dontStopMe)
	{
		if (!dealWithMovement())
			spawnNewBeautifulPieceOfSnow();
		Sleep(*sleepingTime_);
	}
}

void platek::waitToStop()
{
	iMovesLikeaJagger->join();

}

platek::~platek()
{
	delete iMovesLikeaJagger;
}