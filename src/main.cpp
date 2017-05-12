#include <ncurses.h>
#include <string>
using std::string;

#include "field.h"

int main() {
	// start up ncurses
	initscr();
	raw();
	noecho();
	keypad(stdscr, true);
	// populate the minefield
	Field field;
	field.populate();
	// end ncurses
	endwin();
}
