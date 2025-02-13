#pragma once
#include <iostream>
#include "engine.h"
#include <windows.h>
#include <sstream>
#include <thread>
#include <iomanip>

// Functions for Visual/Gameplay
int delay = 25;

void TextAnim_WRITE(string text, int ms) {
	for (int i = 0; i < text.size(); i++) {
		cout << text[i];
		wait(ms);
	}
}

void split(string Title, char Fill, int StartY, int Mode) {
	COORD position = getSize();
	int w = (int)(position.X);
	int h = (int)(position.Y);

	xy(0, StartY);
	for (int i = 0; i < w; i++) {
		cout << Fill;
	}
	switch (Mode) {
	case 1:
		xy(((int)(w / 2) - (int)(Title.size() / 2) - 3), StartY - 1);
		break;
	case 2:
		xy(((int)(w / 2) - (int)(Title.size() / 2) - 3), StartY + 1);
		break;
	default:
		cout << "Choice any mode (1 - Title under split screen, 2 - Title upper split screen)";
		break;
	}
	cout << "[ " << Title << " ]";
}

void PrintList(int x, int y, int margin, int size, string* List) {
	for (int i = 0; i < size; i++) {
		xy(x, y + (margin * i));
		cout << List[i];
	}
	xy(0, 0);
}

// Functions of game status (Menu/Story/Settings and more)

void Game() {
	clear();
	cout << "GAME";
}

void Menu();
void Settings();

void TextSpeedMenu() {
	clear();
	split("Playback speed (delay)", '-', 3, 1);
	xy(0, 0);

	string List[20] =
	{ "*-------------------", "**------------------", "***-----------------", "****----------------",
	"*****---------------", "******--------------", "*******-------------", "********------------",
	"*********-----------", "**********----------", "***********---------", "************--------",
	"*************-------", "**************------", "***************-----", "****************----",
	"*****************---", "******************--", "*******************-", "********************"
	};

	int selected = delay / 25 - 1;
	bool quit = false;
	xy(10, 6);
	cout << List[selected] << " " << delay;
	xy(0, 0);
	wait(100);

	while (!quit) {
		if (GetKeyState(VK_RIGHT) & 0x8000) {
			selected++;
			delay += 25;
			if (selected >= 20) {
				selected = 0;
				delay = 25;
			}

			xy(10, 6);
			cout << List[selected] << " " << setw(3) << delay;
			xy(0, 0);
			wait(100);
		};
		if (GetKeyState(VK_LEFT) & 0x8000) {
			selected--;
			delay -= 25;
			if (selected <= -1) {
				selected = 19;
				delay = 500;
			}

			xy(10, 6);
			cout << List[selected] << " " << setw(3) << delay;
			xy(0, 0);
			wait(100);
		};
		if (GetKeyState(VK_RETURN) & 0x8000) {
			wait(100);
			clear();
			Settings();
			quit = true;
			xy(0, 0);
			wait(100);
		}
	}
}

void Settings() {
	clear();
	split("Settings", '-', 3, 1);
	xy(0, 0);

	string List[3] = { "Language", "Playback speed (delay)", "Return to Menu" };
	PrintList(10, 6, 2, 3, List);

	int selected = 0;
	int previous = 0;
	bool quit = false;

	xy(10, 6 + (selected * 2));
	cout << "> " << List[selected];
	xy(0, 0);
	while (!quit) {
		if (GetKeyState(VK_DOWN) & 0x8000) {
			previous = selected++;
			if (selected >= 3) {
				selected = 0;
			}

			xy(10, 6 + (selected * 2));
			cout << "> " << List[selected];
			xy(10, 6 + (previous * 2));
			cout << "" << List[previous] << "  ";
			xy(0, 0);
			wait(100);
		};
		if (GetKeyState(VK_UP) & 0x8000) {
			previous = selected--;
			if (selected <= -1) {
				selected = 2;
			}

			xy(10, 6 + (selected * 2));
			cout << "> " << List[selected];
			xy(10, 6 + (previous * 2));
			cout << "" << List[previous] << "  ";
			xy(0, 0);
			wait(100);
		};
		if (GetKeyState(VK_RETURN) & 0x8000) {
			switch (selected) {
			case 0:
				break;
			case 1:
				TextSpeedMenu();
				quit = true;
				break;
			case 2:
				wait(100);
				clear();
				Menu();
				quit = true;
				break;
			}
			xy(0, 0);
			wait(100);
		}
	}
}

void Menu() {
	split("Menu", '-', 3, 1);
	string List[3] = { "Start", "Settings", "Exit the game" };
	PrintList(10, 6, 2, 3, List);

	int selected = 0;
	int previous = 0;
	bool quit = false;

	xy(10, 6 + (selected * 2));
	cout << "> " << List[selected];
	xy(0, 0);
	while (!quit) {
		if (GetKeyState(VK_DOWN) & 0x8000) {
			previous = selected++;
			if (selected >= 3) {
				selected = 0;
			}

			xy(10, 6 + (selected * 2));
			cout << "> " << List[selected];
			xy(10, 6 + (previous * 2));
			cout << "" << List[previous] << "  ";
			xy(0, 0);
			wait(100);
		};
		if (GetKeyState(VK_UP) & 0x8000) {
			previous = selected--;
			if (selected <= -1) {
				selected = 2;
			}

			xy(10, 6 + (selected * 2));
			cout << "> " << List[selected];
			xy(10, 6 + (previous * 2));
			cout << "" << List[previous] << "  ";
			xy(0, 0);
			wait(100);
		};
		if (GetKeyState(VK_RETURN) & 0x8000) {
			switch (selected) {
			case 0:
				Game();
				quit = true;
				break;
			case 1:
				Settings();
				quit = true;
				break;
			case 2:
				clear();
				xy(55, 13);
				cout << "EXIT...";
				wait(1000);
				quit = true;
				clear();
				break;
			}
			xy(0, 0);
			wait(100);
		}
	}
}