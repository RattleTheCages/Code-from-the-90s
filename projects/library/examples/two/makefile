################################################################################
################################################################################
##                                                                            ##
##12.31.1999  Performance Server Library v2.000  Daniel Huffman               ##
##                                                                            ##
##                                                                            ##
################################################################################
################################################################################


# Use a complier that is POSIX threads enabled.
CC          = g++

OBJFLAGS    = -g -I../../lib/thread -I../../lib/string -I../../lib/error -I../../lib/memory -I../../lib/other -I../../lib/cron -I../../lib/log
LINKFLAGS   = -lpthread


SSERVER_DIR = ../../../library/sserver/
PSERVER_DIR = ../../../library/pserver/
PLIB_DIR    = ../../../library/lib/

EXECS       = client2 server2


################################################################################
## All.                                                                       ##
################################################################################

all:
	@echo `date`
	@echo "Performance Server Object Librarys 1.0"
	@echo "Example Two - P is for Preformace"
	@make $(EXECS)
	@echo `date`


################################################################################
##                                                                            ##
################################################################################

server2.o: server2.cc
	$(CC) $(OBJFLAGS) -c server2.cc


server2: server2.o
	$(CC) $(LINKFLAGS) -o server2 server2.o                                \
        $(SSERVER_DIR)input.o                                                  \
        $(SSERVER_DIR)output.o                                                 \
        $(SSERVER_DIR)server.o                                                 \
        $(SSERVER_DIR)sendrecv.o                                               \
        $(PSERVER_DIR)pserver.o                                                \
        $(PSERVER_DIR)queueDirector.o                                          \
        $(PSERVER_DIR)executionDirector.o                                      \
        $(PSERVER_DIR)threadDirector.o                                         \
        $(PSERVER_DIR)serverDirector.o                                         \
        $(PSERVER_DIR)inputgate.o                                              \
        $(PSERVER_DIR)outputgate.o                                             \
        $(PSERVER_DIR)workthread.o                                             \
        $(PSERVER_DIR)carapace.o                                               \
        $(PLIB_DIR)*.o


################################################################################
##                                                                            ##
################################################################################

client2.o: client2.cc
	$(CC) $(OBJFLAGS) -c client2.cc


client2: client2.o
	$(CC) $(LINKFLAGS) -o client2 client2.o                                \
        $(SSERVER_DIR)client.o                                                 \
        $(SSERVER_DIR)sendrecv.o                                               \
        $(PLIB_DIR)*.o


################################################################################
## Clean.                                                                     ##
################################################################################

clean:
	rm -f $(EXECS)
	rm -f *.o

################################################################################
################################################################################
