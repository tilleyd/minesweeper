/* CLASS: Field
 * AUTHOR: Duncan Tilley
 * DESCR: Field class contains an array of cells.
 */

#ifndef FIELD_H
#define FIELD_H

#include "cell.h"
#include <string>

// percent of field that are mines
#define EASY 10
#define MEDIUM 20
#define HARD 30
#define IMPOSSIBLE 50

class Field {
	public:
		// creates a field of size 20x20 with difficulty
		Field(int);
		// creates a field of size NxM with difficulty
		Field(int, int, int);
		// clears memory used by the mines and cells
		~Field();
		// returns the given row of cells
		Cell* operator[](int) const;
		// populate the mines around an origin
		void populate(int ,int);
		// activate a cell, returning true if a mine is activated
		bool activate(int, int);
		// reset all cells to normal state
		void reset();
		// returns the number of rows
		int getRows() const;
		// returns the number of columns
		int getCols() const;
		// returns a char representation of a given cell, possibly showing mines
		char getChar(int, int, bool) const;
		// returns whether or not there are mines
		bool isPopulated() const;
	private:
		int getVal(int, int) const;
		void activate_r(int, int);
		int _r, _c;
		Cell** _field;
		bool _populated;
		int _diff;
};

#endif
