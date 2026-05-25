#pragma once

#pragma once

#include <string>
using namespace std;
class Room
{
public:
	string building;
	string bldginitials;
	int roomnum;
	int SEATCOUNT;
	int availseats;


public:
	Room();
	Room(string b, string b2, int r, int s, int a);

};

Room::Room()
{
	building = "";
	bldginitials = "";
	roomnum = 0;
	SEATCOUNT = 0;
	availseats = 0;
}
Room::Room(string b, string b2, int r, int s, int a)
{
	building = b;
	bldginitials = b2;
	roomnum = r;
	SEATCOUNT = s;
	availseats = a;
}

