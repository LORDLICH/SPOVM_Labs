#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <time.h>

using namespace std;
int main(int argc, char *argv[])
{
	cout << "This is child" << endl;
	cout << "PID: " << GetCurrentProcessId() << endl;

	auto time = chrono::system_clock::now();

	time_t currentTime = chrono::system_clock::to_time_t(time);

	cout << ctime(&currentTime);

	Sleep(10000);
	return 0;
}