//Allen, Walkup, Zamudio
//each floor has a staircase in one room

/*|__|
  |--|
*/
//go down the staircase to enter a new floor
//get through 5 floors to beat the game

#include "map.h"
#include "player.h"
#include "combat.h"
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

//Saves the player
void save_player(Hero &player, int &floor) {
		//Taken from stack verflow
		std::ofstream ofs;
		ofs.open("saved_player.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		
		ofstream outs("saved_player.txt");

		string s = to_string(player.get_lvl());
		outs << s << endl;

		s = to_string(player.get_exp());
		outs << s << endl;
		
		s = player.get_name();
		outs << s << endl;
		
		s = to_string(player.get_base_hp());
		outs << s << endl;

		s = to_string(player.get_base_attack());
		outs << s << endl;

		s = to_string(player.get_base_defense());
		outs << s << endl;
		
		s = to_string(player.get_base_speed());
		outs << s << endl;
		
		s = to_string(player.get_money());
		outs << s << endl;

		s = to_string(floor);
		outs << floor << endl;
		
		/*
		s = to_string(player.get_attack());
		outs << s << endl;
		
		s = to_string(player.get_defense());
		outs << s << endl;
		
		s = to_string(player.get_speed());
		outs << s << endl;
		
		s = to_string(player.get_health());
		outs << s << endl;
		*/
}

//Loading the player
void load_player(Hero &player, int &floor) {
	ifstream ins("saved_player.txt");
	vector<string> vec;
	//Iterates through every field saved in the saved_player.txt file. 
	for (int i = 0; i < 8; i++) {
		string s;
		getline(ins, s, '\n');
		vec.push_back(s);
	}
	player = Hero(stoi(vec.at(0)), stoi(vec.at(1)), vec.at(2), stoi(vec.at(3)), stoi(vec.at(4)), stof(vec.at(5)), stoi(vec.at(6)), stoi(vec.at(7)));
	string s;
	ins >> s;
	floor = stoi(s);
} 

void pause(Map &map, Hero &player, int &floor) {
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
	int menupos = 0;
	while (true) {
		int ch = getch();
		if (ch == UP && menupos > 0) {
			menupos -= 1;
		}
		if (ch == DOWN && menupos < 2) {
			menupos += 1;
		}
		if (ch == ENTER) break;
		
		move(Map::DISPLAY / 2 - DIALOGUE_HEIGHT / 2 + menupos * 2 + 2, Map::DISPLAY - DIALOGUE_WIDTH + 4);
	}

	if (menupos == 0) return;
	else if (menupos == 1) {
		map.save_map();
		save_player(player, floor);	
	}
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
	int level = 0;
	Hero player;
	Map map;
	cout << "github for this project:\n";
	cout << "https://github.com/scrmbld/rpg-41\n";
	cout << "https://github.com/MayZamudio/rpg-41\n";\
	cout << "https://github.com/walkupcraig75/rpg-41\n";
	//ask the user if they want a new game or to continue
	cout << "Do you want to continue(y/n)?\n";
	while (true) {
		string start_type;
		cin >> start_type;
		if (start_type == "y" || start_type == "Y") {
			map.load_map();
			load_player(player, level);
			break;
		} else if (start_type == "n" || start_type == "N") {
			cout << "What is the name of your intrepid explorer?\n";
			string player_name;
			cin >> player_name;
			player = Hero(player_name);
			break;
		}
	}
	

	turn_on_ncurses();
	//determine starting location
	int x, y;
	start_pos(x, y, map);
	
	while (true) {
		int ch = getch(); // Wait for user input, with TIMEOUT delay
		if (ch == 'q' || ch == 'Q') {
			pause(map, player, level);
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
		mvprintw(Map::DISPLAY + 2, Map::DISPLAY + 1,"$: %i",player.get_money());
		mvprintw(Map::DISPLAY + 3, Map::DISPLAY + 1,"floor: %i", level);
		refresh();
		if (is_stairs(map.spot_data(x, y))) {
			if (descend(x, y, map)) {
				level++;
				if (level == 5) {
					clear();
					endwin(); // End curses mode
					system("clear");
					cout << "win\n";
					exit(0);
				}
				map.init_map();
				start_pos(x, y, map);
			} else {
				x -= 1;
				y -= 3;
			}
		}

		if (map.spot_data(x, y) == Map::MONSTER) {
			string tresh;
			clear();
			endwin();
			system("clear");
			if (combat_mode(player)) {
				cout << "VICTORY!!\n";
				cout << "enter any key to continue\n";
				cin >> tresh;
				map.set_spot(x, y, '.');
			}
			else {
				cout << "Defeat...\n";
				cout << "enter any key to continue\n";
				cin >> tresh;
				break;
			}
			turn_on_ncurses();
		}

		if (map.spot_data(x, y) == Map::TREASURE) {
			player.change_money(player.get_money() + 100);
			map.set_spot(x, y, '.');
		}
		usleep(5000);
	}
	clear();
	endwin(); // End curses mode
	system("clear");
}
