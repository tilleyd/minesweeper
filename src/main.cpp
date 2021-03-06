#include <ncurses.h>
#include <string>
using std::string;

#include "field.h"

#define WHITE 1
#define RED 2
#define YELLOW 3
#define GREEN 4
#define BLUE 5
#define RED_INVERSE 6

// draw the field at the given y and x
void drawField(Field* field, int y, int x, bool show) {
	for (int r = 0; r < field->getRows(); r++) {
		move(y + r, x);
		for (int c = 0; c < field->getCols(); c++) {
			char cur = field->getChar(r, c, show);
			int color = 0;
			// determine the color
			if (cur == MINE_CHAR) {
				color = RED_INVERSE;
			} else if (cur == FLAG_CHAR) {
				color = BLUE;
			} else if (cur >= '0' && cur <= '9') {
				if (cur >= '3') {
					color = RED;
				} else if (cur >= '2') {
					color = YELLOW;
				} else {
					color = GREEN;
				}
			} else {
				color = WHITE;
			}
			attron(COLOR_PAIR(color));
			addch(cur);
			attroff(COLOR_PAIR(color));
			addch(' ');
		}
	}
}

// activate the cell and return true if the game is over
bool activate(Field* field, int y, int x) {
	if (!field->isPopulated()) {
		field->populate(y, x);
	}
	int state = (*field)[y][x].getState();
	if (state == FLAGGED || state == CHECKED) {
		return false;
	} else {
		return field->activate(y, x);
	}
}

// set or remove a flag from a cell
void flag(Field* field, int y, int x) {
	if (field->isPopulated()) {
		int state = (*field)[y][x].getState();
		if (state == NORMAL) {
			(*field)[y][x].setState(FLAGGED);
		} else if (state == FLAGGED) {
			(*field)[y][x].setState(NORMAL);
		}
	}
}

int main() {
	// start up ncurses
	initscr();
	raw();
	noecho();
	keypad(stdscr, true);
	// initialize some colors
	start_color();
	init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
	init_pair(RED, COLOR_RED, COLOR_BLACK);
	init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(RED_INVERSE, COLOR_BLACK, COLOR_RED);
	// TODO receive the field size and difficulty
	int frows = 0, fcols = 0;
	int currow = 0, curcol = 0;
	// populate the minefield
	Field* field;
	if (frows == 0 || fcols == 0) {
		field = new Field(EASY);
	} else {
		field = new Field(EASY, frows, fcols);
	}
	// determine the offsets for centering
	int yoff, xoff;
	getmaxyx(stdscr, yoff, xoff);
	yoff = (yoff - field->getRows()) / 2;
	xoff = (xoff - (field->getCols() * 2)) / 2;

	bool running = true;
	bool won = false;
	while (running) {
		drawField(field, yoff, xoff, false);
		move(yoff + currow, xoff + (curcol * 2));
		char in = getch();
		switch (in) {
			case 'q':
				running = false;
				break;
			// movement
			case 'l':
				if (curcol < field->getCols() - 1) {
					curcol++;
				}
				break;
			case 'h':
				if (curcol > 0) {
					curcol--;
				}
				break;
			case 'j':
				if (currow < field->getRows() - 1) {
					currow++;
				}
				break;
			case 'k':
				if (currow > 0) {
					currow--;
				}
				break;
			// actions
			case ' ':
				if (activate(field, currow, curcol)) {
					running = false;
				}
				break;
			case 'f':
				flag(field, currow, curcol);
				break;
		}
		// check for a win
		if (field->getRemaining() == 0) {
			running = false;
			won = true;
		}
	}
	string msg = "Game over";
	if (won) {
		msg += ", you won!";
	}
	drawField(field, yoff, xoff, true);
	mvprintw(yoff - 1, xoff, msg.c_str());
	getch();
	// end ncurses
	delete field;
	endwin();
}
