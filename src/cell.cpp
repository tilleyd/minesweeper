#include "cell.h"

Cell::Cell()
	:Cell(NORMAL) {
}

Cell::Cell(int state)
	:_state(state) {
}

int Cell::getState() const {
	return _state;
}

char Cell::getChar() const {
	switch (_state) {
		case NORMAL:
			return 'O';
			break;
		case CHECKED:
			return ' ';
			break;
		case FLAGGED:
			return '?';
			break;
		case MINED:
			return 'X';
			break;
		default:
			return 'U';
			break;
	}
}

void Cell::setState(int state) {
	_state = state;
}

