#include <stdio.h>
#include <assert.h>
#include <windows.h>
struct ipc_data_t
{
	float val1, val2, result;
	char op;
	bool success;
	char error_message[1024];
};
int main()
{
	// FAZA 1. Przygotuj zasoby wykorzystywne w komunikacji IPC
	// Wszystkie elementy musz� by� gotowe zanim utworzony zostanie semafor "sem_i_am_ready".
	// Dzi�ki temu unikniemy nieporz�dku w kodzie, gdzie jeden proces tworzy cze�� zasob�w wsp� dzielonych
	// a chwil� p�niej drugi robi to samo.

	// przygotuj semafory do przep�ywu sterowania wykonywaniem obu program�w
	HANDLE sem_execute = CreateSemaphore(NULL, 0, 1, "sem_execute");
	assert(sem_execute != NULL); // uproszczona kontrola b��d�w
	HANDLE sem_results = CreateSemaphore(NULL, 0, 1, "sem_results");
	assert(sem_results != NULL); // uproszczona kontrola b��d�w
	// przygotuj blok wsp�lnej pami�ci
	// - plik mapowany
	HANDLE file_map_handle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL,
		PAGE_READWRITE, 0, sizeof(ipc_data_t), "so1_calc_data");
	if (file_map_handle == NULL)
	{
		printf("Last error code: (%d)\n", GetLastError());
		CloseHandle(sem_execute);
		CloseHandle(sem_results);
		return 1;
	}
	// mapuj fragment pliku
	ipc_data_t *pdata = (ipc_data_t*)MapViewOfFile(file_map_handle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(ipc_data_t));
	if (pdata == NULL)
	{
		printf("Last error code: (%d)\n", GetLastError());
		CloseHandle(file_map_handle);
		CloseHandle(sem_execute);
		CloseHandle(sem_results);
		return 1;
	}  
	// FAZA 2. Czekaj na proces licz�cy
	// Uwaga! Utworzenie tego semafora jest granic� rozdzielaj�c� faz� przygotowania
	// zaob�w wsp�dzielonych i ich u�ywania
	printf("Oczekiwanie na proces liczacy: ");
	HANDLE sem_waiter = CreateSemaphore(NULL, 0, 1, "sem_i_am_ready"); // domy�lnie niesygnalizu�cy
	if(sem_waiter==NULL)
	{
		printf("Last error code: (%d)\n", GetLastError());
		CloseHandle(file_map_handle);
		CloseHandle(sem_execute);
		CloseHandle(sem_results);
		UnmapViewOfFile(pdata);
		return 1;
	}
	while(true)
	{
		DWORD result = WaitForSingleObject(sem_waiter, 1000);
		if (result == WAIT_OBJECT_0)
			break;
		printf(".");
	}
	printf("Ok!\n");
	CloseHandle(sem_waiter);
	while(true)
	{
		printf("Podaj liczbe A: ");
		int n1 = scanf("%f", &pdata->val1);
		printf("Podaj liczbe B: ");
		int n2 = scanf("%f", &pdata->val2);
		printf("Podaj operacje (+, -, /, * lub q zeby wyjsc): ");
		int n3 = scanf("%*c%c", &pdata->op);
		if(!n1 || !n2 || !n3)
		{
			printf("Blad danych wejsciowych; spodziewane dwie liczby oraz operator");
			UnmapViewOfFile(pdata);
			CloseHandle(file_map_handle);
			CloseHandle(sem_execute);
			CloseHandle(sem_results);
			return 1;
		}
		if(pdata->op == 'q')
		{
			UnmapViewOfFile(pdata);
			CloseHandle(file_map_handle);
			CloseHandle(sem_execute);
			CloseHandle(sem_results);
			exit(0);
		}
		// sygnalizuj start oblicze�
		ReleaseSemaphore(sem_execute, 1, NULL);
		// czekaj na wyniki
		WaitForSingleObject(sem_results, INFINITE);
		if(pdata->success)
			printf("Wynik: %f %c %f = %f\n", pdata->val1, pdata->op, pdata->val2, pdata->result);
		else
			printf("Blad  %f %c %f = %s\n", pdata->val1, pdata->op, pdata->val2, pdata->error_message);
	}
}
