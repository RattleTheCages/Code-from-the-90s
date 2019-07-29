################################################################################
################################################################################
##                                                                            ##
##12.31.1999  Performance Server Library v2.000  Daniel Huffman               ##
##                                                                            ##
##  Copyright Daniel Huffman 1999                                             ##
##                                                                            ##
##                                                                            ##
##  Single Thread Performace Server Library Objects                           ##
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

OBJFLAGS    = -g -pthread -I../lib/string -I../lib/thread -I../lib/error -I../lib/log -I../lib/cron


SSERVER_TELENET_DIR         = ./telenet/
SSERVER_DATAOBJS_DIR        = ./dataobjects/
SSERVER_SSERVER_DIR         = ./

SSERVER_TELENET_OBJS        = client.o server.o sendrecv.o
SSERVER_DATA_OBJS           = input.o output.o


################################################################################
## All.                                                                       ##
################################################################################

all:
	@echo "Performance Server Library v2.000    12.31.99    Daniel Huffman"
	@echo `date`
	make $(SSERVER_TELENET_OBJS)
	make $(SSERVER_DATA_OBJS)
	@echo `date`


################################################################################
## Communication Objects.                                                     ##
################################################################################

client.o: $(SSERVER_TELENET_DIR)client.h $(SSERVER_TELENET_DIR)client.cc
	$(CC) $(OBJFLAGS) -c $(SSERVER_TELENET_DIR)client.cc

server.o: $(SSERVER_TELENET_DIR)server.h $(SSERVER_TELENET_DIR)server.cc
	$(CC) $(OBJFLAGS) -c $(SSERVER_TELENET_DIR)server.cc

sendrecv.o: $(SSERVER_TELENET_DIR)sendrecv.h $(SSERVER_TELENET_DIR)sendrecv.cc
	$(CC) $(OBJFLAGS) -c $(SSERVER_TELENET_DIR)sendrecv.cc


################################################################################
## Data Objects.                                                              ##
################################################################################

input.o: $(SSERVER_DATAOBJS_DIR)input.h $(SSERVER_DATAOBJS_DIR)input.cc
	$(CC) $(OBJFLAGS) -c $(SSERVER_DATAOBJS_DIR)input.cc

output.o: $(SSERVER_DATAOBJS_DIR)output.h $(SSERVER_DATAOBJS_DIR)output.cc
	$(CC) $(OBJFLAGS) -c $(SSERVER_DATAOBJS_DIR)output.cc


################################################################################
## Clean.                                                                     ##
################################################################################
clean:
	rm -f *.o


################################################################################
################################################################################
