/**  kill.cc  ******************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman





when      who     what
9.24.96   Dan     Creation.
6.23.98   Dan     Changed:  Using queue object now.
8.2.98    Dan     Added:    Using colony object's info size and last op.

*******************************************************************************/

#include <fstream.h>
#include <iostream.h>//!!
#include "../../lib/log/log.h"
#include "../../lib/other/rand.h"
#include "../../lib/thread/queue.h"
#include "../entity/entity.h"
#include "../entity/colony.h"


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

    in.open(argv[1]);
    if(!in)  {
        (message = "") << "File not found: " << argv[1];
        ::llog.error(message);
        return ERROR_FAIL;
    }


    s = "";
    x = 0;

    while(!in.eof())  {
        for(x=0;x<KILL_BUFF_SIZE;x++)  {
            in.get(buff[x]);
            if(in.eof())  break;
        }
        s.fill(x,buff);
    }
    in.close();

    colony << s.string();


    if(limit > colony.population())  return 1;



/**  Write to a file.  ********************************************************/


    colony.setLastOperation("kill");
    colony.setPopulation(limit);

    t = "";
    colony >> t;


    out.open(argv[1]);
    if(!out)  {
        (message = "") << "Unable to open file: " << argv[1];
        ::llog.error(message);
        return ERROR_FAIL;
    }


    out << t.string();
    out.close();

}


/******************************************************************************/
