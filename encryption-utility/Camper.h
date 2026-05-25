#pragma once

#include <string>
using namespace std;

class Camper
{
public:
	string campusID;
	string fname;
	string lname;
	string	email;
	string phone;
	string	password;

public:
	Camper();
	Camper(string c, string f, string l, string e, string p, string p2);
};

Camper::Camper()
{
	campusID = "";
	fname = "";
	lname = "";
	email = "";
	phone = "";
	password = "";
}

Camper::Camper(string c, string f, string l, string e, string p, string p2)
{
	campusID = c;
	fname = f;
	lname = l;
	email = e;
	phone = p;
	password = p2;
}


