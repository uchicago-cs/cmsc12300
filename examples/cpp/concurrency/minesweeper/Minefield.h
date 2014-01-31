/*
 * Minefield.h
 *
 *  Created on: May 3, 2013
 *      Author: borja
 */

#ifndef MINEFIELD_H_
#define MINEFIELD_H_

#include<iostream>

class Minefield;

enum StrategyType { ADD_AROUND_MINES, COUNT_MINES_AROUND_EMPTIES };

enum EntryType { EMPTY, MINE };

class MinefieldEntry {
	int adjacentMines;
	EntryType type;

public:
	MinefieldEntry(EntryType t = EMPTY);

	EntryType getType();
	int getAdjacentMines();

	string toString();

	int operator++();
	int operator++(int);

	friend std::ostream& operator<<(std::ostream &os, const Minefield &mf);
	friend std::istream& operator>>(std::istream &is, Minefield &mf);

	friend class Minefield;
};

class Minefield {
	int rows, cols;
	MinefieldEntry *field;

public:
	Minefield();
	Minefield(int rows, int cols);
	Minefield(int rows, int cols, float pmine, int seed);
	Minefield(const Minefield &mf);
	~Minefield();

	int getNumRows();
	int getNumCols();

	void solve(int radius = 1, StrategyType strategy = ADD_AROUND_MINES);
	void solve_range(int x_min, int x_max, int y_min, int y_max, int radius = 1, StrategyType strategy = ADD_AROUND_MINES);
	void reset();

	MinefieldEntry getEntry(int row, int col);

	friend std::ostream& operator<<(std::ostream &os, const Minefield &mf);
	friend std::istream& operator>>(std::istream &is, Minefield &mf);

private:
	inline int i(int x, int y) { return x*cols + y; }

	void processEntry(int x, int y, StrategyType strategy, int radius=1);
};

#endif /* MINEFIELD_H_ */
