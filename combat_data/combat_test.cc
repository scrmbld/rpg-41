//FOR TESTING PURPOSES, DELETE LATER
#include "fighter.h"
#include "monsters.h"
#include "list.h"
#include <CircSLelement.h>
#include <Bridges.h>
#include <iostream>
#include <cmath>
using namespace std;
using namespace bridges;

//die function
void die(string s = "INVALID INPUT!") {
    cout << s << endl;
    exit(1);
}

//helper function for linked list
CircSLelement<Fighter> *insertFront(
			CircSLelement<Fighter> *tailElement,
			CircSLelement<Fighter> *newElement);



// If you monster kills you
void lose() {
	system("figlet GAME");
	system("figlet OVER");
	exit(0);
}

bool is_dead(CircSLelement<Fighter>* f) {
	if (f->getValue().get_health() <= 0) return true;
	return false;
}

//checks to see if the player has won the fight, breaks if there's no player in the list
bool win_con(CircSLelement<Fighter> *head) {
	CircSLelement<Fighter> *pos = head;
	while (pos->getLabel() != "Player") {
		if (!is_dead(pos)) return false;
		pos = pos->getNext();
	}
	//pos must be set to player to get here
	if (pos->getValue().get_health() == 0) return false;//the player can't win if they're dead
	return true;
}

//returns true if the player is dead
bool lose_con (CircSLelement<Fighter> *head) {
	CircSLelement<Fighter> *pos = head;
	while (pos->getNext() != head) {
		if (pos->getLabel() == "Player" && is_dead(pos)) return true; 
	}

	return false;
}

bool combat_mode() {
    cout << endl;
    system("figlet -f smblock BATTLE  | lolcat"); //prints title to the screen
    cout << "(ง'̀-'́)ง" << endl;
	//generate the encounter
	srand(time(0));
	int encounter_size = rand() % 5 + 1;
	CircSLelement<Fighter> *encounter = new CircSLelement<Fighter>(CircSLelement<Fighter>(Fighter("The Wizard", 15, 2, 0.5, 1), "Player"));
	CircSLelement<Fighter> *temp = encounter;
	for (int i = 0; i < encounter_size; i++) {
		temp->setNext(new CircSLelement<Fighter>(Fighter("Goblin " + to_string(i), 0, 1, 0.3, 4), "enemy"));
		temp = temp->getNext();
	}
	temp->setNext(encounter);

/*
	temp = encounter;
	while (true) {
		cout << "\n ✳ " << temp->getValue() << " goes first.\n";
		temp = temp->getNext();
	}
*/	
	//run the encounter
	CircSLelement<Fighter> *pos = encounter;
	cout << encounter_size << endl;
	while (pos){	
		if (is_dead(pos)) {
			pos = pos->getNext();
			continue;	
		}
		if (pos->getLabel() == "Player") {
			int damage = pos->getValue().get_attack() / pos->getNext()->getValue().get_defense();
			pos->getNext()->getValue().change_health(pos->getNext()->getValue().get_health() - damage);
		} else {
			int damage = pos->getValue().get_attack() / encounter->getValue().get_defense();
			encounter->getValue().change_health(encounter->getValue().get_health() - damage);
		}
		cout << pos->getValue() << endl;
		cout << pos->getNext()->getValue() << endl;
		if (win_con(encounter)) return true;
		else if (lose_con(encounter)) return false;
		pos = pos->getNext();
	}
	return true;
}


int main() {
	
	//MONSTERS
	int choice;
	cout << "Fight Mode? 1.) Yes 2.)  No " << endl;
	cin >> choice;
	if (!cin || choice < 0) die();
	if (choice == 1) {
		if (combat_mode()) cout << "VICTORY!!\n";
		else cout  << "Deafeat...\n";
	}


}
