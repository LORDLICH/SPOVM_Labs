#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <locale.h>
#include <string>
#include <vector>

using namespace std;
void main()
{
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi;
	HANDLE *piArray = new HANDLE;
	ZeroMemory(&pi, sizeof(pi));
	int size = -1;
	HANDLE hEvent1;   
	vector<HANDLE*> eventVector;  
	DWORD *idArray = new DWORD;
	char temp;


	cout << "'+' - add process" << endl
		<< "'-' - kill process" << endl
		<< "'q' - exit" << endl;
	while (1)
	{
		temp = _getch();
		switch (temp)
		{
		case '+':

			if (!CreateProcess(NULL,
				(LPSTR)"Child.exe",
				NULL,
				NULL,
				TRUE,
				NORMAL_PRIORITY_CLASS,
				NULL,
				NULL,
				&si,
				&pi))
			{
				printf("System error code: %i\n", GetLastError());
				system("pause");
			}
			else
			{
				size++;
				idArray[size] = pi.dwProcessId;
				wchar_t str[20];
				_itow_s(idArray[size], str, 10);
				hEvent1 = CreateEvent(NULL, FALSE, FALSE, (LPCSTR)str); 
				eventVector.push_back(new HANDLE(hEvent1));
				std::cout << "Child successfully created!" << std::endl;
			}
			break;

		case '-':
			SetEvent(*(eventVector.back())); 

			CloseHandle(eventVector.back());
			delete eventVector.back();
			eventVector.pop_back();

			CloseHandle(pi.hProcess);
			size--;
			if (size >= 0)
			{
				pi.hProcess = piArray[size];
				pi.dwProcessId = idArray[size];
			}
			std::cout << "Last created process has been terminated!" << std::endl;
			break;


		case 'q':
			while (size >= 0) {
				SetEvent(*(eventVector.back()));
				Sleep(1000);
				CloseHandle(eventVector.back());
				delete eventVector.back();
				eventVector.pop_back();

				CloseHandle(pi.hProcess);
				size--;
				if (size >= 0)
				{
					pi.hProcess = piArray[size];
					pi.dwProcessId = idArray[size];
				}
				
				
			}
			std::cout << "All processes has been terminated!" << std::endl;
			return;
		default:
			break;
		}
	}

}