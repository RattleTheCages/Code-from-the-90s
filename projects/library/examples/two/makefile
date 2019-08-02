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



# Use a complier that is POSIX threads enabled.
CC          = g++

OBJFLAGS    = -g -I../../lib/thread -I../../lib/string -I../../lib/error -I../../lib/memory -I../../lib/other -I../../lib/cron -I../../lib/log -I../../pserver -I../../pserver/directors -I../../pserver/telenet -I../../pserver/carapace -I../../pserver/dataObjects -I../../pserver/gate
LINKFLAGS   = -pthread


PSERVER_DIR = ../../../library/pserver/
PLIB_DIR    = ../../../library/lib/

EXECS       = client2 server2


################################################################################
## All.                                                                       ##
################################################################################

all:
	@echo "Performance Server Library v2.000    12.31.1999"
	@echo "Copyright 1999-2019  Daniel Huffman  All rights reserved."
	@echo "Example Two - P is for Performance"
	@echo `date`
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
        $(PLIB_DIR)plib_o.a


################################################################################
##                                                                            ##
################################################################################

client2.o: client2.cc
	$(CC) $(OBJFLAGS) -c client2.cc


client2: client2.o
	$(CC) $(LINKFLAGS) -o client2 client2.o                                \
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
