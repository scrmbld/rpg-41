a.out: main.cc map.h load_rooms.h
	g++ main.cc -lcurl -lncurses 

clean:
	rm a.out core *.o
