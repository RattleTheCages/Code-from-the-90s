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
CC          = g++

OBJFLAGS    = -g -pthread -I../lib/string -I../lib/memory -I../lib/thread -I../lib/cron -I../lib/log -I../lib/error -I../lib/other -I../sserver/dataObjects -I../sserver/telenet -I./carapace -I./gate -I./directors -I../genetic/entity


PSERVER_CARAPACE_DIR        = ./carapace/
PSERVER_DIRECTOR_DIR        = ./directors/
PSERVER_GATE_DIR            = ./gate/
PSERVER_PSERVER_DIR         = ./

PSERVER_CARAPACE_OBJS       = carapace_o.o workThread_o.o
PSERVER_DIRECTOR_OBJS       = threadDirector_o.o queueDirector_o.o                 \
                              executionDirector_o.o serverDirector_o.o
PSERVER_GATE_OBJS           = inputGate_o.o outputGate_o.o
PSERVER_PSERVER_OBJS        = pserver_o.o #performanceTuning_o.o


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
	ar rvs pserver_o.a *.o
	@echo `date`


################################################################################
## Perfromance Mulithreaded Server Objects.                                   ##
################################################################################


################################################################################
## Carapace Objects.                                                          ##
################################################################################

carapace_o.o: $(PSERVER_CARAPACE_DIR)carapace_o.h $(PSERVER_CARAPACE_DIR)carapace_o.cc
	$(CC) $(OBJFLAGS) -c $(PSERVER_CARAPACE_DIR)carapace_o.cc

workThread_o.o: $(PSERVER_CARAPACE_DIR)workThread_o.h                          \
             $(PSERVER_CARAPACE_DIR)workThread_o.cc
	$(CC) $(OBJFLAGS) -c $(PSERVER_CARAPACE_DIR)workThread_o.cc


################################################################################
## Director Objects.                                                          ##
################################################################################

threadDirector_o.o: $(PSERVER_DIRECTOR_DIR)threadDirector_o.h                    \
                  $(PSERVER_DIRECTOR_DIR)threadDirector_o.cc
	$(CC) $(OBJFLAGS) -c $(PSERVER_DIRECTOR_DIR)threadDirector_o.cc

queueDirector_o.o: $(PSERVER_DIRECTOR_DIR)queueDirector_o.h                        \
                 $(PSERVER_DIRECTOR_DIR)queueDirector_o.cc
	$(CC) $(OBJFLAGS) -c $(PSERVER_DIRECTOR_DIR)queueDirector_o.cc

executionDirector_o.o: $(PSERVER_DIRECTOR_DIR)executionDirector_o.h                \
                     $(PSERVER_DIRECTOR_DIR)executionDirector_o.cc
	$(CC) $(OBJFLAGS) -c $(PSERVER_DIRECTOR_DIR)executionDirector_o.cc

serverDirector_o.o: $(PSERVER_DIRECTOR_DIR)serverDirector_o.h                      \
                  $(PSERVER_DIRECTOR_DIR)serverDirector_o.cc
	$(CC) $(OBJFLAGS) -c $(PSERVER_DIRECTOR_DIR)serverDirector_o.cc


################################################################################
## Gate Objects.                                                              ##
################################################################################

inputGate_o.o: $(PSERVER_GATE_DIR)inputGate_o.h $(PSERVER_GATE_DIR)inputGate_o.cc
	$(CC) $(OBJFLAGS) -c $(PSERVER_GATE_DIR)inputGate_o.cc

outputGate_o.o: $(PSERVER_GATE_DIR)outputGate_o.h $(PSERVER_GATE_DIR)outputGate_o.cc
	$(CC) $(OBJFLAGS) -c $(PSERVER_GATE_DIR)outputGate_o.cc


################################################################################
## Performace Multithread Server Objects.                                     ##
################################################################################

pserver_o.o: $(PSERVER_PSERVER_DIR)pserver_o.h $(PSERVER_PSERVER_DIR)pserver_o.cc
	$(CC) $(OBJFLAGS) -c $(PSERVER_PSERVER_DIR)pserver_o.cc

#performanceTuning_o.o: $(PSERVER_PSERVER_DIR)performanceTuning_o.h                 \
#                     $(PSERVER_PSERVER_DIR)performanceTuning_o.cc
#	$(CC) $(OBJFLAGS) -c $(PSERVER_PSERVER_DIR)performanceTuning_o.cc


################################################################################
## Clean.                                                                     ##
################################################################################
clean:
	rm -f *.o *.a


################################################################################
################################################################################
