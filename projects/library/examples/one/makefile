################################################################################
################################################################################
##                                                                            ##
## Copyright 12.31.1999  Performance Server Library v2.000  Daniel Huffman    ##
##                                                                            ##
##                                                                            ##
##                                                                            ##
##    Please note.  The header file dependences are not complete in this      ##
##    makefile.  If any changes are made to header files, please `make clean' ##
##    before executing `make all'.                                            ##
##                                                                            ##
################################################################################
################################################################################


CC          = g++

OBJFLAGS    = -g -D_REENTRANT -I../../lib/thread -I../../lib/error -I../../lib/log -I../../lib/string -I../../lib/memory -I../../lib/other -I../../lib/cron -I../../sserver/telenet -I../../pserver -I../../pserver/directors -I../../sserver/telenet -I../../pserver/carapace -I../../sserver/dataObjects -I../../pserver/gate
LINKFLAGS   = -pthread -lnsl -D_REENTRENT


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
        $(PSERVER_DIR)pserver_o.a                                              \
        $(SSERVER_DIR)sserver_o.a                                              \
        $(PLIB_DIR)plib_o.a


################################################################################
##                                                                            ##
################################################################################

client1.o: client1.cc
	$(CC) $(OBJFLAGS) -c client1.cc


client1: client1.o
	$(CC) $(LINKFLAGS) -o client1 client1.o                                \
        $(SSERVER_DIR)sserver_o.a                                              \
        $(PLIB_DIR)plib_o.a


clientw.o: clientw.cc
	$(CC) $(OBJFLAGS) -c clientw.cc


clientw: clientw.o
	$(CC) $(LINKFLAGS) -o clientw clientw.o                                \
        $(SSERVER_DIR)sserver_o.a                                              \
        $(PLIB_DIR)plib_o.a


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
