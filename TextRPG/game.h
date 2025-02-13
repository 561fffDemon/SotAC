#pragma once

#include "engine.h"
#include "classes.h"

#include <iostream>
#include <windows.h>
#include <sstream>
#include <thread>

void Settings();
void Menu();


// Functions for Visual/Gameplay
int delay = 25;

void TextAnim_WRITE(string text, int ms) {
	for (int i = 0; i < text.size(); i++) {
		cout << text[i];
		if (text[i] == '.')
			wait(ms + (int)(ms * 0.8));
		else if (text[i] == ',')
			wait(ms + (int)(ms * 0.7));
		wait(ms);
	}
}

void TextAnim_xy(string text, int ms,int x,int y) {
	xy(x, y);
	TextAnim_WRITE(text,ms);
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
	if (Title != "")
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

void Fight() {
	clear();
	Entity player{100.0, 90.0, 25.0, 50.0, "Аранар"};
	Entity shadow{ 1000.0, 1000.0, 5.0, 0.0, "Тень" };

	string List[2] = { "Ударить", "Уйти с позором (Проигрыш)" };

	bool quitT = false;
	int selected = 0;
	int previous = 0;

	PrintList(10, 8, 2, 2, List);

	xy(10, 8 + (selected * 2));
	cout << "> " << List[selected];
	xy(0, 0);

	split("Тень", '-',5,1);
	xy(0, 0);
	split(player.GetNAME(), '-', 22, 2);
	xy(5, 24);
	cout << "HP: " << player.GetHP() << "/" << player.GetMaxHP() << " ";
	xy(5, 25);
	cout << "Defence: " << player.GetDEF() << "%" << " ";

	xy(93, 1);
	cout << "HP Тени: " << shadow.GetHP() << "/" << shadow.GetMaxHP() << " ";
	xy(93, 2);
	cout << "Defence Тени: " << shadow.GetDEF() << "%" << " ";

	xy(0, 0);
	while (!quitT) {
		if (GetKeyState(VK_UP) & 0x8000) {
			previous = selected--;
			if (selected < 0)
				selected = 1;


			xy(10, 8 + (selected * 2));
			cout << "> " << List[selected];
			xy(10, 8 + (previous * 2));
			cout << "" << List[previous] << "  ";
			xy(0, 0);
			wait(100);
		};
		if (GetKeyState(VK_DOWN) & 0x8000) {
			previous = selected++;
			if (selected > 1)
				selected = 0;


			xy(10, 8 + (selected * 2));
			cout << "> " << List[selected];
			xy(10, 8 + (previous * 2));
			cout << "" << List[previous] << "  ";
			xy(0, 0);
			wait(100);
		};
		if (GetKeyState(VK_RETURN) & 0x8000) {
			wait(100);
			switch (selected) {
			case 0:
				shadow.TakeDMG_HP(player.GetDMG());
				
				cout << "Вы ударили Тень на " << player.GetDMG() << " урона\nЗдоровье врага: " << shadow.GetHP() << "/" << shadow.GetMaxHP() << " +(" << shadow.GetDEF() << "%)";
				wait(500);
				xy(0,0);
				for (int i = 0; i < 30; i++) {
					cout << " ";
				}
				cout << "\n";
				for (int i = 0; i < 30; i++) {
					cout << " ";
				}
				xy(93, 1);
				cout << "HP Тени: " << shadow.GetHP() << "/" << shadow.GetMaxHP() << " ";
				xy(93, 2);
				cout << "Defence Тени: " << shadow.GetDEF() << "%" << " ";
				xy(0, 0);

				break;
			case 1:
				quitT = true;
				break;
			}
		}
	}
}


void Game() {
	clear();
	split("History", '-', 3, 1);
	xy(0, 0);
	
// Тень, некогда могущественное зло, была запечатана древними магами и отважными воинами.Со временем печати ослабли, и Тень стала жаждать свободы.Её последователи, призраки и нежить, рыскали по земле, сея хаос и разрушение.
	TextAnim_xy("В королевстве Эберон царил Золотой век, ознаменованный небывалым миром и процветанием.", delay, 5, 5);
	TextAnim_xy("Однако за этим фасадом благополучия таилась древняя угроза, давно забытая и похороненная в летописях истории.", delay, 5, 6);

	Fight();
}



void TextSpeedMenu() {
	clear();
	split("Playback speed (delay)", '-', 3, 1);
	xy(0, 0);

	string List[20] =
	{
	"*-------------------", "**------------------", "***-----------------", "****----------------",
	"*****---------------", "******--------------", "*******-------------", "********------------",
	"*********-----------", "**********----------", "***********---------", "************--------",
	"*************-------", "**************------", "***************-----", "****************----",
	"*****************---", "******************--", "*******************-", "********************"
	};

	int selected = delay / 25 - 1;
	bool quit = false;
	xy(10, 6);
	cout << List[selected] << "    " << delay << " мс.";
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
			cout << List[selected] << "    " << delay << " мс. ";
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
			cout << List[selected] << "    " << delay << " мс. ";
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
				clear();
				split("Menu", '-', 3, 1);

				PrintList(10, 6, 2, 3, List);
				xy(10, 6 + (selected * 2));
				cout << "> " << List[selected];
				xy(0, 0);
				break;
			case 1:
				Settings();
				clear();
				split("Menu", '-', 3, 1);

				PrintList(10, 6, 2, 3, List);
				xy(10, 6 + (selected * 2));
				cout << "> " << List[selected];
				xy(0, 0);
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