################################################################################
################################################################################
##                                                                            ##
##12.31.1999  Performance Server Library v2.000  Daniel Huffman               ##
##                                                                            ##
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

OBJFLAGS    = -g -D_REENTRANT
LINKFLAGS   = -lpthread -lsocket -lnsl -D_REENTRENT


SSERVER_DIR = ../../../library/sserver/
PSERVER_DIR = ../../../library/pserver/
PLIB_DIR    = ../../../library/lib/

EXECS       = client1 server1 clientw


################################################################################
## All.                                                                       ##
################################################################################

all:
	@echo `date`
	@echo "Performance Server Object Librarys 1.0"
	@echo "Example One - Simple Performance Client-Server Pair"
	@make $(EXECS)
	@echo `date`


################################################################################
##                                                                            ##
################################################################################

server1.o: server1.cc
	$(CC) $(OBJFLAGS) -c server1.cc


server1: server1.o
	$(CC) $(LINKFLAGS) -o server1 server1.o                                \
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

client1.o: client1.cc
	$(CC) $(OBJFLAGS) -c client1.cc


client1: client1.o
	$(CC) $(LINKFLAGS) -o client1 client1.o                                \
        $(SSERVER_DIR)client.o                                                 \
        $(SSERVER_DIR)sendrecv.o                                               \
        $(PLIB_DIR)*.o


clientw.o: clientw.cc
	$(CC) $(OBJFLAGS) -c clientw.cc


clientw: clientw.o
	$(CC) $(LINKFLAGS) -o clientw clientw.o                                \
        $(SSERVER_DIR)client.o                                                 \
        $(SSERVER_DIR)sendrecv.o                                               \
        $(PLIB_DIR)*.o \
        $(PLIB_DIR)/Templates.DB/*.o


################################################################################
## Clean.                                                                     ##
################################################################################

clean:
	rm -f $(EXECS)
	rm -f ps1
	rm -f sc1
	rm -f *.o

################################################################################
################################################################################
