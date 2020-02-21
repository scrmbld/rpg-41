#pragma once
#include <vector>
#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <ncurses.h>
#include "load_rooms.h"
using namespace std; 

class Map {
	vector<vector<char>> view;//what actually gets put on the screen, pulls from rooms based off of layout
	vector<vector<vector<char>>> rooms;//stores what the rooms look like (each room is a 2d vector of chars)
	vector<vector<int>> layout;//stores which rooms are where
	//file names of all the rooms
	const vector<string> paths = {"room_01.txt", "room_02.txt", "room_03.txt"};
	string stairs = "stairs_room.txt"; //the room with the stairs
	default_random_engine gen;//setting up RNG
	public:
	static const char HERO     = 'H';
	static const char MONSTER  = 'M';
	static const char WALL     = '#';
	static const char WATER    = '~';
	static const char OPEN     = '.';
	static const char TREASURE = '$';
	static const char VOID = ' ';
	static const size_t DISPLAY = 30;//the size of the area that actually gets printed
	static const size_t LAYOUT_SIZE = 6;//the map is LAYOUT_SIZE rooms by LAYOUT_SIZE rooms
	static const size_t ROOM_WIDTH = 36;//the rooms are ROOM_WIDTH chars by ROOM_HEIGHT chars
	static const size_t ROOM_HEIGHT = 20;
	static const size_t WIDTH = 216; //the width of the area that can be printed
	static const size_t HEIGHT = 120;//the height of the area that can be printed
	//save map
	void save_map() {
		//shamelessly stolen from stackoverflow, clears map_data/saved_map.txt
		std::ofstream ofs;
		ofs.open("map_data/saved_map.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		
		ofstream outs("map_data/saved_map.txt");
		for (const auto &v : view) {
			string s;
			for (char c : v) {
				s.push_back(c);
			}
			outs << s << "\n";
		}
	}
	//load saved map
	void load_map() {
		view.clear();
		ifstream ins("map_data/saved_map.txt");
		for (int i = 0; i < HEIGHT; i++) {
			string s;
			getline(ins, s);
			vector<char> vec;
			for (int j = 0; j < WIDTH; j++) {
				vec.push_back(s.at(j));
			}
			view.push_back(vec);
		}
		
	}
	//generate map
	void init_map() {
		uniform_int_distribution<int> d100(1, 100);
		view.clear();
		layout.clear();
		//randomly generating the layout
		for (int i = 0; i < LAYOUT_SIZE; i++) {
			vector<int> row;
			for (int j = 0; j < LAYOUT_SIZE; j++) {
				row.push_back(d100(gen) % paths.size());
			}
			layout.push_back(row);
		}

		load_rooms(rooms, {stairs}); //puts the staircase room at the end of vector rooms
		layout.at(d100(gen) % LAYOUT_SIZE).at(d100(gen) % LAYOUT_SIZE) = -1;//-1 in layout corresponds to stairs
		
		/*
		//couts the layout of the map
		for (const auto &v : layout) {
			for (int i : v) {
				cout << i;
			}
			cout << endl;
		}
		*/

		//translating the layout into characters that get output on the screen (by pulling from vector rooms)

		//iterates through the different roooms (in vector layout) on the y axis
		for (int i = 0; i < LAYOUT_SIZE; i++) {
			//iterates through contents of a room (in rooms.at(layout.at(i))) on y axis
			for (int j = 0; j < ROOM_HEIGHT; j++) {
				//iterates through the different rooms (in vector layout) on the x axis
				vector<char> row;
				for (int k = 0; k < LAYOUT_SIZE; k++) {
					//iterates through contents of a room on x axis
					for (int l = 0; l < ROOM_WIDTH; l++) {
						if (layout.at(i).at(k) == -1) row.push_back(rooms.back().at(j).at(l));
						else row.push_back(rooms.at(layout.at(i).at(k)).at(j).at(l));
					}
				}
				view.push_back(row);
			}
		}

		//putting walls around the edges
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				if (i == 0 && view.at(i + 1).at(j) != WALL && view.at(i + 1).at(j) != VOID) view.at(i).at(j) = WALL;
				if (j == 0 && view.at(i).at(j + 1) != WALL && view.at(i).at(j + 1) != VOID) view.at(i).at(j) = WALL;
				if (i == HEIGHT - 1 && view.at(i - 1).at(j) != WALL && view.at(i - 1).at(j) != VOID) view.at(i).at(j) = WALL;
				if (j == WIDTH - 1 && view.at(i).at(j - 1) != WALL && view.at(i).at(j - 1) != VOID) view.at(i).at(j) = WALL;
			}
		}

		//placing monsters and chests
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				if (d100(gen) < 2 && (view.at(i).at(j) != WALL && view.at(i).at(j) != VOID)) view.at(i).at(j) = MONSTER;
				if (d100(gen) < 2 && !(i % 3) &&  (view.at(i).at(j) != WALL && view.at(i).at(j) != VOID)) view.at(i).at(j) = TREASURE;
			}
		}

	}

	//Draw the DISPLAY tiles around coordinate (x,y)
	void draw(int x, int y) {
		int start_x = x - DISPLAY/2;
		int end_x = x + DISPLAY/2;
		int start_y = y - DISPLAY/2;
		int end_y = y + DISPLAY/2;

		//Bounds check to handle the edges
		if (start_x < 0) {
			end_x = end_x - start_x;
			start_x = 0;
		}
		if (end_x > WIDTH-1) {
			start_x = start_x - (end_x - (WIDTH-1));
			end_x = WIDTH-1;
		}
		if (start_y < 0) {
			end_y = end_y - start_y;
			start_y = 0;
		}
		if (end_y > HEIGHT-1) {
			start_y = start_y - (end_y - (HEIGHT-1));
			end_y = HEIGHT-1;
		}

		
		//Now draw the map using NCURSES
		for (size_t i = start_y; i <= end_y; i++) {
			for (size_t j = start_x; j <= end_x; j++) {
				//if (i == cursor_x && j == cursor_y)
				//	attron(A_UNDERLINE | A_BOLD);
				int color = 1;
				if (view[i][j] == WALL) color = 5;
				else if (view[i][j] == MONSTER) color = 2;
				else if (view[i][j] == TREASURE) color = 4;
				
				if (i == y && j == x) {
					color = 3;
					attron(COLOR_PAIR(color));
					mvaddch(i-start_y,j-start_x, HERO);
				} else {
					attron(COLOR_PAIR(color));
					mvaddch(i-start_y,j-start_x,view[i][j]);
				}
				attroff(COLOR_PAIR(color));
				//attroff(A_UNDERLINE | A_BOLD);
			}
		}

	}
	Map() {
		load_rooms(rooms, paths);
		init_map();
	}

	//returns whatever character is in the map at the provided coordinates
	char spot_data(int x, int y) const {
		assert(x < WIDTH && y < HEIGHT && x >= 0 && y >= 0);
		return view[y][x];
	}

	void set_spot(int x, int y, char c) {
		assert(x < WIDTH && y < HEIGHT && x >= 0 && y >= 0);
		view[y][x] = c;
	}
	
};

