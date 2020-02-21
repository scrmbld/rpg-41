#include "list.h"
#include "fighter.h"
#include "monsters.h"
using namespace std;

//getters
Fighter LL::get_fighter() {
	return f;
}
LL* LL::get_next() {
	return next;
}

//setters
void LL::update_health(int h) {
	f.change_health(h);
}
void LL::change_fighter(Fighter f) {
	this->f = f;
}
void LL::change_next(LL *next) {
	this-> next = next;
}

//constructors
LL::LL(Fighter f, LL* next) {
	this->f = f;
	this->next = next;

}
/*
LL(Goblin g, LL* next) {
	this->f = Fighter(g.get_name(), g.get_health(), g.get_attack(), g.get_defense(), g.get_speed);
	this->next = next;
}
LL(Dragon g, LL* next) {
	this->f = Fighter(g.get_name(), g.get_health(), g.get_attack(), g.get_defense(), g.get_speed);
	this->next = next;
}
LL(Warlock g, LL* next) {
	this->f = Fighter(g.get_name(), g.get_health(), g.get_attack(), g.get_defense(), g.get_speed);
	this->next = next;
}
LL(Sorceror g, LL* next) {
	this->f = Fighter(g.get_name(), g.get_health(), g.get_attack(), g.get_defense(), g.get_speed);
	this->next = next;
}
*/

//destructors
LL::~LL() {
	LL *pos = this->get_next();
	while (pos != nullptr) delete this;
}


//other functions
void insert(LL* tail, LL new_item) {
	LL* temp = new LL(new_item.get_fighter(), tail->get_next());
	tail->change_next(temp);
}
