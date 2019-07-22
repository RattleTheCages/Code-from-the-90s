################################################################################
################################################################################
##                                                                            ##
##12.31.1999  Performance Server Library v2.000  Daniel Huffman               ##
##                                                                            ##
##                                                                            ##
##  Multithreaded Performace Server Library Objects                           ##
##                                                                            ##
##                                                                            ##
##    Please note.  The header file dependences are not complete in this      ##
##    makefile.  If any changes are made to header files, please `make clean' ##
##    before executing `make all'.                                            ##
##                                                                            ##
################################################################################
################################################################################


# Use a complier that is POSIX threads enabled.
CC          = /opt/SUNWspro/bin/CC

OBJFLAGS    = -g -pthread


PSERVER_CARAPACE_DIR        = ./carapace/
PSERVER_DIRECTOR_DIR        = ./directors/
PSERVER_GATE_DIR            = ./gate/
PSERVER_PSERVER_DIR         = ./

PSERVER_CARAPACE_OBJS       = carapace.o workthread.o
PSERVER_DIRECTOR_OBJS       = threadDirector.o queueDirector.o                 \
                              executionDirector.o serverDirector.o
PSERVER_GATE_OBJS           = inputgate.o outputgate.o
PSERVER_PSERVER_OBJS        = pserver.o performancetuning.o


################################################################################
## All.                                                                       ##
################################################################################

all:
	@echo "Performance Server Library v2.000    12.31.99    Daniel Huffman"
	@echo `date`
	make $(PSERVER_CARAPACE_OBJS)
	make $(PSERVER_DIRECTOR_OBJS)
	make $(PSERVER_GATE_OBJS)
	make $(PSERVER_PSERVER_OBJS)
	@echo `date`


################################################################################
## Perfromance Mulithreaded Server Objects.                                   ##
################################################################################


################################################################################
## Carapace Objects.                                                          ##
################################################################################

carapace.o: $(PSERVER_CARAPACE_DIR)carapace.h $(PSERVER_CARAPACE_DIR)carapace.cc
	$(CC) $(OBJFLAGS) -c $(PSERVER_CARAPACE_DIR)carapace.cc

workthread.o: $(PSERVER_CARAPACE_DIR)workthread.h                              \
             $(PSERVER_CARAPACE_DIR)workthread.cc
	$(CC) $(OBJFLAGS) -c $(PSERVER_CARAPACE_DIR)workthread.cc


################################################################################
## Director Objects.                                                          ##
################################################################################

threadDirector.o: $(PSERVER_DIRECTOR_DIR)threadDirector.h                      \
                  $(PSERVER_DIRECTOR_DIR)threadDirector.cc
	$(CC) $(OBJFLAGS) -c $(PSERVER_DIRECTOR_DIR)threadDirector.cc

queueDirector.o: $(PSERVER_DIRECTOR_DIR)queueDirector.h                        \
                 $(PSERVER_DIRECTOR_DIR)queueDirector.cc
	$(CC) $(OBJFLAGS) -c $(PSERVER_DIRECTOR_DIR)queueDirector.cc

executionDirector.o: $(PSERVER_DIRECTOR_DIR)executionDirector.h                \
                     $(PSERVER_DIRECTOR_DIR)executionDirector.cc
	$(CC) $(OBJFLAGS) -c $(PSERVER_DIRECTOR_DIR)executionDirector.cc

serverDirector.o: $(PSERVER_DIRECTOR_DIR)serverDirector.h                      \
                  $(PSERVER_DIRECTOR_DIR)serverDirector.cc
	$(CC) $(OBJFLAGS) -c $(PSERVER_DIRECTOR_DIR)serverDirector.cc


################################################################################
## Gate Objects.                                                              ##
################################################################################

inputgate.o: $(PSERVER_GATE_DIR)inputgate.h $(PSERVER_GATE_DIR)inputgate.cc
	$(CC) $(OBJFLAGS) -c $(PSERVER_GATE_DIR)inputgate.cc

outputgate.o: $(PSERVER_GATE_DIR)outputgate.h $(PSERVER_GATE_DIR)outputgate.cc
	$(CC) $(OBJFLAGS) -c $(PSERVER_GATE_DIR)outputgate.cc


################################################################################
## Performace Multithread Server Objects.                                     ##
################################################################################

pserver.o: $(PSERVER_PSERVER_DIR)pserver.h $(PSERVER_PSERVER_DIR)pserver.cc
	$(CC) $(OBJFLAGS) -c $(PSERVER_PSERVER_DIR)pserver.cc

performancetuning.o: $(PSERVER_PSERVER_DIR)performancetuning.h                 \
                     $(PSERVER_PSERVER_DIR)performancetuning.cc
	$(CC) $(OBJFLAGS) -c $(PSERVER_PSERVER_DIR)performancetuning.cc


################################################################################
## Clean.                                                                     ##
################################################################################
clean:
	rm -f *.o


################################################################################
################################################################################
