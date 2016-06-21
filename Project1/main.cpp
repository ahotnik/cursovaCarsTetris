#define _CRT_SECURE_NO_WARNINGS
#include "player.h"
#include <conio.h>
#include <time.h> 
#include <windows.h>

static int a= 97;
static int d = 100;
static int space = 32;
static int symbol = 42;
static int block = (int)'+';
static int blockLenght = 4;
static int carWidth = 10;
static int carLenght = 8;
static int lines = 25;
static int colums = 25;

void saveResult(Player test){
	FILE* f;
	f = fopen("rate.dat", "a");
	fseek(f, 0, SEEK_END);
	fwrite(&test, sizeof(Player), 1, f);
	fclose(f);
}

void showResult(){
	FILE *f;
	f = fopen("rate.dat", "r");
	if (f == NULL){
		printf("no scores\n");
		return;
	}
	fseek(f, 0, SEEK_SET);
	while (true)
	{
		Player tmp;
		fread(&tmp, sizeof(Player), 1, f);
		if (feof(f))
		{
			break;
		}
		cout << tmp.name << "\t" << tmp.point << endl;
	}
	fclose(f);
}

void cursorVisible(bool flag){
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = flag;
	SetConsoleCursorInfo(handle, &structCursorInfo);
}

int mainMenu(){
	system("cls");
	int position = 1;
	bool choose = false;
	int size = 4;
	char ** menus = new char*[size];
	menus[0] = "New game";
	menus[1] = "Rate Table";
	menus[2] = "Clear rate";
	menus[3] = "Exit";
	while (true){
		system("cls");
		cout << "Menu:" << endl;

		for (int i = 0; i < size; i++)
		{
			if (i == position - 1)
			{
				cout << "* ";
			}
			else{
				cout << "  ";
			}
			cout << menus[i] << endl;
		}
		switch (_getch())
		{
		case 224:
			switch (_getch())
			{
			case 80:
				position < size ? position++ : position = 1;
				break;

			case 72:
				position > 1 ? position-- : position = size;
				break;
			}
			break;
		case 13:
			choose = true;
			break;
		}
		if (choose)
		{
			break;
		}
	}
	return position;
	system("cls");
}

void borderLines(int ** gameTable){

	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			gameTable[i][0] = '|';
			gameTable[i][18] = '|';
			gameTable[i][j] = ' ';
		}
	}
}

bool isLose(int ** gameTable, int y, int x){
	char obstacle = 219;
	if (gameTable[y - 2][x] == obstacle || gameTable[y - 2][x - 1] == obstacle || gameTable[y - 2][x + 1] == obstacle) {
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void showGame(int ** gameTable, int y, int x, Player & player){
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			cout << (char)gameTable[i][j];
			if (j >= 19) {
				cout << endl;
			}
		}
	}
	++player.point;
	cout << player.point << " ";
}

void carPosition(int ** gameTable, int & y, int & x){

	char obstacle = 219;
	if (GetAsyncKeyState(VK_LEFT)) {
		if (gameTable[y][x - 3] == obstacle) {
			//goto lost;
		}
		else if (gameTable[y][x - 3] != '|') {
			gameTable[y][x] = ' ';
			gameTable[y][x + 1] = ' ';
			gameTable[y][x - 1] = ' ';
			gameTable[y + 1][x - 1] = ' ';
			gameTable[y + 1][x + 1] = ' ';
			gameTable[y - 1][x - 1] = ' ';
			gameTable[y - 1][x + 1] = ' ';
			x -= 3;
			gameTable[y][x] = 'X';
			gameTable[y][x + 1] = '|';
			gameTable[y][x - 1] = '|';
			gameTable[y + 1][x - 1] = 'o';
			gameTable[y + 1][x + 1] = 'o';
			gameTable[y - 1][x - 1] = 'o';
			gameTable[y - 1][x + 1] = 'o';
		}
	}
	//moves the car to the right
	if (GetAsyncKeyState(VK_RIGHT)) {
		if (gameTable[y][x + 3] == obstacle) {
			//goto lost;
		}
		else if (gameTable[y][x + 3] != '|') {
			gameTable[y][x] = ' ';
			gameTable[y][x + 1] = ' ';
			gameTable[y][x - 1] = ' ';
			gameTable[y + 1][x - 1] = ' ';
			gameTable[y + 1][x + 1] = ' ';
			gameTable[y - 1][x - 1] = ' ';
			gameTable[y - 1][x + 1] = ' ';
			x += 3;
			gameTable[y][x] = 'X';
			gameTable[y][x + 1] = '|';
			gameTable[y][x - 1] = '|';
			gameTable[y + 1][x - 1] = 'o';
			gameTable[y + 1][x + 1] = 'o';
			gameTable[y - 1][x - 1] = 'o';
			gameTable[y - 1][x + 1] = 'o';
		}
	}
}

void showCar(int ** gameTable, int & y, int & x){
	char car = 'X';
	gameTable[y][x] = 'X';
	gameTable[y][x + 1] = '|';
	gameTable[y][x - 1] = '|';
	gameTable[y + 1][x - 1] = 'o';
	gameTable[y + 1][x + 1] = 'o';
	gameTable[y - 1][x - 1] = 'o';
	gameTable[y - 1][x + 1] = 'o';
}

void showBlock(int ** gameTable, int & a, int & b){
	char obstacle = 219;
	gameTable[a][b] = ' ';
	gameTable[a][b] = ' ';
	gameTable[a][b + 1] = ' ';
	gameTable[a][b - 1] = ' ';
	gameTable[a + 1][b - 1] = ' ';
	gameTable[a + 1][b + 1] = ' ';
	gameTable[a - 1][b - 1] = ' ';
	gameTable[a - 1][b + 1] = ' ';
	++a;
	gameTable[a][b] = obstacle;
	gameTable[a][b + 1] = obstacle;
	gameTable[a][b - 1] = obstacle;
	gameTable[a + 1][b - 1] = obstacle;
	gameTable[a + 1][b + 1] = obstacle;
	gameTable[a - 1][b - 1] = obstacle;
	gameTable[a - 1][b + 1] = obstacle;
	if (a > 20) {
		a = 1;
		b = rand() % 15 + 2;
	}
}

void Game(int ** gameTable, Player & player){
	srand(time(0));

	int y = 17, x = 9; //car position
	player.point = 0;
	int speed = 100; //determines the speed of the obstacles (and the car)
	int a = 1, b = rand() % 15 + 2; //the obstacles coordiantes
	while (true)
	{
		system("cls");

		//lines
		borderLines(gameTable);
		//endlines


		//showcar
		showCar(gameTable, y, x);
		showBlock(gameTable, a, b);
		carPosition(gameTable, y, x);
		
		showGame(gameTable, y, x, player);
		if (isLose(gameTable, y, x))
		{
			cout << "GAME OVER\n";
			saveResult(player);
			break;
		}

		if (player.point == 100 || player.point == 200 || player.point == 300 || player.point == 400) {
			speed -= 25;
		}
		Sleep(speed);

	}

}


int main(){

	srand(time(NULL));

	int ** gameTable = new int*[lines];

	for (size_t i = 0; i < lines; i++)
	{
		gameTable[i] = new int[colums];
	}

	Player newplayer;
	char name[10];

	cursorVisible(false);


	while (true)
	{
		switch (mainMenu()){
		case 1:
			system("cls");
			cout << "Enter name: ";
			cin >> name;
			newplayer.SetName(name);
			system("cls");
			Game(gameTable, newplayer);
			break;
		case 2:
			system("cls");
			showResult();
			system("pause");
			break;
		case 3:
			remove("rate.dat");
			break;
		case 4:
			return 0;
			break;
		}
	}
	return 0;
}