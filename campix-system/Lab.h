#pragma once

#include "Room.h"
#include <string>
using namespace std;
class Lab : public Room
{public:
	//all the other variables are inherited from the Room (parent) class
	int numcomps;

public:
	Lab();
	Lab(string b, string b2, int r, int s, int a);

};

Lab::Lab()
{
	numcomps = 0;
}
Lab::Lab(string b, string b2, int r, int s, int a)
{
	//pass the variables to the parent constructor
	Room(b, b2, r, s, a);
	numcomps = a;
}
