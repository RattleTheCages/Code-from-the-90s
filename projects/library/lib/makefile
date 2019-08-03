################################################################################
################################################################################
##                                                                            ##
##  12.31.1999  Performance Server Library v2.000                             ##
##                                                                            ##
##                                                                            ##
##  Performace, Thread, and System Resource Abstraction Library Objects       ##
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

OBJFLAGS    = -g -pthread -I../include -I./string -I./thread -I./error -I./memory


PLIB_STRING_DIR     = ./string/
PLIB_ERROR_DIR      = ./error/
PLIB_CRON_DIR       = ./cron/
PLIB_LOG_DIR        = ./log/
PLIB_THREAD_DIR     = ./thread/
PLIB_PARSE_DIR      = ./parse/
PLIB_OTHER_DIR      = ./other/

PLIB_STRING_OBJS    = string_o.o
PLIB_ERROR_OBJS     = error_o.o
PLIB_CRON_OBJS      = time_o.o
PLIB_LOG_OBJS       = log_o.o
PLIB_THREAD_OBJS    = thread_o.o mutex_o.o
PLIB_PARSE_OBJS     = parse_o.o
PLIB_OTHER_OBJS     = sysinfo_o.o rand_o.o decimal_o.o


################################################################################
## All.                                                                       ##
################################################################################

all:
	@echo "Performance Server Library v2.000    12.31.1999"
	@echo "Copyright 1999-2019  Daniel Huffman  All rights reserved."
	@echo `date`
	make $(PLIB_STRING_OBJS)
	make $(PLIB_ERROR_OBJS)
	make $(PLIB_CRON_OBJS)
	make $(PLIB_LOG_OBJS)
	make $(PLIB_THREAD_OBJS)
	make $(PLIB_PARSE_OBJS)
	make $(PLIB_OTHER_OBJS)
	ar rvs plib_o.a *.o
	@echo `date`


################################################################################
## Perfromance Library Objects.                                               ##
################################################################################


################################################################################
## String Object.                                                             ##
################################################################################

string_o.o: $(PLIB_STRING_DIR)string_o.h $(PLIB_STRING_DIR)string_o.cc
	$(CC) $(OBJFLAGS) -c $(PLIB_STRING_DIR)string_o.cc


################################################################################
## Error Object.                                                              ##
################################################################################

error_o.o: $(PLIB_ERROR_DIR)error_o.h $(PLIB_ERROR_DIR)error_o.cc
	$(CC) $(OBJFLAGS) -c $(PLIB_ERROR_DIR)error_o.cc


################################################################################
## Cronograph Objects.                                                        ##
################################################################################

time_o.o: $(PLIB_CRON_DIR)time_o.h $(PLIB_CRON_DIR)time_o.cc
	$(CC) $(OBJFLAGS) -c $(PLIB_CRON_DIR)time_o.cc


################################################################################
## Log Object.                                                                ##
################################################################################

log_o.o: $(PLIB_LOG_DIR)log_o.h $(PLIB_LOG_DIR)log_o.cc
	$(CC) $(OBJFLAGS) -c $(PLIB_LOG_DIR)log_o.cc


################################################################################
## Thread Objects.                                                            ##
################################################################################

thread_o.o: $(PLIB_THREAD_DIR)thread_o.h $(PLIB_THREAD_DIR)thread_o.cc
	$(CC) $(OBJFLAGS) -c $(PLIB_THREAD_DIR)thread_o.cc

mutex_o.o: $(PLIB_THREAD_DIR)mutex_o.h $(PLIB_THREAD_DIR)mutex_o.cc
	$(CC) $(OBJFLAGS) -c $(PLIB_THREAD_DIR)mutex_o.cc


################################################################################
## Parse Object.                                                              ##
################################################################################

parse_o.o: $(PLIB_PARSE_DIR)parse_o.h $(PLIB_PARSE_DIR)parse_o.cc
	$(CC) $(OBJFLAGS) -c $(PLIB_PARSE_DIR)parse_o.cc


################################################################################
## Other Objects.                                                             ##
################################################################################

sysinfo_o.o: $(PLIB_OTHER_DIR)sysinfo_o.h $(PLIB_OTHER_DIR)sysinfo_o.cc
	$(CC) $(OBJFLAGS) -c $(PLIB_OTHER_DIR)sysinfo_o.cc

rand_o.o: $(PLIB_OTHER_DIR)rand_o.h $(PLIB_OTHER_DIR)rand_o.cc
	$(CC) $(OBJFLAGS) -c $(PLIB_OTHER_DIR)rand_o.cc

decimal_o.o: $(PLIB_OTHER_DIR)decimal_o.h $(PLIB_OTHER_DIR)decimal_o.cc
	$(CC) $(OBJFLAGS) -c $(PLIB_OTHER_DIR)decimal_o.cc


################################################################################
## Clean.                                                                     ##
################################################################################
clean:
	rm -f *.o *.a


################################################################################
################################################################################
