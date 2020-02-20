a.out: main.o fighter.o combat_data/fighter.h map.h load_rooms.h player.h
	\g++ main.o fighter.o -lcurl -lncurses -O3 

main.o: main.cc player.h map.h
	\g++ -c main.cc -O3

fighter.o: combat_data/fighter.cc combat_data/fighter.h
	g++ -c combat_data/fighter.cc

clean:
	rm a.out core *.o
