#c++ compiler
CPPC = g++
#compiler flags
CPPFLAGS = -c -O3
#linker flags
LFLAGS = -lcurl -lncurses -O3
#.o files
OBJS = fighter.o main.o
#executable name
PROG = RPG

${PROG}: ${OBJS}
	${CPPC} ${OBJS} ${LFLAGS} -o ${PROG}

%.o: %.cc
	${CPPC} $< ${CPPFLAGS}

clean:
	rm ${PROG} *.o

fighter.o: fighter.cc combat.h fighter.h
main.o:	main.cc map.h player.h combat.h load_rooms.h
