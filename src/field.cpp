#include "cell.h"
#include <cmath>
#include <ctime>
#include <sstream>
#include <string>

#include "field.h"

Field::Field(int d)
	: Field(d, 20, 20) {
}

Field::Field(int d, int r, int c)
	: _r(r)
	, _c(c)
	, _populated(false)
	, _diff(d) {
	_field = new Cell*[_r];
	for (int i = 0; i < _r; i++) {
		_field[i] = new Cell[_c];
	}
}

Field::~Field() {
	for (int i = 0; i < _r; i++) {
		delete [] _field[i];
	}
	delete [] _field;
}

Cell* Field::operator[](int i) const {
	return _field[i];
}

void Field::populate(int r, int c) {
	srand(time(0));
	for (int i = 0; i < _r; i++) {
		for (int j = 0; j < _c; j++) {
			// random number in range 0-99
			int num = rand() % 100;
			if (num < _diff) {
				if (!(abs(i - r) <= 1 && abs(j - c) <= 1)) {
					_field[i][j].setMine(true);
				}
			}
		}
	}
	_populated = true;
}

bool Field::activate(int r, int c) {
	if (_field[r][c].hasMine()) {
		return true;
	} else {
		activate_r(r, c);
		return false;
	}
}

void Field::activate_r(int r, int c) {
	_field[r][c].setState(CHECKED);
	int val = getVal(r, c);
	if (val == 0) {
		int y[] = {0, -1, -1, -1, 0, 1, 1, 1};
		int x[] = {1, 1, 0, -1, -1, -1, 0, 1};
		// activate all neighbours
		for (int i = 0; i < 8; i++) {
			int row = r + y[i];
			int col = c + x[i];
			if ((row >= 0 && row < _r) && (col >= 0 && col < _c)) {
				if (_field[row][col].getState() == NORMAL) {
					activate_r(row, col);
				}
			}
		}
	}
}

void Field::reset() {
	for (int r = 0; r < _r; r++) {
		for (int c = 0; c < _c; c++) {
			_field[r][c].setState(NORMAL);
		}
	}
}

int Field::getRows() const {
	return _r;
}

int Field::getCols() const {
	return _c;
}

char Field::getChar(int r, int c, bool show) const {
	int state = _field[r][c].getState();
	int val = getVal(r, c);
	switch (state) {
		case NORMAL:
			if (show && _field[r][c].hasMine()) {
				return 'X';
			} else {
				return '+';
			}
			break;
		case CHECKED:
			if (val > 0) {
				return ('0' + val);
			} else {
				return ' ';
			}
			break;
		case FLAGGED:
			return '?';
			break;
		default:
			return ' ';
			break;
	}
}

bool Field::isPopulated() const {
	return _populated;
}

int Field::getRemaining() const {
	int count = 0;
	for (int r = 0; r < _r; r++) {
		for (int c = 0; c < _c; c++) {
			if (!_field[r][c].hasMine() && _field[r][c].getState() != CHECKED) {
				count++;
			}
		}
	}
	return count;
}

int Field::getVal(int r, int c) const {
	// find the number of neighbouring mines
	int y[] = {0, -1, -1, -1, 0, 1, 1, 1};
	int x[] = {1, 1, 0, -1, -1, -1, 0, 1};
	int val = 0;
	for (int i = 0; i < 8; i++) {
		int row = r + y[i];
		int col = c + x[i];
		if ((row >= 0 && row < _r) && (col >= 0 && col < _c)) {
			if (_field[row][col].hasMine()) {
				val++;
			}
		}
	}
	return val;
}
