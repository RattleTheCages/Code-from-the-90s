################################################################################
################################################################################
##                                                                            ##
##  12.31.1999  Performance Server Library v2.000                             ##
##                                                                            ##
##                                                                            ##
##  Genetic Artifical Intellgence Objects                                     ##
##                                                                            ##
##                                                                            ##
##    Please note.  The header file dependences are not complete in this      ##
##    makefile.  If any changes are made to header files, please `make clean' ##
##    before executing `make all'.                                            ##
##                                                                            ##
##                                                                            ##
##                 Copyright 1999-2019  Daniel Huffman  All rights reserved.  ##
##                                                                            ##
################################################################################
################################################################################



CC          = g++

OBJFLAGS    = -g -I../include -I./entity
LINKFLAGS   = -pthread



##all: init reproduce kill spellsort lottosort

all: init kill reproduce spellsort genetic_o.a



OBJS = entity_o.o chromosome_o.o name_o.o colony_o.o traits_o.o




LIB_DIR       = ../lib/
ENTITY_DIR    = ./entity/
PROCESSES_DIR = ./processes/

LIB_OBJS      = ../lib/*.o




chromosome_o.o: ${ENTITY_DIR}chromosome_o.cc
	${CC} -c -g ${ENTITY_DIR}chromosome_o.cc ${OBJFLAGS}

entity_o.o: ${ENTITY_DIR}entity_o.cc
	${CC} -c -g ${ENTITY_DIR}entity_o.cc ${OBJFLAGS}

colony_o.o: ${ENTITY_DIR}colony_o.cc
	${CC} -c -g ${ENTITY_DIR}colony_o.cc ${OBJFLAGS}

name_o.o: ${ENTITY_DIR}name_o.cc
	${CC} -c -g ${ENTITY_DIR}name_o.cc ${OBJFLAGS} -I../include

traits_o.o: ${ENTITY_DIR}traits_o.cc
	${CC} -c -g ${ENTITY_DIR}traits_o.cc ${OBJFLAGS}

reproduce_o.o: ${PROCESSES_DIR}reproduce_o.cc
	${CC} -c -g ${PROCESSES_DIR}reproduce_o.cc ${OBJFLAGS}



init.o: ${PROCESSES_DIR}init.cc
	${CC} -c -g ${PROCESSES_DIR}init.cc ${OBJFLAGS}

spellsort.o: $(PROCESSES_DIR)spellsort.cc
	${CC} -c -g ${PROCESSES_DIR}spellsort.cc ${OBJFLAGS}

kill.o: ${PROCESSES_DIR}kill.cc
	${CC} -c -g ${PROCESSES_DIR}kill.cc ${OBJFLAGS}

lottosort.o: ${PROCESSES_DIR}lottosort.cc
	${CC} -c -g ${PROCESSES_DIR}lottosort.cc ${OBJFLAGS}



init: ${OBJS} init.o
	${CC} -o init init.o ${OBJS} ${LIB_DIR}/*.o ${LINKFLAGS}

kill: ${OBJS} kill.o
	${CC} -o kill kill.o ${OBJS} ${LIB_DIR}/*.o ${LINKFLAGS}

reproduce: ${OBJS} reproduce_o.o
	${CC} -o reproduce reproduce_o.o ${OBJS} ${LIB_DIR}/*.o ${LINKFLAGS}



lottosort: ${OBJS} lottosort.o
	${CC} -o lottosort lottosort.o ${OBJS} ${LIB_OBJS} ${LINKFLAGS}


spellsort: ${OBJS} spellsort.o
	${CC} -o spellsort spellsort.o ${OBJS} ${LIB_OBJS} ${LINKFLAGS}

genetic_o.a: ${OBJS}
	ar rvs genetic_o.a ${OBJS}
	cp genetic_o.a libgenetic_o.a




clean:
	rm -f *.o *.a
	rm -f del seed.txt core *.core
	rm -f lottosort kill reproduce init count spellsort


