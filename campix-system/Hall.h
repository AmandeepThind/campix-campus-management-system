#pragma once
#include "Room.h"

class StudyHall : public Room {
public:
	//all the other variables are inherited from the Room (parent) class
	string halltype;//added to distinguish study halls

public:
	StudyHall();
	StudyHall(string b, string b2, int r, int s, int a);

};

StudyHall::StudyHall()
{
	halltype = "";
}
StudyHall::StudyHall(string b,string b2, int r, int s, int a)
{
	//pass the variables to the parent constructor
	Room(b, b2, r, s, a);
	halltype = "Science"; //default to Science, but can change type in data file.
}
