/* CLASS: Field
 * AUTHOR: Duncan Tilley
 * DESCR: Field class contains an array of cells.
 */

#ifndef FIELD_H
#define FIELD_H

#include "cell.h"

class Field {
	public:
		// creates a field of size 20x20
		Field();
		// creates a field of size NxM
		Field(int, int);
		// clears memory used by the mines and cells
		~Field();
		// returns the given row of cells
		Cell* operator[](int) const;
		// populate the mines
		void populate();
		// reset all cells to normal state
		void reset();
	private:
		int _r, _c;
		Cell** _field;
		int** _mines;
};

#endif

