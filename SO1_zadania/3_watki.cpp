#include <iostream>
#include <ctype.h>
#include <windows.h>
#include <vector>
#include <string>
#include <sstream>

DWORD WINAPI male_litery(LPVOID data);
DWORD WINAPI duze_litery(LPVOID data);
DWORD WINAPI jedna_duza(LPVOID data);

std::string tekst;
std::string male;
std::string duze;
std::string z_duzej;
std::string runn;

HANDLE Semafor;

int main()
{
	//TWORZENIE SEMAFORA
	Semafor = CreateSemaphore(NULL, 1, 1, NULL);
	if (Semafor == NULL) return 1;
	bool run = 1;
	while (run)
	{
		std::cout << "Czy chcesz podac zdanie? T/N : ";
		std::getline(std::cin, runn);
		if(runn == "T")
		{
			run = 1;
		}
		else if(runn == "N")
		{
			run = 0;
			break;
		}
		else
			break;
		//POBIERANIE TEKSTU
		std::cout << "Podaj tekst: ";
		std::getline(std::cin, tekst);
		//if(tekst == "break")
		//	break;
		//std::cin >> tekst;
		male = tekst;
		duze = tekst;
		z_duzej = tekst;

		//TWORZENIE WATKOW
		HANDLE watek1 = CreateThread(NULL, 0, male_litery, NULL, 0, NULL);
		HANDLE watek2 = CreateThread(NULL, 0, duze_litery, NULL, 0, NULL);
		HANDLE watek3 = CreateThread(NULL, 0, jedna_duza, NULL, 0, NULL);
		if (watek1 == NULL || watek2 == NULL || watek3 == NULL) return 2;
		std::vector<HANDLE> watki;
		watki.push_back(watek1);
		watki.push_back(watek2);
		watki.push_back(watek3);

		//CZEKANIE NA WATKI
		WaitForMultipleObjects(static_cast<DWORD>(watki.size()), &watki[0], TRUE, INFINITE);

		for (unsigned int i = 0; i < watki.size(); i++)
			CloseHandle(watki[i]);

		//WYSWIETLENIE
		std::cout << "Male litery: " << male << std::endl;
		std::cout << "Duze litery: " << duze << std::endl;
		std::cout << "Z duzej: " << z_duzej << std::endl;
		tekst.clear();
	}
	CloseHandle(Semafor);
	return 0;
}

DWORD WINAPI male_litery(LPVOID data)
{
	bool akcja = true;
	DWORD rezultat;
	while (akcja)
	{
		rezultat = WaitForSingleObject(Semafor, 0L);
		if (rezultat == WAIT_OBJECT_0)
		{
			akcja = false;
			for (unsigned int i = 0; i < tekst.size(); ++i)
			{
				male[i] = tolower(tekst[i]);
			}
			if (!ReleaseSemaphore(Semafor, 1, NULL)) return 1;
			akcja = false;
		}
	}
	return 0;
}

DWORD WINAPI duze_litery(LPVOID data)
{
	bool akcja = true;
	DWORD rezultat;
	while (akcja)
	{
		rezultat = WaitForSingleObject(Semafor, 0L);
		if (rezultat == WAIT_OBJECT_0)
		{
			akcja = false;
			for (unsigned int i = 0; i < tekst.size(); ++i)
			{
				duze[i] = toupper(tekst[i]);
			}
			if (!ReleaseSemaphore(Semafor, 1, NULL)) return 1;
			akcja = false;
		}
	}
	return 0;
}

DWORD WINAPI jedna_duza(LPVOID data)
{
	bool akcja = true;
	DWORD rezultat;
	while (akcja)
	{
		rezultat = WaitForSingleObject(Semafor, 0L);
		if (rezultat == WAIT_OBJECT_0)
		{
			akcja = false;
			z_duzej[0] = toupper(tekst[0]);
			for (unsigned int i = 1; i < tekst.size(); ++i)
			{
				if ((tekst[i-1]) == ' ')
				{
					z_duzej[i] = toupper(tekst[i]);
				}
				else
				{
					z_duzej[i] = tolower(tekst[i]);
				}
				
			}
			if (!ReleaseSemaphore(Semafor, 1, NULL)) return 1;
			akcja = false;
		}
	}
	return 0;
}




