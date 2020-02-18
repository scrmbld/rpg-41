//FOR TESTING PURPOSES, DELETE LATER
#include "fighter.h"
#include "monsters.h"
#include "heroes.h"
#include <iostream>
using namespace std;


void die(string s = "INVALID INPUT!") {
    cout << s << endl;
    exit(1);
}

// If you kill monster
void win() {
	system("figlet WINNER");
	exit(0);
}

// If you monster kills you
void lose() {
	system("figlet GAME");
	system("figlet OVER");
	exit(0);
}

void combat_mode() {
    cout << endl;
    system("figlet -f smblock BATTLE  | lolcat"); //prints title to the screen
    cout << "(ง'̀-'́)ง" << endl;
	Fighter f("Haigen - The Troll", 100, 10, 2, 1);
	Fighter d("The Wizard", 10, 2, 0.5, 1);
	Fighter *active = &f;
	Fighter *inactive = &d;
	
	cout << "\n ✳ " << active->get_name() << " goes first.\n";
	
	while (active->get_health() > 0){	
        cout << "\n (╯°□°)╯︵◓" << endl;
        cout << "\n " << active->get_name() << " is attacking " << inactive->get_name() << endl;
        int damage = 1;

		damage *= active->get_attack() / (inactive->get_defense());

        cout << "\n (。_°)☆ " << endl;
        cout << "\n " << inactive->get_name() << " takes damage of " << damage << " and the hp goes from " << inactive->get_health() << " to ";
        inactive->change_health(inactive->get_health() - damage);
        cout << inactive->get_health() << endl;
        if (active == &d) {
            active = &f;
            inactive = &d;
        } else {
            active = &d;
            inactive = &f;

        }
		
    cout << endl;
    cout << "✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶\n";
    system("figlet VICTORY!!!!! | lolcat");
    cout << "\n ";
    cout << " 🏆 " << inactive->get_name() << " has defeated " << active->get_name() << " !!!" << endl;
    cout << "\n   (∩ᄑ_ᄑ)⊃*･｡*･:≡( ε:) " << endl;
    cout << endl;
    cout << endl;
    cout << "✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶\n";
}
}



int main() {
	
	//MONSTERS
	cout << endl;
	cout << "THE MONSTERS" << endl;
	cout << endl;
	Fighter f("Haigen - The Troll", 100, 2, 0.5, 4);
	Dragon d(10, 2, 0.5, 1);
	Goblin g(30, 2, 0.5, 1);
	
	cout << f << endl;
	cout << d << endl;
	cout << g << endl;

	// HEROES
	cout << endl;
	cout << "THE HEROES" << endl;
	cout << endl;
	Warlock w(120, 2, 0.75, 3);
	Sorcerer s(130, 2 , 0.75, 2);
	Hero h("Alatar - The Wizard", 100, 2, 0.75, 4);

	cout << w << endl;
	cout << s << endl;
	cout << h << endl;

	int choice;
	cout << "Fight Mode? 1.) Yes 2.)  No " << endl;
	cin >> choice;
	if (!cin || choice < 0) die();
	if (choice == 1) {
		combat_mode();
	}


}
