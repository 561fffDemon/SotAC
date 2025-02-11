#pragma once
#include <iostream>
#include <windows.h>
#include <sstream>
#include <thread>

// Global functions for creating other functions

using namespace std;

void wait(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void xy(int x, int y) {
	COORD pos = { x,y };
	HANDLE o = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(o, pos);
}

COORD getSize() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD SIZE;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	SIZE = { (short)(csbi.srWindow.Right - csbi.srWindow.Left + 1), (short)(csbi.srWindow.Right - csbi.srWindow.Top + 1) };
	return SIZE;
}

void clear() {
	COORD TopLeft = { 0,0 };
	DWORD written;
	CONSOLE_SCREEN_BUFFER_INFO screen;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, TopLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, TopLeft, &written
	);
	xy(0, 0);
}