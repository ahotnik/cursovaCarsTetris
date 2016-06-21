#include <iostream>

using namespace std;


#include <iostream>

struct Player
{
	char * name=new char[10];
	int point = 0;
	int speed;
	void SetName(char * name);
	void ShowPoints();
	void SetPoints(int point);
};