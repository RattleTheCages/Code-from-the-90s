/**  reproduce.cc  *************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman




    DNA Artifical Intellegence Entity Reproduction Process Object.





when      who     what
9.24.96   Dan     Creation.
6.13.98   Dan     Changed:  Have all output start with `reproduce'.
6.22.98   Dan     Added:    Usage.
                  Changed:  Using a queue to hold entities now.
6.29.98   Dan     Added:    Using thread object and threads now.
7.14.98   Dan     Added:    Verbose option on the command line and in code.
8.2.98    Dan     Added:    Using the new global object.  Tracking the
                            generation through the colony object now.
12.24.99  Dan     Changed:  Using OLP, removed global object and threading.

*******************************************************************************/


#include <unistd.h>
#include <fstream.h>

#include "../../lib/thread/thread.h"
#include "../../lib/log/log.h"
#include "../../lib/other/rand.h"
#include "../processes/reproduce.h"
#include "../entity/colony.h"


#define REPRODUCE_BUFF_SIZE 4096


rand_o       rndm;
log_o        log;
reproduce_o* reproduce;

reproduce_o::reproduce_o(entity_o* e1,const entity_o& e2,int g)/*:entity_o(*e1)*/  {
    GuestEntity = &e2;
    Generation  = g;
}

reproduce_o::~reproduce_o()  {}

/*
void reproduce_o::threadloop()  {
    entity_o* baby;
    if(guestentity)  {
        baby = reproduce(*guestentity,generation);
        ::global.newentities.put(baby);
        if(::global.verbose == 1)  {
            baby->display(cout,18);
            cout << endl;
        }
    }
    ::global.mutex.broadcast("threadloop");
}
*/

void usage(const char* name)  {
    cout << '\n';
    cout << "Usage: " << name << " [-r integer] [-g integer] string\n";
    cout << "The options are:\n";
    cout << "-r integer  : Number of reproduction generation interations.\n";
    cout << "-g integer  : Starting generation number\n";
    cout << "-v integer  : Vebose mode\n";
    cout << "            : 1 - display new entities after generation.\n";
    cout << "The manditory is:\n";
    cout << "string      : Name of the colony to execute reproduction.\n";
}


int main(int argc, char* argv[])  {
    string_o          s;
    string_o          message;
    char              buffer[REPRODUCE_BUFF_SIZE];
    reproduce_o*      reproduce;
    colony_o          colony;
colony_o* colony2;
    queue_o<entity_o> entities;
    queue_o<entity_o> entitieshold;
    entity_o*         entity1;
    entity_o*         entity2;
    //entity_o          temp;
    ifstream          in;
    ofstream          out;
    int               pick;
    int               population;
    int               x,y,fileIndex,generation;
    char              datebuff[256];
string_o colonyString;
    entity_o* baby;

    int startingGeneration           =   0;
    int numberOfGenerationIterations =   1;

    ::log.registerName(argv[0]);



/**  Check passed in arguments.  **********************************************/

    if(argc < 2)  {
        usage("reproduce");
        return -1;
    }
    x = 1;
    while(x<argc)  {
        if(*argv[x] == '-' && *(argv[x]+1) == 'r')  {
            x++;
            y = atoi(argv[x]);
            if(y > 0 && y < 65534)  numberOfGenerationIterations = y;
            else  {
                (message = "") << "Unable to use '" << argv[x];
                message << "' as the number of generation interations.";
                ::log.error(message);
            }
        }
        else if(*argv[x] == '-' && *(argv[x]+1) == 'g')  {
            x++;
            y = atoi(argv[x]);
            if(y > 1 && y < 65534)  startingGeneration = y;
            else  {
                (message = "") << "Unable to use '" << argv[x];
                message << "' as the starting generation.";
                ::log.error(message);
            }
        }
        else  break;
        x++;
    }
    if(x != argc-1)  {
        usage(argv[0]);
        return -1;
    }
    fileIndex = x;

    message = "";
    message << "colony `" << argv[fileIndex];
    message << "'  iterations: " << numberOfGenerationIterations;
    ::log << message;


/**  Open colony and get colony information.  *********************************/
/**  Load colony.  ************************************************************/

    message = "";
    message << "Loading entity colony: `" << argv[fileIndex] << "'.";
    ::log << message;
   
    in.open(argv[fileIndex]);
    if(!in)  {
        (message = "") << "File not found: " << argv[fileIndex];
        ::log.error(message);
        return -1;
    }

    while(!in.eof())  {
        for(x=0;x<REPRODUCE_BUFF_SIZE;x++)  {
            in.get(buffer[x]);
            if(in.eof())  break;
        }
        colonyString.fill(x,buffer);
    }

    colony << colonyString.string();


    if(startingGeneration == 0)
        startingGeneration = colony.lastGeneration()+1;


    in.close();
    delete entity1;


    (message = "") << "Finshed loading entity colony.";
    ::log << message;


/******************************************************************************/
/**  Place entities randomly into a linked list.                             **/
/******************************************************************************/


    for(x=0;x<colony.population();x++)  {
        entitieshold.put(colony.Entities[x]);//!!! private data.
  // Make random!!
    }


    generation = colony.lastGeneration()+1;


/******************************************************************************/
/**  Iterate reproduction.                                                   **/
/******************************************************************************/

/*
    for(generation=startingGeneration;
        generation<startingGeneration+numberOfGenerationIterations;
        generation++)  {
*/

        while(entitieshold.cardinality() > 0)  entities.put(entitieshold.get());
        (message = "") << "population: " << entities.cardinality();
        message << "  generation: " << generation;
        ::log << message;


/******************************************************************************/
/**  Match up entities randomly to reproduce.                                **/
/******************************************************************************/


        population = entities.cardinality();
        if(population/2 != ((double)population)/2.0)  population--;

        x = 0;
        while(x++ < population/2)  {
            pick = rndm.i(entities.cardinality()-1);
            for(y=0;y<pick;y++)  {
                entity1 = entities.get();
                entities.put(entity1);
            }
            entity1 = entities.get();
            entitieshold.put(entity1);
            pick = rndm.i(entities.cardinality()-1);
            for(y=0;y<pick;y++)  {
                entity2 = entities.get();
                entities.put(entity2);
            }
            entity2 = entities.get();
            entitieshold.put(entity2);


/**  Start pick one reproduce thread with pick two.  **************************/

            //reproduce = new reproduce_o(entity1,*entity2,generation);

            baby = entity1->reproduce(*entity2,generation);
            entitieshold.put(baby);

        }


        while(entities.cardinality() > 0)  entitieshold.put(entities.get());
/*
        while(newentities.cardinality() > 0)
            ;//entitieshold.put(::global.newentities.get());
*/



/**  Write colony including new members.  *************************************/

    out.open(argv[fileIndex]);
    if(!out)  {
        (message = "") << "Can not open file: " << argv[fileIndex];
        ::log.error(message);
        return -1;
    }

    colony2 = new colony_o(colony.name(),
                           entitieshold.cardinality(),
                           "Colony",
                           colony.lastGeneration()+1,
                           colony.mutationRate());
    y = entitieshold.cardinality();
    for(x=0;x<y;x++)  {
        colony2->Entities[x] = entitieshold.get();
    }

    s = "";
    (*colony2) >> s;
    out << s.string();
    out.close();
}

/******************************************************************************/
