#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <Windows.h>
#include <conio.h>

void main()
{
	unsigned int id = GetCurrentProcessId();
	HANDLE hEvent;
	wchar_t str[20];		
	_itow(id, str, 10);
	hEvent = CreateEvent(NULL, FALSE, FALSE, (LPCSTR)str);

	while (1)
	{
		std::cout << "Child #" << id << std::endl;
		Sleep(1000);
		if (WaitForSingleObject(hEvent, 0) == WAIT_OBJECT_0)
		{
			ResetEvent(hEvent);
			//CloseHandle(hEvent);
			return;
		}
	}
}