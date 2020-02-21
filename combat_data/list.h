#pragma once
#include "fighter.h"
#include "monsters.h"
using namespace std;

class LL{
	private:
		Fighter f;
		LL* next;
	public:
		//getters
		Fighter get_fighter();
		LL* get_next();
		//setters
		void update_health(int);
		void change_fighter(Fighter);
		void change_next(LL*);
		//constructors
		LL(Fighter, LL*);
		/*
		LL(Goblin, LL*);
		LL(Dragon, LL*);
		LL(Sorceror, LL*);
		LL(Warlock, LL*);
		*/
		//destructor
		~LL();
};

void insert(LL* tail, LL new_item);
