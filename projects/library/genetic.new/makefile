################################################################################
################################################################################
##                                                                            ##
##12.31.1999  Performance Server Library v2.000  Daniel Huffman               ##
##                                                                            ##
##                                                                            ##
##  Genetic Artifical Intellgence Objects                                     ##
##                                                                            ##
##                                                                            ##
##    Please note.  The header file dependences are not complete in this      ##
##    makefile.  If any changes are made to header files, please `make clean' ##
##    before executing `make all'.                                            ##
##                                                                            ##
################################################################################
################################################################################


# Use a complier that is POSIX threads enabled.
CC          = g++

OBJFLAGS    = -g -D_REENTRANT
LINKFLAGS   = -pthread



##all: init reproduce kill spellsort lottosort

all: init kill reproduce spellsort



OBJS = entity.o chromosome.o name.o colony.o




LIB_DIR       = ../lib/
ENTITY_DIR    = ./entity/
PROCESSES_DIR = ./processes/

LIB_OBJS      = ../lib/string.o ../lib/parse.o ../lib/rand.o




chromosome.o: ${ENTITY_DIR}chromosome.cc
	${CC} -c -g ${ENTITY_DIR}chromosome.cc ${OBJFLAGS}

entity.o: ${ENTITY_DIR}entity.cc
	${CC} -c -g ${ENTITY_DIR}entity.cc ${OBJFLAGS}

colony.o: ${ENTITY_DIR}colony.cc
	${CC} -c -g ${ENTITY_DIR}colony.cc ${OBJFLAGS}



name.o: ${PROCESSES_DIR}name.cc
	${CC} -c -g ${PROCESSES_DIR}name.cc ${OBJFLAGS}

init.o: ${PROCESSES_DIR}init.cc
	${CC} -c -g ${PROCESSES_DIR}init.cc ${OBJFLAGS}

reproduce.o: ${PROCESSES_DIR}reproduce.cc
	${CC} -c -g ${PROCESSES_DIR}reproduce.cc ${OBJFLAGS}

lottosort.o: ${PROCESSES_DIR}lottosort.cc
	${CC} -c -g ${PROCESSES_DIR}lottosort.cc ${OBJFLAGS}

spellsort.o: $(PROCESSES_DIR)spellsort.cc
	${CC} -c -g ${PROCESSES_DIR}spellsort.cc ${OBJFLAGS}

kill.o: ${PROCESSES_DIR}kill.cc
	${CC} -c -g ${PROCESSES_DIR}kill.cc ${OBJFLAGS}



init: ${OBJS} init.o
	${CC} -o init init.o ${OBJS} ${LIB_DIR}/*.o ${LINKFLAGS}

kill: ${OBJS} kill.o
	${CC} -o kill kill.o ${OBJS} ${LIB_DIR}/*.o ${LINKFLAGS}

reproduce: ${OBJS} reproduce.o
	${CC} -o reproduce reproduce.o ${OBJS} ${LIB_DIR}/*.o ${LINKFLAGS}



lottosort: ${OBJS} lottosort.o
	${CC} -o lottosort lottosort.o ${OBJS} ${LIB_OBJS} ${LINKFLAGS}


spellsort: ${OBJS} spellsort.o
	${CC} -o spellsort spellsort.o ${OBJS} ${LIB_OBJS} ${LINKFLAGS}




clean:
	rm -f *.o
	rm -f d del seed.txt core *.core
	rm -f lottosort kill reproduce init count spellsort


