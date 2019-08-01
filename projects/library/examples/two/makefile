################################################################################
################################################################################
##                                                                            ##
## Copyright 12.31.1999  Performance Server Library v2.000  Daniel Huffman    ##
##                                                                            ##
##                                                                            ##
################################################################################
################################################################################


# Use a complier that is POSIX threads enabled.
CC          = g++

OBJFLAGS    = -g -I../../lib/thread -I../../lib/string -I../../lib/error -I../../lib/memory -I../../lib/other -I../../lib/cron -I../../lib/log -I../../pserver -I../../pserver/directors -I../../sserver/telenet -I../../pserver/carapace -I../../sserver/dataObjects -I../../pserver/gate
LINKFLAGS   = -pthread


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
        $(PSERVER_DIR)pserver_o.a                                              \
        $(SSERVER_DIR)sserver_o.a                                              \
        $(PLIB_DIR)plib_o.a


################################################################################
##                                                                            ##
################################################################################

client2.o: client2.cc
	$(CC) $(OBJFLAGS) -c client2.cc


client2: client2.o
	$(CC) $(LINKFLAGS) -o client2 client2.o                                \
        $(SSERVER_DIR)sserver_o.a                                              \
        $(PLIB_DIR)plib_o.a


################################################################################
## Clean.                                                                     ##
################################################################################

clean:
	rm -f $(EXECS)
	rm -f *.o

################################################################################
################################################################################
