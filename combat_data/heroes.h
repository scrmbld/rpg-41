#pragma once
#include <iostream>
#include "fighter.h"
using namespace std;

//child classes
class Sorcerer : public Fighter {
    public:
        Sorcerer(int level);
};

class Warlock : public Fighter {
    public:
        Warlock(int level);
};       

