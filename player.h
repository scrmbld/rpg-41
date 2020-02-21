#pragma once
#include "combat_data/fighter.h"
#include <unistd.h>
using namespace std;

class Hero : public Fighter {
	protected:
		int money;
		int exp;
		int level;
		int base_hp = 10;
		int base_attack = 5;
		float base_defense = 1.0;
		int base_speed = 10;
	public:
		Hero() : Fighter(1, "PLAYER", 10, 5, 1.0, 10) {}
		Hero(string name) : Fighter(1, name, 10, 5, 1.0, 10) {
			//base stats
			this->base_hp = base_hp;
			this->base_attack = base_attack;
			this->base_defense = base_defense;
			this->base_speed = base_speed;
			//level & experience
			this->lvl = 1;
			this->exp = 0;
		}
		Hero(int lvl) : Fighter(lvl, name, 10, 5, 1.0, 10) {}
		Hero(int lvl, string player_name, int base_hp, int base_attack, float base_defense, int base_speed) : Fighter(lvl, player_name, base_hp, base_attack, base_defense, base_speed) {
			//base stats
			this->base_hp = base_hp;
			this->base_attack = base_attack;
			this->base_defense = base_defense;
			this->base_speed = base_speed;
			//level & experience
			this->lvl = lvl;
			this->exp = 16 * pow(2, lvl);
		}
		Hero(int lvl, int exp, string player_name, int base_hp, int base_attack, float base_defense, int base_speed, int money) : Fighter(lvl, player_name, base_hp, base_attack, base_defense, base_speed) {
			//base stats
			this->base_hp = base_hp;
			this->base_attack = base_attack;
			this->base_defense = base_defense;
			this->base_speed = base_speed;
			//level & experience
			this->lvl = lvl;
			this->exp = exp;
			this->money = money;
		}
		
		//getters (base stats)
		int get_base_hp() { return base_hp; }
		int get_base_attack() { return base_attack; }
		float get_base_defense() { return base_defense; }
		int get_base_speed() { return base_speed; }
		//other getters
		int get_exp() { return exp; }
		int get_lvl() { return lvl; }
		int get_money() { return money; }
		
		//increments base hp
		void base_hp_inc() { this->base_hp++; }
		//increments base attack
		void base_attack_inc() { this->base_attack++; }
		//increases base defense by 10%
		void base_def_inc() { this->base_defense += this->base_defense / 10.0; }
		//increments base speed
		void base_speed_inc() { this->base_hp = base_hp; }

		//gives the player exp
		void give_exp(int exp) {
			this->exp += exp;
			if (exp > 16 * pow(2, lvl)) {
				level++;
			}
		}
		//update the player's money
		void change_money(int x) { this->money = x; }
};
