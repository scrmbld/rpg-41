#include "map.h"
#include "player.h"
#include <unistd.h>
#include <CircSLelement.h>

const unsigned int TIMEOUT = 10; //Milliseconds to wait for a getch to finish
const int UP = 65; //Key code for up arrow
const int DOWN = 66;
const int LEFT = 68;
const int RIGHT = 67;
const int ENTER = 10;

bool is_stairs(char c) {
	if (c == '|' || c == '-' || c == '_') return true;
	return false;
}

//ask the user if they want to descend the stairs, entering a new map
bool descend(int &x, int &y, Map &map) {
	//make the text box
	int DIALOGUE_WIDTH = 30;
	int DIALOGUE_HEIGHT = 7;
	for (int i = 0; i < DIALOGUE_WIDTH; i++) {
		for (int j = 0; j < DIALOGUE_HEIGHT; j++) {\
			char c = ' ';
			if (j == 0 || j == DIALOGUE_HEIGHT -1 ) c = '=';
			else if (i == 0 || i == DIALOGUE_WIDTH - 1) c = '|';
			mvaddch(Map::DISPLAY / 2 - DIALOGUE_HEIGHT / 2 + j, Map::DISPLAY - DIALOGUE_WIDTH + 2  + i, c);
		}
	}
	//print the content
	mvprintw(Map::DISPLAY / 2 - DIALOGUE_HEIGHT / 2 + 1, Map::DISPLAY - DIALOGUE_WIDTH + 3, "Do you want to go deeper?");
	mvprintw(Map::DISPLAY / 2 - DIALOGUE_HEIGHT / 2 + 5, Map::DISPLAY - DIALOGUE_WIDTH + 5, "Yes");
	mvprintw(Map::DISPLAY / 2 - DIALOGUE_HEIGHT / 2 + 5, Map::DISPLAY - DIALOGUE_WIDTH + 25, "No");
	
	//take the user's input
	move(Map::DISPLAY / 2 - DIALOGUE_HEIGHT / 2 + 5, Map::DISPLAY - DIALOGUE_WIDTH + 24);
	bool menupos = false;
	while (true) {
		int ch = getch();
		if (ch == LEFT) {
			menupos = true;
			move(Map::DISPLAY / 2 - DIALOGUE_HEIGHT / 2 + 5, Map::DISPLAY - DIALOGUE_WIDTH + 4);
		}
		if (ch == RIGHT) {
			menupos = false;
			move(Map::DISPLAY / 2 - DIALOGUE_HEIGHT / 2 + 5, Map::DISPLAY - DIALOGUE_WIDTH + 24);
		}
		if (ch == ENTER) break;
	}

	return menupos;
}

void pause(Map &map) {
	//make the text box
	int DIALOGUE_WIDTH = 25;
	int DIALOGUE_HEIGHT = 17;
	for (int i = 0; i < DIALOGUE_WIDTH; i++) {
		for (int j = 0; j < DIALOGUE_HEIGHT; j++) {\
			char c = ' ';
			if (j == 0 || j == DIALOGUE_HEIGHT -1 ) c = '=';
			else if (i == 0 || i == DIALOGUE_WIDTH - 1) c = '|';
			mvaddch(Map::DISPLAY / 2 - DIALOGUE_HEIGHT / 2 + j, Map::DISPLAY - DIALOGUE_WIDTH + 2  + i, c);
		}
	}
	//print the content
	mvprintw(Map::DISPLAY / 2 - DIALOGUE_HEIGHT / 2 + 1, Map::DISPLAY - DIALOGUE_WIDTH + 3, "Pause");
	mvprintw(Map::DISPLAY / 2 - DIALOGUE_HEIGHT / 2 + 2, Map::DISPLAY - DIALOGUE_WIDTH + 5, "Continue");
	mvprintw(Map::DISPLAY / 2 - DIALOGUE_HEIGHT / 2 + 4, Map::DISPLAY - DIALOGUE_WIDTH + 5, "Save");
	mvprintw(Map::DISPLAY / 2 - DIALOGUE_HEIGHT / 2 + 6, Map::DISPLAY - DIALOGUE_WIDTH + 5, "Quit");
	
	//take the user's input
	move(Map::DISPLAY / 2 - DIALOGUE_HEIGHT / 2 + 5, Map::DISPLAY - DIALOGUE_WIDTH + 24);
	bool menupos = 0;
	while (true) {
		int ch = getch();
		if (ch == UP && menupos > 0;) {
			menupos -= 1;
		}
		if (ch == DOWN && menupos < 3) {
			menupos += 1;
		}
		if (ch == ENTER) break;
		
		move(Map::DISPLAY / 2 - DIALOGUE_HEIGHT / 2 + menupos * 2 + 2, Map::DISPLAY - DIALOGUE_WIDTH + 4);
	}

	if (menupos == 0) return;
	else if (menupos == 1) map.save_map();
	else if (menupos == 2) {
		clear();
		endwin(); 
		system("clear");
		exit(0);
	}
	
}

void turn_on_ncurses() {
	initscr();//Start curses mode
	start_color(); //Enable Colors if possible
	init_pair(1,COLOR_WHITE,COLOR_BLACK); //Set up some color pairs
	init_pair(2,COLOR_CYAN,COLOR_BLACK);
	init_pair(3,COLOR_GREEN,COLOR_BLACK);
	init_pair(4,COLOR_YELLOW,COLOR_BLACK);
	init_pair(5,COLOR_RED,COLOR_BLACK);
	init_pair(6,COLOR_MAGENTA,COLOR_BLACK);
	clear();
	noecho();
	cbreak();
	timeout(TIMEOUT); //Set a max delay for key entry
}

//places the player when a new floor starts, makes sure to not spawn them in a wall
void start_pos(int &x, int &y, const Map &map) {
	x = Map::WIDTH / 2;
	y = Map::HEIGHT / 2;
	for (int i = Map::HEIGHT / 2; i < Map::HEIGHT; i++) {
		if (map.spot_data(x, i) == Map::OPEN) {
			y = i;
			break;
		}
	}
	
}

//If it doesn't compile after adding #include "combat_data.h" or whatever this is why
bool combat() {
	return true;
}

int main() {
	turn_on_ncurses();
	Map map;
	map.load_map();
	//determine starting location
	int x, y;
	start_pos(x, y, map);
	
	while (true) {
		int ch = getch(); // Wait for user input, with TIMEOUT delay
		if (ch == 'q' || ch == 'Q') {
			pause(map);
		}
		else if (ch == RIGHT && map.spot_data(x + 1, y) != Map::WALL) {
			x++;
			if (y >= Map::HEIGHT) y = Map::HEIGHT - 1; //Clamp value
		}
		else if (ch == LEFT && map.spot_data(x - 1, y) != Map::WALL) {
			x--;
			if (y < 0) y = 0;
		}
		else if (ch == UP && map.spot_data(x, y - 1) != Map::WALL) {
			y--;
			if (x < 0) x = 0;
		}
		else if (ch == DOWN && map.spot_data(x, y + 1) != Map::WALL) {
			y++;
			if (x >= Map::WIDTH) x = Map::WIDTH - 1; //Clamp value
		}
		else if (ch == ERR) { //No keystroke
			; //Do nothing
		}
		clear();
		map.draw(x,y);
		mvprintw(Map::DISPLAY + 1, Map::DISPLAY + 1,"X: %i Y: %i\n",x,y);
		refresh();
		if (is_stairs(map.spot_data(x, y))) {
			if (descend(x, y, map)) {
				map.init_map();
				start_pos(x, y, map);
			} else {
				x -= 1;
				y -= 3;
			}
		}

		if (map.spot_data(x, y) == Map::MONSTER) {
			if (combat()) map.set_spot(x, y, '.');
			else break;
		}
		usleep(5000);
	}
	clear();
	endwin(); // End curses mode
	system("clear");
	map.save_map();
}
