#include "cell.h"
#include "field.h"

Field::Field()
	: Field(20, 20) {
}

Field::Field(int r, int c)
	: _r(r)
	, _c(c)
	, _mines(0) {
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

void Field::populate() {

}

void Field::reset() {
	for (int r = 0; r < _r; r++) {
		for (int c = 0; c < _c; c++) {
			_field[r][c].setState(NORMAL);
		}
	}
}
