#ifndef PLATEK_H
#define PLATEK_H
#include <thread>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <mutex>


constexpr unsigned int xsize = 128;
constexpr unsigned int ysize = 20;

class platek
{
	unsigned int x_, y_;
	unsigned char * arr;
	unsigned int * sleepingTime_;
	unsigned int startingX;

	std::thread * iMovesLikeaJagger;
	bool * dontStopMe;
	void youSpinMeRoundTheThread();
	bool dealWithMovement();
	void randomlyMoveLeftorRight();
	void spawnNewBeautifulPieceOfSnow();
	bool moveToTheRight();
	bool moveToTheLeft();
	bool WhereDoYouGo();
	bool getLow();
	void eraseFromArray();
	void saveNewToArray();
	void gotxy(UINT x, UINT y);
public:
	static std::mutex mtx;
	void makeTheSnowStartsFalling();
	void waitToStop();
	explicit platek(bool * switcher, unsigned char * gimmeArray, unsigned int * sleepingTime, unsigned int x, unsigned int y);
	~platek();
};
#endif // PLATEK_H
