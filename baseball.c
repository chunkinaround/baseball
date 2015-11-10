#include <ncurses.h>

// Maybe use halfdelay to simulate pitches?

char* field_path = "field.map";

/* forward declarations */
int initmap(const char *map_path);
void initplayers();
void pitch();

typedef struct {
	int curr_x;
	int curr_y;
	char position;
	char bgChar;
} Player;

Player batter;
Player pitcher;
Player catcher;
Player first;
Player second;
Player third;
Player shortStop;
Player left;
Player center;
Player right;

int main() {
	char ch;

	initscr();
	keypad(stdscr, TRUE);				//Enable funtion keys and keypad
	noecho();					//Don't echo input
	printw("Play ball!\n");
	refresh();
	getch();
	
	clear();
	refresh();

	if (initmap(field_path) < 0) {
		printw("Failed to read map file, exiting");
		refresh();
		getch();
		endwin();
		return 0;
	}

	initplayers();

	getch();
	while (ch != 'q') {
		ch = getch();
		if (ch == '\n')
			pitch();
	}
	endwin();

	return 0;
}

void pitch() {
	int x = 118;
	int y = 40;
	int hit = 0;
	char prevChar = ' ';
	char ch;
	
	timeout(30);

	while (y < 54) {
		ch = getch();
		if ((ch == 'b') && (y == 53))
			hit = 1;
		mvaddch(y,x, prevChar);
		prevChar = mvinch(y,x);
		if (hit > 0)
			y--;
		else
			y++;
		mvaddch(y, x, '*');
	}
}

int initmap(const char *map_path) {
	FILE *mapFile;
	int y = 0;
	char linePtr[238];

	mapFile = fopen(map_path, "r");

	if (mapFile == NULL){
		printw("file open failed");
		refresh();
		getch();
		return -1;
	}

	mapFile = fopen(field_path, "r");
	for (y=0;y<58;y++) {
		fread(linePtr, sizeof(char), 238, mapFile);
		printw(linePtr);
	}
	refresh();	

	return 0;
}

void initplayers() {
	pitcher.curr_x = 118;
	pitcher.curr_y = 41;
	pitcher.position = 'P';
	pitcher.bgChar = ' ';
	
	catcher.curr_x = 118;
	catcher.curr_y = 54;
	catcher.position = 'c';
	catcher.bgChar = ' ';

	batter.curr_x = 116;
	batter.curr_y = 53;
	batter.position = 'B';
	batter.bgChar = ' ';

	first.curr_x = 142;
	first.curr_y = 37;
	first.position = '1';
	first.bgChar = ' ';

	second.curr_x = 131;
	second.curr_y = 31;
	second.position = '2';
	second.bgChar = ' ';

	third.curr_x = 94;
	third.curr_y = 37;
	third.position = '3';
	third.bgChar = ' ';

	shortStop.curr_x = 105;
	shortStop.curr_y = 31;
	shortStop.position = 'S';
	shortStop.bgChar = ' ';

	left.curr_x = 75;
	left.curr_y = 18;
	left.position = 'L';
	left.bgChar = ' ';

	center.curr_x = 119;
	center.curr_y = 11;
	center.position = 'C';
	center.bgChar = ' ';

	right.curr_x = 161;
	right.curr_y = 18;
	right.position = 'R';
	right.bgChar = ' ';

	mvaddch(pitcher.curr_y, pitcher.curr_x, pitcher.position);
	mvaddch(catcher.curr_y, catcher.curr_x, catcher.position);
	mvaddch(batter.curr_y, batter.curr_x, batter.position);
	mvaddch(first.curr_y, first.curr_x, first.position);
	mvaddch(second.curr_y, second.curr_x, second.position);
	mvaddch(third.curr_y, third.curr_x, third.position);
	mvaddch(shortStop.curr_y, shortStop.curr_x, shortStop.position);
	mvaddch(left.curr_y, left.curr_x, left.position);
	mvaddch(center.curr_y, center.curr_x, center.position);
	mvaddch(right.curr_y, right.curr_x, right.position);
}
