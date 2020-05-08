#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <time.h>

using namespace std;
int main(int argc, char *argv[])
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	TCHAR SecondProcess[] = TEXT("secondProcess");
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(argv[1],
		argv[2],
		NULL,
		NULL,
		TRUE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si,
		&pi))
		printf("CreateProcess failed\n");

	WaitForSingleObject(pi.hProcess, 2000);

	cout << "This is parent" << endl;
	cout << "Descr: " << (int)pi.hProcess << endl << "ID: " << (int)pi.dwProcessId << endl;

	auto time = chrono::system_clock::now();

	time_t currentTime = chrono::system_clock::to_time_t(time);

	cout << ctime(&currentTime);

	cout << endl;

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return 0;
}