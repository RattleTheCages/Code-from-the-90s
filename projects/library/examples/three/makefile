################################################################################
################################################################################
##                                                                            ##
## Copyright 12.31.1999  Performance Server Library v2.000  Daniel Huffman    ##
##                                                                            ##
##                                                                            ##
##                                                                            ##
##                                                                            ##
################################################################################
################################################################################


CC          = g++

OBJFLAGS    = -g -I../../lib/thread -I../../lib/string -I../../lib/log -I../../lib/error -I../../lib/memory -I../../lib/other -I../../lib/cron -I../../sserver/telenet -I../../pserver -I../../pserver/directors -I../../sserver/telenet -I../../pserver/carapace -I../../sserver/dataObjects -I../../pserver/gate
LINKFLAGS   = -pthread


SSERVER_DIR = ../../../library/sserver/
PSERVER_DIR = ../../../library/pserver/
PLIB_DIR    = ../../../library/lib/

EXECS       = client3 server3


################################################################################
## All.                                                                       ##
################################################################################

all:
	@echo `date`
	@echo "Performance Server Object Librarys 1.0"
	@echo "Example Three - Taking care of shared memory"
	@make $(EXECS)
	@echo `date`


################################################################################
##                                                                            ##
################################################################################

server3.o: server3.cc
	$(CC) $(OBJFLAGS) -c server3.cc


server3: server3.o
	$(CC) $(LINKFLAGS) -o server3 server3.o                                \
        $(PSERVER_DIR)pserver_o.a                                              \
        $(SSERVER_DIR)sserver_o.a                                              \
        $(PLIB_DIR)plib_o.a


################################################################################
##                                                                            ##
################################################################################

client3.o: client3.cc
	$(CC) $(OBJFLAGS) -c client3.cc


client3: client3.o
	$(CC) $(LINKFLAGS) -o client3 client3.o                                \
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
