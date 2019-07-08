#include <iostream>
#include <thread>
#include <vector>
#include "platek.cpp"
#include <windows.h>

constexpr unsigned int width = 128;
constexpr unsigned int height = 20;		//ustawilem wysokosc na 20 aby "pojemnik" na platki byl przejrzysty


void ShowConsoleCursor(bool showFlag)   //usuniecie migajacego kursora
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void gotxy(UINT x, UINT y)
{
	COORD coord;
	coord.X = static_cast<SHORT>(x);
	coord.Y = static_cast<SHORT>(y);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printWinterWalls() //drukowanie ramek
{
	for (unsigned int i = 0; i <= height; i++)
	{
		gotxy(0, i);
		std::cout << "|";
		gotxy(width, i);
		std::cout << "|";
	}
	for (unsigned int i = 0; i < width; i++)
	{
		gotxy(i, height + 1);
		std::cout << "-";
	}
}

typedef std::unique_ptr<platek> platekPtr;  //unique_ptr jako wskaznik na obiekt typu platek


int main()
{
	bool threadsKiller = false;
	unsigned char screen[width][height];
	unsigned int sleepTime = 10;
	
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect); 
   	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 1100,400, TRUE);	//zmiana wielkosci konsoli
    
	ShowConsoleCursor(false);

	std::vector<platekPtr> myLovelyPiecesOfSnow;    //vector obiektow(unique_ptr)

	printWinterWalls();

	for (unsigned int i = 0; i < 64; i++)   //czyszczenie pola
	{
		for (unsigned int j = 0; j < 128; j++)
		{
			screen[i][j] = ' ';
		}
	}
	int counter = 1;
	for (int i = 0; i < 16; i++) //tworzenie watkow
	{
		myLovelyPiecesOfSnow.push_back(platekPtr(new platek(&threadsKiller, &screen[0][0], &sleepTime, i + counter, 0)));
		counter += 7;
	}

	counter = 1;
	for (auto & i : myLovelyPiecesOfSnow)   //uruchamianie watkow(roznie opadajace platki)
	{
		if (counter++ % 2 == 0)
			i->makeTheSnowStartsFalling();
		Sleep(10 + counter);
	}
	counter = 1;
	for (auto & i : myLovelyPiecesOfSnow)
	{
		if (counter++ % 2 != 0)
			i->makeTheSnowStartsFalling();
		Sleep(10 + counter);
	}



	while (getchar() != 'q') {}   //konczenie programu
	threadsKiller = true;
	for (auto & i : myLovelyPiecesOfSnow)
	{
		i->waitToStop();
	}
	return 0;
}
