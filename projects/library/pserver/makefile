################################################################################
################################################################################
##                                                                            ##
##  12.31.1999  Performance Server Library v2.000                             ##
##                                                                            ##
##                                                                            ##
##  Multithreaded Performace Server Library Objects                           ##
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

OBJFLAGS    = -g -pthread -I../include


PSERVER_CARAPACE_DIR        = ./carapace/
PSERVER_DIRECTOR_DIR        = ./directors/
PSERVER_GATE_DIR            = ./gate/
PSERVER_PSERVER_DIR         = ./

PSERVER_CARAPACE_OBJS       = carapace_o.o workThread_o.o
PSERVER_DIRECTOR_OBJS       = threadDirector_o.o queueDirector_o.o                 \
                              executionDirector_o.o serverDirector_o.o
PSERVER_GATE_OBJS           = inputGate_o.o outputGate_o.o
PSERVER_PSERVER_OBJS        = pserver_o.o #performanceTuning_o.o

SSERVER_TELENET_DIR         = ./telenet/
SSERVER_DATAOBJS_DIR        = ./dataObjects/
SSERVER_SSERVER_DIR         = ./

SSERVER_TELENET_OBJS        = client_o.o server_o.o sendrecv_o.o
SSERVER_DATA_OBJS           = input_o.o output_o.o


################################################################################
## All.                                                                       ##
################################################################################

all:
	@echo "Performance Server Library v2.000    12.31.1999"
	@echo "Copyright 1999-2019  Daniel Huffman  All rights reserved."
	@echo `date`
	make $(SSERVER_TELENET_OBJS)
	make $(SSERVER_DATA_OBJS)
	make $(PSERVER_CARAPACE_OBJS)
	make $(PSERVER_DIRECTOR_OBJS)
	make $(PSERVER_GATE_OBJS)
	make $(PSERVER_PSERVER_OBJS)
	ar rvs pserver_o.a *.o
	cp pserver_o.a libpserver_o.a
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
## Communication Objects.                                                     ##
################################################################################

client_o.o: $(SSERVER_TELENET_DIR)client_o.h $(SSERVER_TELENET_DIR)client_o.cc
	$(CC) $(OBJFLAGS) -c $(SSERVER_TELENET_DIR)client_o.cc

server_o.o: $(SSERVER_TELENET_DIR)server_o.h $(SSERVER_TELENET_DIR)server_o.cc
	$(CC) $(OBJFLAGS) -c $(SSERVER_TELENET_DIR)server_o.cc

sendrecv_o.o: $(SSERVER_TELENET_DIR)sendrecv_o.h $(SSERVER_TELENET_DIR)sendrecv_o.cc
	$(CC) $(OBJFLAGS) -c $(SSERVER_TELENET_DIR)sendrecv_o.cc


################################################################################
## Data Objects.                                                              ##
################################################################################

input_o.o: $(SSERVER_DATAOBJS_DIR)input_o.h $(SSERVER_DATAOBJS_DIR)input_o.cc
	$(CC) $(OBJFLAGS) -c $(SSERVER_DATAOBJS_DIR)input_o.cc

output_o.o: $(SSERVER_DATAOBJS_DIR)output_o.h $(SSERVER_DATAOBJS_DIR)output_o.cc
	$(CC) $(OBJFLAGS) -c $(SSERVER_DATAOBJS_DIR)output_o.cc


################################################################################
## Clean.                                                                     ##
################################################################################
clean:
	rm -f *.o *.a


################################################################################
################################################################################
