/*
 * Minefield.cpp
 *
 *  Created on: May 3, 2013
 *      Author: borja
 */

#include<algorithm>
using namespace std;

#include "Minefield.h"

MinefieldEntry::MinefieldEntry(EntryType t)
{
	this->type = t;
	this->adjacentMines = 0;
}

void MinefieldEntry::setType(EntryType t)
{
	this->type = t;
}

EntryType MinefieldEntry::getType()
{
	return this->type;
}

int MinefieldEntry::operator++()
{
	return adjacentMines++;
}

int MinefieldEntry::operator++(int a)
{
	return ++adjacentMines;
}


Minefield::Minefield(): rows(0), cols(0), field(NULL)
{
	// TODO Auto-generated constructor stub

}

Minefield::Minefield(int rows, int cols): rows(rows), cols(cols)
{
	this->field = new MinefieldEntry[rows*cols];
}

Minefield::Minefield(const Minefield &mf)
{
	this->rows = mf.rows;
	this->cols = mf.cols;
	this->field = new MinefieldEntry[rows*cols];
	copy(&mf.field[0], &mf.field[rows*cols], &this->field[0]);
}


Minefield::~Minefield()
{
	delete[] field;
}

void Minefield::solve_range(int x_min, int x_max, int y_min, int y_max)
{
	for (int x=x_min; x < x_max; x++)
		for (int y=y_min; y < y_max; y++)
			if (field[i(x,y)].getType() == MINE)
				processMine(x,y);
}

void Minefield::solve()
{
	solve_range(0, rows, 0, cols);
}


std::ostream& operator<<(std::ostream &os, const Minefield &mf)
{
	for (int x=0; x < mf.rows; x++)
	{
		for (int y=0; y < mf.cols; y++)
		{
			MinefieldEntry &entry = mf.field[x*mf.cols + y];
			switch(entry.type)
			{
			case MINE:
				os << "X";
				break;
			case EMPTY:
				os << entry.adjacentMines;
				break;
			}
			os << " ";
		}
		os << endl;
	}

	return os;
}

std::istream& operator>>(std::istream &is, Minefield &mf)
{
	is >> mf.rows;
	is >> mf.cols;

	if (mf.rows == 0 && mf.cols == 0)
	{
		is.setstate(ios::eofbit);
		return is;
	}

	delete[] mf.field;

	mf.field = new MinefieldEntry[mf.rows * mf.cols];

	for(int i=0; i < mf.rows*mf.cols; i++)
	{
		int x;
		is >> x;
		mf.field[i].setType(x?MINE:EMPTY);
	}

	return is;
}

void Minefield::processMine(int x, int y, int radius)
{
	radius = 10;
	for(int x2=x-radius; x2<=x+radius; x2++)
		if(x2 >= 0 && x2 < rows)
			for(int y2=y-radius; y2<=y+radius; y2++)
				if(y2 >= 0 && y2 < cols && !(x2==x && y2==y))
					field[i(x2,y2)]++;
}

