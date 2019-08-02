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

OBJFLAGS    = -g -I../../lib/thread -I../../lib/string -I../../lib/log -I../../lib/error -I../../lib/memory -I../../lib/other -I../../lib/cron -I../../pserver/telenet -I../../pserver -I../../pserver/directors -I../../pserver/telenet -I../../pserver/carapace -I../../pserver/dataObjects -I../../pserver/gate
LINKFLAGS   = -pthread


PSERVER_DIR = ../../../library/pserver/
PLIB_DIR    = ../../../library/lib/

EXECS       = client3 server3


################################################################################
## All.                                                                       ##
################################################################################

all:
	@echo "Performance Server Library v2.000    12.31.1999"
	@echo "Copyright 1999-2019  Daniel Huffman  All rights reserved."
	@echo "Example Three - Taking care of shared memory"
	@echo `date`
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
        $(PLIB_DIR)plib_o.a


################################################################################
##                                                                            ##
################################################################################

client3.o: client3.cc
	$(CC) $(OBJFLAGS) -c client3.cc


client3: client3.o
	$(CC) $(LINKFLAGS) -o client3 client3.o                                \
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
