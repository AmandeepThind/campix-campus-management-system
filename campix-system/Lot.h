#pragma once

class Lot
{
public:
	char lotcode;
	int SPOTCOUNT;
	int availspots;
public:
	Lot();
	Lot(char l, int s, int a);

};

Lot::Lot()
{
	lotcode = 'x';
	SPOTCOUNT = 0;
	availspots = 0;
}

Lot::Lot(char l, int s, int a)
{
	lotcode = l;
	SPOTCOUNT = s;
	availspots = a;
}