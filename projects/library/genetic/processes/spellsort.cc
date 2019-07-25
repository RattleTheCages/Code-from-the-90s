/**  spellsort.cc  *************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman





when        who        what
8.24.96     Dan        Creation.
8.2.98      Dan        Added:    Using new Global Object now.

*******************************************************************************/

#include <fstream>
#include <iostream>
using namespace std;
#include <stdlib.h>
//#include "../processes/global.h"
#include "../entity/colony.h"
#include "../../lib/other/rand.h"

#define SPELLSORT_BUFF_SIZE 4096

#define SPELLSORT_DEFAULT_NUMBER_OF_CHROMOSOMES 6

rand_o rndm;

int main(int argc, char* argv[])  {
    char     datebuff[256];
    char     buff[SPELLSORT_BUFF_SIZE];
    string_o string;
    colony_o colony;
    int  wordlength = 0;
    while(*(argv[2]+wordlength) != '\0')  wordlength++;

    if(!wordlength)  {
        cout << "usage: spellsort colony word\n";
        return -1;
    }

    if(wordlength != SPELLSORT_DEFAULT_NUMBER_OF_CHROMOSOMES)  {
        cout << "spellsort: Please use a " << SPELLSORT_DEFAULT_NUMBER_OF_CHROMOSOMES;
        cout << " letter word.\n";
        return -1;
    }

    cout << "spellsort: colony `" << argv[1] << "'  word `" << argv[2] << "'  length: " << wordlength << endl;

    entity_o*  ent;
    entity_o** entities;
    int       i,j,k,x;

/**  Read in file of the entities' DNA.  **************************************/

    ifstream in;
    entity_o  temp;
    int      population;

    in.open(argv[1]);
    if(!in)  {
        cout << "spellsort: File not found: " << argv[1] << endl;
        return -1;
    }

    while(!in.eof())  {
        for(x=0;x<SPELLSORT_BUFF_SIZE;x++)  {
            in.get(buff[x]);
            if(in.eof())  break;
        }
        string.fill(x,buff);
    }
    in.close();

    colony << string.string();
population = colony.population();

for(x=0;x<colony.population();x++)  {
string = "";
(colony.Entities[x])->display(string,20);
cout << string.string() << endl;
}

    cout << "spellsort: population: " << population << endl;


/**  **************************************************************************/ 

    int  score[4096];
    char wordtry[2096][SPELLSORT_DEFAULT_NUMBER_OF_CHROMOSOMES+1];
    char wordplc[4096][SPELLSORT_DEFAULT_NUMBER_OF_CHROMOSOMES+1];
    int  worddleft;
    int  worddright;
    int  pair;
    for(i=0;i<population;i++)  {
        wordtry[i][SPELLSORT_DEFAULT_NUMBER_OF_CHROMOSOMES] = '\0';
        wordplc[i][SPELLSORT_DEFAULT_NUMBER_OF_CHROMOSOMES] = '\0';
    }

    for(i=0;i<population;i++)  {
        for(pair=0;pair<SPELLSORT_DEFAULT_NUMBER_OF_CHROMOSOMES;pair=pair+2)  {
            worddleft   = 0;
            worddright  = 0;
            for(k=0;k<colony.Entities[i]->Chromosomes[pair]->numberOfGenes();k++)  {
                worddleft = ((int)
((*(colony.Entities[i]->Chromosomes[pair]))[k]) - 97 + worddleft) % 26;
                worddright = ((int)
((*(colony.Entities[i]->Chromosomes[pair+1]))[k]) - 97 + worddright) % 26;
            }
            wordtry[i][pair] = (char)(worddleft+97);
            wordplc[i][pair] = (char)(worddleft+97);
            wordtry[i][pair+1] = (char)(worddright+97);
            wordplc[i][pair+1] = (char)(worddright+97);
        }
    }

    for(i=0;i<population;i++)  {
        score[i] = 0;
        for(j=0;j<SPELLSORT_DEFAULT_NUMBER_OF_CHROMOSOMES;j++)
            if(*(argv[2]+j) == wordtry[i][j])  score[i]++;
//cout << i << "  " << score[i] << "  " << entities[i]->name << "  " << entities[i]->uniqueid << "  " <<  wordtry[i] << "  " << endl;
    }

    int      tempscore;
    entity_o* tempentity;

    for(i=0;i<population;i++)  {
        for(j=i;j<population;j++)  {
            if(score[j] > score[i])  {
                tempscore = score[j];
                score[j] = score[i];
                score[i] = tempscore;
                for(k=0;k<SPELLSORT_DEFAULT_NUMBER_OF_CHROMOSOMES+1;k++)  wordplc[i][k] = wordtry[j][k];
                for(k=0;k<SPELLSORT_DEFAULT_NUMBER_OF_CHROMOSOMES+1;k++)  wordplc[j][k] = wordtry[i][k];
                tempentity = colony.Entities[j];
                colony.Entities[j] = colony.Entities[i];
                colony.Entities[i] = tempentity;
            }
        }
    }
cout<<endl;
int rr;
if(20<population)  rr =20;
else rr = population;
for(i=rr-1;i>=0;i--)  {
cout << score[i] << " " << wordplc[i] << " ";
string = "";
colony.Entities[i]->display(string,14);
cout<<string.string();
cout<<endl;

}


/**  Write order to a file.  **************************************************/

    ofstream out(argv[1]);

    colony.setLastOperation("spellsort");
    string = "";
    colony >> string;
    out << string.string();
    out.close();
}


/******************************************************************************/
