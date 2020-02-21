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



bool is_dead(CircSLelement<Fighter>* f) {
	if (f->getValue().get_health() <= 0) return true;
	return false;
}

//checks to see if the player has won the fight, breaks if there's no player in the list
bool win_con(CircSLelement<Fighter> *head) {
	CircSLelement<Fighter> *pos = head->getNext();
	while (pos->getLabel() != "Player") {
		if (!is_dead(pos)) return false;
		pos = pos->getNext();
	}
	//pos must be set to player to get here
	if (pos->getValue().get_health() <= 0) return false;//the player can't win if they're dead
	return true;
}

//returns true if the player is dead
bool lose_con (CircSLelement<Fighter> *head) {
	CircSLelement<Fighter> *pos = head;
	while (pos->getNext() != head) {
		if (pos->getLabel() == "Player" && is_dead(pos)) return true; 
		pos = pos->getNext();
	}

	return false;
}

bool combat_mode(Fighter &player) {
    Bridges *bridges = new Bridges(222, "scrmbld", 
			"347981115445");
	int lvl = player.get_level();
	
	//generate the encounter
	srand(time(0));
	int encounter_size = rand() % 5 + 1;
	CircSLelement<Fighter> *encounter = new CircSLelement<Fighter>(Fighter(lvl, "Goblin 0", rand() % 5 + 8, rand() % 3 + 1, (rand() % 7 + 3) * 0.1 , rand() % 3 + 10), "enemy");
	encounter->getVisualizer()->setColor("red");
	CircSLelement<Fighter> *temp = encounter;
	
	for (int i = 0; i < encounter_size; i++) {
		temp->setNext(new CircSLelement<Fighter>(Fighter(lvl, "Goblin " + to_string(i + 1), rand() % 5 + 8, rand() % 3 + 1, (rand() % 7 + 3) * 0.1 , 9 - i), "enemy"));
		temp->getVisualizer()->setColor("red");
		temp = temp->getNext();
	}
	temp->setNext(encounter);
	temp = encounter;

	CircSLelement<Fighter> *p = new CircSLelement<Fighter>(player, "Player");
	p->getVisualizer()->setColor("blue");
	//if the player is faster than all the enemies
	if (player.get_speed() >= encounter->getValue().get_speed()) {
		p->setNext(encounter);
		temp = encounter->getNext();
		//set temp to the last item in the list
		while (temp != encounter) {
			temp = temp->getNext();
		}
		temp->setNext(p);
		encounter = p;
	} else {
		//if the player is not faster than all the enemies
		while (temp) {
			if (player.get_speed() <= temp->getValue().get_speed() && player.get_speed() >= temp->getNext()->getValue().get_speed()) {
				p->setNext(temp->getNext());
				temp->setNext(p);
				break;
			}

			temp = temp->getNext();
			if (temp == encounter) break;
		}
	}
	bridges->setDataStructure(encounter);
	bridges->visualize();
	//run the encounter
	cout << endl;
    system("figlet -f smblock BATTLE  | lolcat"); //prints title to the screen
    cout << "(ง'̀-'́)ง" << endl;
	CircSLelement<Fighter> *pos = encounter;
	while (pos) {
		if (is_dead(pos)) {
			pos = pos->getNext();
			continue;
		}
		if (pos->getLabel() == "Player") {
			CircSLelement<Fighter> *tgt = pos->getNext();
			while (is_dead(tgt)) {
				tgt = tgt->getNext();
				if (tgt->getLabel() == "Player") break; //prevents infinite loops
			}
			int damage = pos->getValue().get_attack() / tgt->getValue().get_defense();
			tgt->getValue().change_health(tgt->getValue().get_health() - damage);
			cout << pos->getValue() << endl;
			cout << tgt->getValue() << endl;
		} else {
			int damage = pos->getValue().get_attack() / p->getValue().get_defense();
			p->getValue().change_health(p->getValue().get_health() - damage);
			cout << pos->getValue() << endl;
			cout << p->getValue() << endl;
		}
		if (win_con(p)) return true;
		else if (lose_con(p)) return false;
		pos = pos->getNext();
	}
	return true;
}

