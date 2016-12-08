#include <iostream>
#include<stdio.h>
#include"game.h"
#include<Windows.h>
void hideConsole(){
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);
}
int main(int argc, char *argv[]) {
	system("chcp 866");
	//hideConsole();
	Game(4);
	return 0;
}
