#pragma once
#include <iostream>
using namespace std;
class Fighter {
	protected:
		int lvl = 0;
		string name;
		int attack;
		float defense;
		int speed;
		int hp;
	public:
		Fighter();
		Fighter(int lvl, string name, int hp, int attack, float defense, int speed);
		//WARNING: unleveled Fighter constructor is deprecated
		Fighter(string name, int hp, int attack, float defense, int speed);
		//getters
		int get_level();
		string get_name();
		int get_health();
		int get_attack();
		float get_defense();
		int get_speed();
		//mutators
		void change_name(string);
		void change_health(int);
		void change_attack(int);
		void change_defense(float);
		void change_speed(int);

};

ostream& operator<<(ostream&, Fighter);

