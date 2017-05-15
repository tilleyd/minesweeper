#include "cell.h"

Cell::Cell()
	:Cell(NORMAL) {
}

Cell::Cell(int state)
	: _state(state)
	, _mined(false) {
}

int Cell::getState() const {
	return _state;
}

void Cell::setState(int state) {
	_state = state;
}

bool Cell::hasMine() const {
	return _mined;
}

void Cell::setMine(bool s) {
	_mined = s;
}
