#pragma once
#include "fighter.h"

class Dragon : public Fighter {
	    public:
			Dragon(int hp, int attack, float defense, int speed);
};


class Goblin : public Fighter {
	    public:
			Goblin(int hp, int attack, float defense, int speed);
};
