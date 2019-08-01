/**  init.cc  ******************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman






when        who        what
9.24.96     Dan        Creation.
6.14.98     Dan        Changed:  Using updated objects.
6.22.98     Dan        Changed:  The rand_o object is in lib directory now.
                       Added:    Cheking passed in arguments and usage.
6.27.98     Dan        Added:    Using new colony object now.
8.2.98      Dan        Added:    Using new Global Object now.
8.9.98      Dan        Added:    Command line option for mutation rate.

*******************************************************************************/


#include <stdlib.h>
#include <fstream>
#include <iostream>
using namespace std;

#include "log_o.h"
#include "rand_o.h"
#include "colony_o.h"
#include "name_o.h"


#define INIT_DEFAULT_NUMBER_OF_ENTITIES     200
#define INIT_DEFAULT_NUMBER_OF_CHROMOSOMES    6
#define INIT_DEFAULT_NUMBER_OF_GENES        200
#define INIT_DEFAULT_INITAL_GENERATION      100
#define INIT_DEFAULT_MUTATION_RATE         1000



log_o  llog;
rand_o rndm;


void usage(const char* name)  {
    cout << '\n';
    cout << "Usage: " << name << " [-e integer] [-g integer] [-c integer] [-m integer] string\n";
    cout << "The options are:\n";
    cout << "-e integer  : Number of entities to create.\n";
    cout << "-g integer  : Number of genes per chromosome.\n";
    cout << "-c integer  : Number of chromosomes.\n";
    cout << "-m integer  : Mutation rate.\n";
    cout << "The manditory is:\n";
    cout << "string      : Name of the colony to be created.\n";
}


int main(int argc,char* argv[])  {
    string_o    message;
    string_o    s;
    int         x,y,z;
    char        gene;
    name_o*     name;
    int         colonyNameIndex,mutationRate;
    int         numberOfEntities,numberOfGenes,numberOfChromosomes;
    colony_o*   colony;

    entity_o*   entity;
    numberOfEntities    = INIT_DEFAULT_NUMBER_OF_ENTITIES;
    numberOfGenes       = INIT_DEFAULT_NUMBER_OF_GENES;
    numberOfChromosomes = INIT_DEFAULT_NUMBER_OF_CHROMOSOMES;
    mutationRate        = INIT_DEFAULT_MUTATION_RATE;


/**  Check passed in arguments.  **********************************************/

    if(argc < 2)  {
        usage("init");
        return -1;
    }
    x = 1;
    while(x<argc)  {
        if(*argv[x] == '-' && *(argv[x]+1) == 'e')  {
            x++;
            y = atoi(argv[x]);
            if(y > 1 && y < 65534)  numberOfEntities = y;
            else  {
                cout << "init: Unable to use '" << argv[x];
                cout << "' as the number of entites.\n";
            }
        }
        else if(*argv[x] == '-' && *(argv[x]+1) == 'g')  {
            x++;
            y = atoi(argv[x]);
            if(y > 1 && y < 65534)  numberOfGenes = y;
            else  {
                cout << "init: Unable to use '" << argv[x];
                cout << "' as the number of genes.\n";
            }
        }
        else if(*argv[x] == '-' && *(argv[x]+1) == 'c')  {
            x++;
            y = atoi(argv[x]);
            if(y > 1 && y < 65534)  numberOfChromosomes = y;
            else  {
                cout << "init: Unable to use '" << argv[x];
                cout << "' as the number of chromosomes.\n";
            }
        }
        else if(*argv[x] == '-' && *(argv[x]+1) == 'm')  {
            x++;
            y = atoi(argv[x]);
            if(y >= 0 && y < 65534)  mutationRate = y;
            else  {
                cout << "init: Unable to use '" << argv[x];
                cout << "' as the Mutation Rate.\n";
            }
        }
        else  break;
        x++;
    }
    if(x != argc-1)  {
        usage("init");
        return -1;
    }


/******************************************************************************/



    colonyNameIndex = x;

    message = "";
    message << "init: Creating colony `" << argv[colonyNameIndex] << "'.\n";
    message << "init: Creating " << numberOfEntities << " entities with ";
    message << numberOfGenes << " genes on each of thier ";
    message << numberOfChromosomes << " chromosomes.";
    ::llog << message;

    colony = new colony_o(argv[colonyNameIndex],
                          numberOfEntities,
                          "Colony",
                          INIT_DEFAULT_INITAL_GENERATION,
                          mutationRate);

    if(!colony)  {
        (message = "") << "new colony_o returned NULL.";
        ::llog.error(message);
        return -1;
    }

    for(x=0;x<numberOfEntities;x++)  {
        name = new name_o();
        entity = new entity_o(100,numberOfChromosomes,numberOfGenes,name->id(),name->name(),mutationRate);
        for(y=0;y<numberOfChromosomes;y++)  {
            for(z=0;z<numberOfGenes;z++)  {
                gene = rndm.i(26)+97;
                entity->Chromosomes[y]->setGene(z,gene);
            }
        }
        colony->Entities[x] = entity;
    }

    //global.sysinfo.currentTime(buff);
    //colony->setOriginDate(buff);


    ofstream out(argv[colonyNameIndex]);
    if(!out)  {
        cout << argv[0] << ": Can not open file: `" << argv[colonyNameIndex];
        cout << "'." << endl;
        return -1;
    }

    s = "";
    *colony >> s;
    out << s.string() << endl;

    out.close();


    return 1;
}


/******************************************************************************/
