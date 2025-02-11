#pragma once
#include <iostream>
#include "engine.h"
#include <windows.h>
#include <sstream>
#include <thread>

// Functions for Visual/Gameplay

void TextAnim_WRITE(string text, int ms) {
	for (int i = 0; i < text.size(); i++) {
		cout << text[i];
		wait(ms);
	}
}

void split(string Title, char Fill, int StartY,int Mode) {
	COORD position = getSize();
	int w = (int)(position.X);
	int h = (int)(position.Y);

	xy(0, StartY);
	for (int i = 0; i < w; i++) {
		cout << Fill;
	}
	switch (Mode) {
	case 1:
		xy(( (int)(w/2) - (int)(Title.size() / 2) - 3), StartY - 1);
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

void Settings() {
	clear();
	split("Settings", '-', 3, 1);
	xy(0, 0);
	bool quit = false;

	while (!quit) {

	}
}

void Menu() {
	split("Menu", '-', 3, 1);
	string List[3] = {"Start", "Settings", "Exit the game"};
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
			if (selected == 3) {
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
				break;
			case 1:
				Settings();
				break;
			case 2:
				quit = true;
				break;
			}
			xy(0, 0);
			wait(100);
		}
	}
}