################################################################################
################################################################################
##                                                                            ##
##    12.31.1999  Performance Server Library v2.000                           ##
##                                                                            ##
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

OBJFLAGS    = -g -D_REENTRANT -I../../lib/thread -I../../lib/error -I../../lib/log -I../../lib/string -I../../lib/memory -I../../lib/other -I../../lib/cron -I../../pserver/telenet -I../../pserver -I../../pserver/directors -I../../pserver/telenet -I../../pserver/carapace -I../../pserver/dataObjects -I../../pserver/gate
LINKFLAGS   = -pthread -lnsl -D_REENTRENT


SSERVER_DIR = ../../../library/sserver/
PSERVER_DIR = ../../../library/pserver/
PLIB_DIR    = ../../../library/lib/

EXECS       = client1 server1 clientw


################################################################################
## All.                                                                       ##
################################################################################

all:
	@echo "Performance Server Library v2.000    12.31.1999"
	@echo "Copyright 1999-2019  Daniel Huffman  All rights reserved."
	@echo "Example One - Simple Performance Client-Server Pair"
	@echo `date`
	@make $(EXECS)
	@echo `date`


################################################################################
##                                                                            ##
################################################################################

server1.o: server1.cc
	$(CC) $(OBJFLAGS) -c server1.cc


server1: server1.o
	$(CC) $(LINKFLAGS) -o server1 server1.o                                \
        $(PSERVER_DIR)pserver_o.a                                              \
        $(PLIB_DIR)plib_o.a


################################################################################
##                                                                            ##
################################################################################

client1.o: client1.cc
	$(CC) $(OBJFLAGS) -c client1.cc


client1: client1.o
	$(CC) $(LINKFLAGS) -o client1 client1.o                                \
        $(PSERVER_DIR)pserver_o.a                                              \
        $(PLIB_DIR)plib_o.a


clientw.o: clientw.cc
	$(CC) $(OBJFLAGS) -c clientw.cc


clientw: clientw.o
	$(CC) $(LINKFLAGS) -o clientw clientw.o                                \
        $(PSERVER_DIR)pserver_o.a                                              \
        $(PLIB_DIR)plib_o.a


################################################################################
## Clean.                                                                     ##
################################################################################

clean:
	rm -f $(EXECS)
	rm -f *.o

################################################################################
################################################################################
