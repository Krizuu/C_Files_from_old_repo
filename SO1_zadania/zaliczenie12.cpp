#include <iostream>
#include <ctype.h>
#include <windows.h>
#include <vector>
#include <string>
#include <sstream>

DWORD WINAPI watek1(LPVOID data);
DWORD WINAPI watek2(LPVOID data);
DWORD WINAPI watek3(LPVOID data);
DWORD WINAPI watek4(LPVOID data);


HANDLE Semafor;

int main()
{
	//TWORZENIE SEMAFORA
	Semafor = CreateSemaphore(NULL, 1, 1, NULL);
	if (Semafor == NULL) return 1;
	bool run = 1;
	int a, b, zakr;
	
	std::cout << "Podaj przedzial od : ";
	std::cin >> a;
	std::cout << "Podaj przedzial do : ";
	std::cin >> b;
	std::cout << "Jaki zakres : ";
	std::cin >> zakr;
	
	while (run)
	{
		
		int watki2 = 0;
		int sum = (b - a) + 1;
		watki2 = sum/zakr;
		int sprawdz = a;
		int licz = 0;
		int tab[100];
		
		for(int k = a; k <= b; k++)
		{
			tab[licz]=k;
			licz++;
		}
		
		licz = licz;
		int licz2 = licz / 2;
		
		//TWORZENIE WATKOW
		if(zakr == 1)
		{
			HANDLE watek1 = CreateThread(NULL, 0, watek, NULL, 0, NULL);
			
			if (watek1 == NULL) return 2;
			std::vector<HANDLE> watki;
			watki.push_back(watek1);
		}
		else if(zakr == 2)
		{
			int tab2[]
			HANDLE watek1 = CreateThread(NULL, 0, watek, NULL, 0, NULL);
			HANDLE watek2 = CreateThread(NULL, 0, watek, NULL, 0, NULL);
			
			if (watek1 == NULL || watek2 == NULL) return 2;
			std::vector<HANDLE> watki;
			watki.push_back(watek1);
			watki.push_back(watek2);
		}
		else if(zakr == 3)
		{
			HANDLE watek1 = CreateThread(NULL, 0, watek, NULL, 0, NULL);
			HANDLE watek2 = CreateThread(NULL, 0, watek, NULL, 0, NULL);
			HANDLE watek3 = CreateThread(NULL, 0, watek, NULL, 0, NULL);
			
			if (watek1 == NULL || watek2 == NULL || watek3 == NULL) return 2;
			std::vector<HANDLE> watki;
			watki.push_back(watek1);
			watki.push_back(watek2);
			watki.push_back(watek3);
		}
		else if(zakr == 4)
		{
			HANDLE watek1 = CreateThread(NULL, 0, watek, NULL, 0, NULL);
			HANDLE watek2 = CreateThread(NULL, 0, watek, NULL, 0, NULL);
			HANDLE watek3 = CreateThread(NULL, 0, watek, NULL, 0, NULL);
			HANDLE watek4 = CreateThread(NULL, 0, watek, NULL, 0, NULL);
			
			if (watek1 == NULL || watek2 == NULL || watek3 == NULL || watek4 == NULL) return 2;
			std::vector<HANDLE> watki;
			watki.push_back(watek1);
			watki.push_back(watek2);
			watki.push_back(watek3);
			watki.push_back(watek4);
		}
		
	
		//CZEKANIE NA WATKI
		WaitForMultipleObjects(static_cast<DWORD>(watki.size()), &watki[0], TRUE, INFINITE);

		for (unsigned int i = 0; i < watki.size(); i++)
			CloseHandle(watki[i]);

		//WYSWIETLENIE
		if(zakr == 1)
		{
			std::cout << "Obliczenia: " << tab << std::endl;
			tab.clear();
		}
		if(zakr == 2)
		{
			std::cout << "Obliczenia: " << tab << std::endl;
			std::cout << "Obliczenia: " << tab << std::endl;
			tab.clear();
		}
		if(zakr == 3)
		{
			std::cout << "Obliczenia: " << tab << std::endl;
			std::cout << "Obliczenia: " << tab << std::endl;
			std::cout << "Obliczenia: " << tab << std::endl;
			tab.clear();
		}
		if(zakr == 4)
		{
			std::cout << "Obliczenia: " << tab << std::endl;
			std::cout << "Obliczenia: " << tab << std::endl;
			std::cout << "Obliczenia: " << tab << std::endl;
			std::cout << "Obliczenia: " << tab << std::endl;
			tab.clear();
		}
		
	}
	CloseHandle(Semafor);
	run = 0;
	return 0;
}

DWORD WINAPI watek1(LPVOID data)
{
	bool akcja = true;
	DWORD rezultat;
	while (akcja)
	{
		rezultat = WaitForSingleObject(Semafor, 0L);
		
		for(unsigned int i = a; i < b; i++)
  		{
      		flag = true;
      		for(unsigned int j = 2; j < i && flag; j++)
      		{
          		if(i % j == 0)
          		{
             		flag = false;
          		}
      		}
      		if(flag)
      		{
          		numVec->push_back(i);
      		}
  }
		if (rezultat == WAIT_OBJECT_0)
		{
			akcja = false;
			for (unsigned int i = 1; i < tab.size(); ++i)
			{
				tabend[i] = tab[i];
			}
			if (!ReleaseSemaphore(Semafor, 1, NULL)) return 1;
			akcja = false;
		}
	}
	return 0;
}

DWORD WINAPI watek2(LPVOID data)
{
	bool akcja = true;
	DWORD rezultat;
	while (akcja)
	{
		rezultat = WaitForSingleObject(Semafor, 0L);
		
		for(unsigned int i = a; i < b; i++)
  		{
      		flag = true;
      		for(unsigned int j = 2; j < i && flag; j++)
      		{
          		if(i % j == 0)
          		{
             		flag = false;
          		}
      		}
      		if(flag)
      		{
          		numVec->push_back(i);
      		}
  }
		if (rezultat == WAIT_OBJECT_0)
		{
			akcja = false;
			for (unsigned int i = 1; i < tab.size(); ++i)
			{
				tabend[i] = tab[i];
			}
			if (!ReleaseSemaphore(Semafor, 1, NULL)) return 1;
			akcja = false;
		}
	}
	return 0;
}

DWORD WINAPI watek3(LPVOID data)
{
	bool akcja = true;
	DWORD rezultat;
	while (akcja)
	{
		rezultat = WaitForSingleObject(Semafor, 0L);
		
		for(unsigned int i = a; i < b; i++)
  		{
      		flag = true;
      		for(unsigned int j = 2; j < i && flag; j++)
      		{
          		if(i % j == 0)
          		{
             		flag = false;
          		}
      		}
      		if(flag)
      		{
          		numVec->push_back(i);
      		}
  }
		if (rezultat == WAIT_OBJECT_0)
		{
			akcja = false;
			for (unsigned int i = 1; i < tab.size(); ++i)
			{
				tabend[i] = tab[i];
			}
			if (!ReleaseSemaphore(Semafor, 1, NULL)) return 1;
			akcja = false;
		}
	}
	return 0;
}

DWORD WINAPI watek4(LPVOID data)
{
	bool akcja = true;
	DWORD rezultat;
	while (akcja)
	{
		rezultat = WaitForSingleObject(Semafor, 0L);
		
		for(unsigned int i = a; i < b; i++)
  		{
      		flag = true;
      		for(unsigned int j = 2; j < i && flag; j++)
      		{
          		if(i % j == 0)
          		{
             		flag = false;
          		}
      		}
      		if(flag)
      		{
          		numVec->push_back(i);
      		}

  }
		if (rezultat == WAIT_OBJECT_0)
		{
			akcja = false;
			for (unsigned int i = 1; i < tab.size(); ++i)
			{
				tabend[i] = tab[i];
			}
			if (!ReleaseSemaphore(Semafor, 1, NULL)) return 1;
			akcja = false;
		}
	}
	return 0;
}






