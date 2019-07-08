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
	HANDLE sem_user = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "sem_i_am_ready");
	if (sem_user == NULL)
	{
		printf("Proces interfejsu uzytkownika nie jest uruchomiony...");
		return 1;
	}
	ReleaseSemaphore(sem_user, 1, NULL);
	CloseHandle(sem_user);
	// otwórz pamiêæ wspó³dzielon¹
	HANDLE file_map_handle = OpenFileMapping(FILE_MAP_ALL_ACCESS, false, "so1_calc_data");
	if(file_map_handle == NULL)
	{
		printf("Last error code: (%d)\n", GetLastError());
		return 1;
	}
	ipc_data_t *pdata = (ipc_data_t*)MapViewOfFile(file_map_handle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(ipc_data_t));
	if (pdata == NULL)
	{
		printf("Last error code: (%d)\n", GetLastError());
		CloseHandle(file_map_handle);
		return 1;
	}
	HANDLE sem_execute = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "sem_execute");
	if(sem_execute==NULL)
	{
		printf("Last error code: (%d)\n", GetLastError());
		CloseHandle(file_map_handle);
		UnmapViewOfFile(pdata);
		return 1;
	}
	HANDLE sem_results = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "sem_results");
	if(sem_results==NULL)
	{
		printf("Last error code: (%d)\n", GetLastError());
		CloseHandle(file_map_handle);
		UnmapViewOfFile(pdata);
		CloseHandle(sem_execute);
		return 1;
	}
	while (true)
	{
		printf("Czekam na uzytkownika...\n");
		WaitForSingleObject(sem_execute, INFINITE);
		// walidacja
		if(strchr("+-*/", pdata->op) == NULL)
		{
			pdata->success = false;
			strcpy(pdata->error_message, "Nieznana operacja");
		}
		else

			if (pdata->val2 == 0.0f && pdata->op == '/')
			{
				pdata->success = false;
				strcpy(pdata->error_message, "Blad dzielenia przez zero");
			}
			else
			{
				if (pdata->op == '+')
					pdata->result = pdata->val1 + pdata->val2;
				if (pdata->op == '-')
					pdata->result = pdata->val1 - pdata->val2;
				if (pdata->op == '/')
					pdata->result = pdata->val1 / pdata->val2;
				if (pdata->op == '*')
					pdata->result = pdata->val1 * pdata->val2;
				pdata->success = true;
			}
		printf("Informuje proces uzytkownika, ze robota skonczona.\n");
		ReleaseSemaphore(sem_results, 1, NULL);
	}
}
