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
SSERVER_DATAOBJS_DIR        = ./dataObjects/
SSERVER_SSERVER_DIR         = ./

SSERVER_TELENET_OBJS        = client_o.o server_o.o sendrecv_o.o
SSERVER_DATA_OBJS           = input_o.o output_o.o


################################################################################
## All.                                                                       ##
################################################################################

all:
	@echo "Performance Server Library v2.000    12.31.99    Daniel Huffman"
	@echo `date`
	make $(SSERVER_TELENET_OBJS)
	make $(SSERVER_DATA_OBJS)
	ar rvs sserver_o.a *.o
	@echo `date`


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
