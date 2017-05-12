/* CLASS: Cell
 * AUTHOR: Duncan Tilley
 * DESCR: Cell class represents a single cell in the minefield.
 */

#ifndef CELL_H
#define CELL_H

#define NORMAL 0
#define CHECKED 1
#define FLAGGED 2
#define MINED 3

class Cell {
	public:
		// creates a cell in the normal state
		Cell();
		// creates a cell with the given state
		Cell(int);
		// returns the current state
		int getState() const;
		// returns a character representing the current state
		char getChar() const;
		// sets the state
		void setState(int);
	private:
		int _state;
};

#endif

