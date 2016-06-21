#include "player.h"
using namespace std;

void Player::SetName(char * name){
	this->name = name;
}

void Player::ShowPoints(){
	cout << point << endl;
}
void Player::SetPoints(int point){
	this->point = point;
}