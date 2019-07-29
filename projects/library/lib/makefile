################################################################################
################################################################################
##                                                                            ##
##12.31.1999  Performance Server Library v2.000  Daniel Huffman               ##
##                                                                            ##
##                                                                            ##
##  Performace, Thread, and System Resource Abstraction Library Objects       ##
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

OBJFLAGS    = -g -pthread


PLIB_STRING_DIR     = ./string/
PLIB_ERROR_DIR      = ./error/
PLIB_CRON_DIR       = ./cron/
PLIB_LOG_DIR        = ./log/
PLIB_THREAD_DIR     = ./thread/
PLIB_PARSE_DIR      = ./parse/
PLIB_OTHER_DIR      = ./other/

PLIB_STRING_OBJS    = string.o
PLIB_ERROR_OBJS     = error.o
PLIB_CRON_OBJS      = time.o
PLIB_LOG_OBJS       = log.o
PLIB_THREAD_OBJS    = thread.o mutex.o
PLIB_PARSE_OBJS     = parse.o
PLIB_OTHER_OBJS     = sysinfo.o rand.o decimal.o


################################################################################
## All.                                                                       ##
################################################################################

all:
	@echo "Performance Server Library v2.000    12.31.99    Daniel Huffman"
	@echo `date`
	make $(PLIB_STRING_OBJS)
	make $(PLIB_ERROR_OBJS)
	make $(PLIB_CRON_OBJS)
	make $(PLIB_LOG_OBJS)
	make $(PLIB_THREAD_OBJS)
	make $(PLIB_PARSE_OBJS)
	make $(PLIB_OTHER_OBJS)
	@echo `date`


################################################################################
## Perfromance Library Objects.                                               ##
################################################################################


################################################################################
## String Object.                                                             ##
################################################################################

string.o: $(PLIB_STRING_DIR)string.h $(PLIB_STRING_DIR)string.cc
	$(CC) $(OBJFLAGS) -c $(PLIB_STRING_DIR)string.cc


################################################################################
## Error Object.                                                              ##
################################################################################

error.o: $(PLIB_ERROR_DIR)error.h $(PLIB_ERROR_DIR)error.cc
	$(CC) $(OBJFLAGS) -c $(PLIB_ERROR_DIR)error.cc


################################################################################
## Cronograph Objects.                                                        ##
################################################################################

time.o: $(PLIB_CRON_DIR)time.h $(PLIB_CRON_DIR)time.cc
	$(CC) $(OBJFLAGS) -c $(PLIB_CRON_DIR)time.cc


################################################################################
## Log Object.                                                                ##
################################################################################

log.o: $(PLIB_LOG_DIR)log.h $(PLIB_LOG_DIR)log.cc
	$(CC) $(OBJFLAGS) -c $(PLIB_LOG_DIR)log.cc


################################################################################
## Thread Objects.                                                            ##
################################################################################

thread.o: $(PLIB_THREAD_DIR)thread.h $(PLIB_THREAD_DIR)thread.cc
	$(CC) $(OBJFLAGS) -c $(PLIB_THREAD_DIR)thread.cc

mutex.o: $(PLIB_THREAD_DIR)mutex.h $(PLIB_THREAD_DIR)mutex.cc
	$(CC) $(OBJFLAGS) -c $(PLIB_THREAD_DIR)mutex.cc


################################################################################
## Parse Object.                                                              ##
################################################################################

parse.o: $(PLIB_PARSE_DIR)parse.h $(PLIB_PARSE_DIR)parse.cc
	$(CC) $(OBJFLAGS) -c $(PLIB_PARSE_DIR)parse.cc


################################################################################
## Other Objects.                                                             ##
################################################################################

sysinfo.o: $(PLIB_OTHER_DIR)sysinfo.h $(PLIB_OTHER_DIR)sysinfo.cc
	$(CC) $(OBJFLAGS) -c $(PLIB_OTHER_DIR)sysinfo.cc

rand.o: $(PLIB_OTHER_DIR)rand.h $(PLIB_OTHER_DIR)rand.cc
	$(CC) $(OBJFLAGS) -c $(PLIB_OTHER_DIR)rand.cc

decimal.o: $(PLIB_OTHER_DIR)decimal.h $(PLIB_OTHER_DIR)decimal.cc
	$(CC) $(OBJFLAGS) -c $(PLIB_OTHER_DIR)decimal.cc


################################################################################
## Clean.                                                                     ##
################################################################################
clean:
	rm -f *.o


################################################################################
################################################################################
