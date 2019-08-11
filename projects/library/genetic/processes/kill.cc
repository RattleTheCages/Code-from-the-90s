/**  kill.cc  ******************************************************************

    12.31.1999  Performance Server Library v2.000





when      who     what
9.24.96   Dan     Creation.
6.23.98   Dan     Changed:  Using queue object now.
8.2.98    Dan     Added:    Using colony object's info size and last op.




                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/

#include <stdlib.h>
#include <fstream>
#include <iostream>//!!
using namespace std;
#include "log_o.h"
#include "rand_o.h"
#include "queue_o.h"
#include "entity_o.h"
#include "colony_o.h"


#define KILL_BUFF_SIZE 4096


rand_o rndm;
log_o  llog;


int main(int argc, char* argv[])  {
    long int x;
    string_o message;
    char buff[KILL_BUFF_SIZE];
    string_o s,t;


    ::llog.registerName(argv[0]);

    (message = "") << "colony `" << argv[1];
    message << "' population limit: " << argv[2];
    ::llog << message;


    colony_o          colony;
    queue_o<entity_o> entities;
    entity_o*         entp;
//    int               i,j,k;
    int               limit;
    ifstream          in;
    ofstream          out;
    int               population;

    limit = atoi(argv[2]);


/**  Read in file of the entities' DNA.  **************************************/


    colony.load(argv[1]);


    if(limit > colony.population())  return 1;



/**  Write to a file.  ********************************************************/


    colony.setLastOperation("kill");
    colony.setPopulation(limit);

    colony.unload(argv[1]);

}


/******************************************************************************/
