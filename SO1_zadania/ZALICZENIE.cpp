#include <iostream>
#include <ctype.h>
#include <windows.h>
#include <vector>
#include <string>
#include <sstream>
//nie ma synchronizacji
DWORD WINAPI watek(LPVOID data);

int main()
{
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
		int sum = static_cast<unsigned int>((b - a) / zakr);
		watki2 = sum/zakr;
		int sprawdz = a;
		int licz = 0;
		int watek[100];
		int maxToThread
		
		/*for(unsigned int i = a; i <= b - 1; i += sum)
    	{
        counter++;
        if(i > b || counter == zakr)
            maxToThread = b;
        else
            maxToThread = i + sum;
        watek[counter] = ;
    	}*/
    	
		//TWORZENIE WATKOW
		
		std::vector<HANDLE> watki;
		
		for(int c = 1; c <= watki2; c++)
		{
			if(licz != n-1)
			{
				watek[licz] = a;
				a++;
				licz++;
				if(a == b)
					break;
			}
			HANDLE watek[c] = CreateThread(NULL, 0, watek, NULL, 0, NULL);
			
			watki.push_back(watek[c]);
		}
		//HANDLE watek1 = CreateThread(NULL, 0, watek, NULL, 0, NULL);
	
		if (watek[1] == NULL)
			return 2;
		//std::vector<HANDLE> watki;
		/*for(int c = 1; c <= watki.size(); c++)
		{
			watki.push_back(watek[c]);
		}*/
		

		//CZEKANIE NA WATKI
		WaitForMultipleObjects(static_cast<DWORD>(watki.size()), &watki[0], TRUE, INFINITE);
		
		for (unsigned int i = 0; i < watki.size(); i++)
			CloseHandle(watki[i]);

		//WYSWIETLENIE
		for(int c = 1; c <= watki; c++)
		{
			std::cout << "Liczby: " << tabend << std::endl;
		}
		
		tab2.clear();
		run = 0;
	}
	return 0;
}

DWORD WINAPI watek(LPVOID data)
{
	bool akcja = true;
	
	while (akcja)
	{
		
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
      		tabend[i] = watek[i];
  		}
		
	}
	return 0;
}






