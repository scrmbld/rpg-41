#include "fighter.h"
#include <iostream>
using namespace std;

Fighter::Fighter(int lvl, string name, int hp, int attack, float defense, int speed) {
	this->lvl = lvl;
	this->name = name;
	this->hp = hp * (1 + 0.1 * lvl);
	this->attack = attack * (1 + 0.1 * lvl);
	this->defense = defense * (1 + 0.1 * lvl);
	this->speed = speed * (1 + 0.1 * lvl);
}

Fighter::Fighter(string name, int hp, int attack, float defense, int speed) {
	cerr << "WARNING: unleveled Fighter constructor is deprecated.\nUse Fighter(int level, string name, int hp, int attack, float defense, int speed) instead\n";
	this->name = name;
	this->hp = hp;
	this->attack = attack;
	this->defense = defense;
	this->speed = speed;
}

Fighter::Fighter() {
	this->name = "";
	this->hp = 0;
	this->attack = 0;
	this->defense = 0;
	this->speed = 0;
}

//getters
string Fighter::get_name() { return name; }
int Fighter::get_health() { return hp; }
int Fighter::get_attack() { return attack; }
float Fighter::get_defense() { return defense; }
int Fighter::get_speed() { return speed; }

//mutators
void Fighter::change_name(string s) {
	name = s;
}
void Fighter::change_health(int i) {
	hp = i;
}
void Fighter::change_attack(int i) {
	attack = i;
}
void Fighter::change_defense(float f) {
	defense = f;
}
void Fighter::change_speed(int i) {
	speed = i;
}

//operators
ostream& operator<<(ostream& outs, Fighter f) {
	outs << f.get_name() << endl;
	outs << "Health: " << f.get_health() << endl;
	outs << "Attack: " << f.get_attack() << endl;
	outs << "Defense: " << f.get_defense() << endl;
	outs << "Speed: " << f.get_speed() << endl;
	return outs;
} 

