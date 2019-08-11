/**  spellsort.cc  *************************************************************

    12.31.1999  Performance Server Library v2.000





when        who        what
8.24.96     Dan        Creation.
8.2.98      Dan        Added:    Using new Global Object now.




                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/

#include <iostream>
using namespace std;
#include <stdlib.h>
//#include "../processes/global.h"
#include "colony_o"
#include "rand_o"
#include "traits_o"

#define SPELLSORT_BUFF_SIZE 8096

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

    entity_o  temp;
    int      population;


    colony.load(argv[1]);

population = colony.population();

for(x=0;x<colony.population();x++)  {
string = "";
(colony.entities()[x])->display(string,20);
cout << string.string() << endl;
}

    cout << "spellsort: population: " << population << endl;


/**  **************************************************************************/ 

    int  score[4096];
    char wordtry[4096][SPELLSORT_DEFAULT_NUMBER_OF_CHROMOSOMES+1];
    char wordplc[4096][SPELLSORT_DEFAULT_NUMBER_OF_CHROMOSOMES+1];
    int  worddleft;
    int  worddright;
    int  pair;
    for(i=0;i<population;i++)  {
        wordtry[i][SPELLSORT_DEFAULT_NUMBER_OF_CHROMOSOMES] = '\0';
        wordplc[i][SPELLSORT_DEFAULT_NUMBER_OF_CHROMOSOMES] = '\0';
    }

/*
    for(i=0;i<population;i++)  {
        for(pair=0;pair<SPELLSORT_DEFAULT_NUMBER_OF_CHROMOSOMES;pair=pair+2)  {
            worddleft   = 0;
            worddright  = 0;
            for(k=0;k<colony.entities()[i]->chromosomes()[pair]->numberOfGenes();k++)  {
                worddleft = ((int)
((*(colony.entities()[i]->chromosomes()[pair]))[k]) - 97 + worddleft) % 26;
                worddright = ((int)
((*(colony.entities()[i]->chromosomes()[pair+1]))[k]) - 97 + worddright) % 26;
            }
            wordtry[i][pair] = (char)(worddleft+97);
            wordplc[i][pair] = (char)(worddleft+97);
            wordtry[i][pair+1] = (char)(worddright+97);
            wordplc[i][pair+1] = (char)(worddright+97);
        }
    }
*/

    traits_o traits;

    for(i=0;i<population;i++)  {

            wordtry[i][0] =  traits.trait(0, *colony.entities()[i]) + 97;
            wordtry[i][1] =  traits.trait(1, *colony.entities()[i]) + 97;
            wordtry[i][2] =  traits.trait(2, *colony.entities()[i]) + 97;
            wordtry[i][3] =  traits.trait(3, *colony.entities()[i]) + 97;
            wordtry[i][4] =  traits.trait(4, *colony.entities()[i]) + 97;
            wordtry[i][5] =  traits.trait(5, *colony.entities()[i]) + 97;

            wordplc[i][0] =  traits.trait(0, *colony.entities()[i]) + 97;
            wordplc[i][1] =  traits.trait(1, *colony.entities()[i]) + 97;
            wordplc[i][2] =  traits.trait(2, *colony.entities()[i]) + 97;
            wordplc[i][3] =  traits.trait(3, *colony.entities()[i]) + 97;
            wordplc[i][4] =  traits.trait(4, *colony.entities()[i]) + 97;
            wordplc[i][5] =  traits.trait(5, *colony.entities()[i]) + 97;
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
                tempentity = colony.entities()[j];
                colony.entities()[j] = colony.entities()[i];
                colony.entities()[i] = tempentity;
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
colony.entities()[i]->display(string,14);
cout<<string.string();
cout<<endl;

}


/**  Write order to a file.  **************************************************/


    colony.unload(argv[1]);

}


/******************************************************************************/
