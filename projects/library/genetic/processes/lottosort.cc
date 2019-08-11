/**  lottosort.cc  *************************************************************

    12.31.1999  Performance Server Library v2.000





when        who     what
5.17.98     Dan     Creation.
6.13.98     Dan     Fixed:    Bug with scoring repeating numbers.
6.24.98     Dan     Changed:  Using a queue to hold entities now.
                    Added:    Lotto Object.
8.2.98      Dan     Added:    Using new Global Object now.
2.3.99      Dan     Changed:  Processing loops.
2.20.99     Dan     Added:    Using new running score now.
2.22.99     Dan     Changed:  NOG genes are moved into the function now.
                              New functions, will they work?
3.12.99     Dan     Changed:  Fixed bug in geneformula.



                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/

#include <fstream.h>
#include <stdlib.h>
#include "../processes/global.h"
#include "../colony/colony.h"
#include "./lotto.h"
#include "../../library/lib/other/sysinfo.h"
#include "../../library/lib/other/rand.h"
#include "../../library/lib/thread/queue.h"

#define LOTTO_RANGE     42
#define NUMBER_OF_PICKS  6
#define NOG 10

global_o global;
int debugOn[20];


unsigned short pow(unsigned short n,unsigned short e)  {
    unsigned short x = n;
    e = e % 16; 
    if(e == 0)  return 1;
    for(unsigned short i=1;i<e;i++)  x = x * n;
    return x;
}


unsigned int geneformula(char* genes,unsigned short prev,unsigned short winner,unsigned short rand)  {
    unsigned short x;
    unsigned short g[NOG];
    unsigned short pick;


    for(x=0;x<NOG;x++)  g[x] = (unsigned int)(genes[x]-'a'+1);

    switch(g[0]-1)  {
        case 0:
            pick = (rand + g[1] + g[7]) + (winner + g[2] + g[8]) + (prev + g[3] + g[9]);
            break;
        case 1:
            pick = (rand + g[1] + g[7]) + (winner + g[2] + g[8]) - (prev + g[3] + g[9]);
            break;
        case 2:
            pick = (rand + g[1] + g[7]) - (winner + g[2] + g[8]) + (prev + g[3] + g[9]);
            break;
        case 3:
            pick = (rand + g[1] + g[7]) - (winner + g[2] + g[8]) - (prev + g[3] + g[9]);
            break;

        case 4:
            pick = (rand + g[1] * g[7]) + (winner + g[2] * g[8]) + (prev + g[3] * g[9]);
            break;
        case 5:
            pick = (rand + g[1] * g[7]) + (winner + g[2] * g[8]) - (prev + g[3] * g[9]);
            break;
        case 6:
            pick = (rand + g[1] * g[7]) - (winner + g[2] * g[8]) + (prev + g[3] * g[9]);
            break;
        case 7:
            pick = (rand + g[1] * g[7]) - (winner + g[2] * g[8]) - (prev + g[3] * g[9]);
            break;

        case 8:
            pick = (rand + g[1] * g[7] + g[4]) + (winner + g[2] + g[8]) + (pow(g[3] * g[9],prev) + g[5]);
            break;
        case 9:
            pick = (rand + pow(g[1],g[7]) + g[4]) - (winner + g[2] * g[8]) + (g[3] * g[9] * pow(prev,g[5]));
            break;
        case 10:
            pick = (pow(rand,g[1] + g[4]) + g[7]) - (winner + g[2] * g[8]) + (g[3] * g[9] * pow(prev,g[5]));
            break;
        case 11:
            pick = (rand + g[1] * g[7] + g[4]) + (pow(g[8],winner) + g[2]) + (pow(g[3] + g[9],prev) + g[5]);
            break;

        case 12:
            pick = (pow(rand,g[1]) + g[7] * g[4]) + (winner + pow(g[2],g[8])) + (pow(g[3] * g[9],prev) + g[5]);
            break;

        case 13:
            switch(prev % 3)  {
                case 0:
                    pick = (rand + g[1] + g[2] + winner + g[6]);
                    break;
                case 1:
                    pick = (-1 * g[1] + rand - winner + g[6] + g[3]);
                    break;
                default:
                    pick = (-1 * g[1] + rand + g[4] + g[5] - winner + g[2] + g[3]);
                    break;
            }

        case 14:
            pick = (rand + g[1] - g[7] * g[4]) + (pow(g[8],winner + g[2]) + g[6]) + (pow(g[3],prev + g[5]) + g[9]);
            break;

        case 15:
            pick = (rand + g[1] * g[7] + g[4]) - (pow(g[8],winner+g[6]) + g[2]) + (pow(g[3] + g[9],prev) + g[5]);
            break;

        case 16:
            pick = (rand * g[1] - g[7]) - (winner - g[2] * g[8]) - (prev + g[3] * g[9]);
            break;
        case 17:
            pick = (rand - g[1] * g[7] + g[4]) + ((winner - g[2]) * g[8]) - ((prev + g[3]) * g[9]);
            break;
        case 18:
            pick = ((rand * g[4]) + g[1] * g[7]) - ((winner - g[2]) * g[8]) + (prev + g[3] - g[9]);
            break;
        case 19:
            pick = (rand + (g[1] - g[4]) * g[7]) - ((winner * g[2]) - g[8]) - (prev + g[3] + g[9]);
            break;

        case 20:
            pick = (rand + g[1] * (g[7] * g[4])) + (winner + g[2] % g[8]) + (pow(g[3] * g[9],prev) + g[5]);
            break;
        case 21:
            pick = (rand + pow(g[1],rand) + g[4]) - (winner - rand + g[2] * g[8]) + (g[3] - g[9] + pow(prev,g[5])+g[6]);
            break;
        case 22:
            pick = (rand - prev - g[1] + g[4] - g[7]) - (winner + (prev + g[2]) + g[8]);
            break;
        case 23:
            pick = (rand + g[1] * g[7] - prev + g[4]) + (pow(g[8],(winner-rand)) + g[2]) + (g[3] + g[9] - prev + g[5] * rand);
            break;

        case 24:
            pick = (rand + g[1] * (g[7] % g[4])) + (winner + g[2] + g[8]) + (pow(prev,g[3] - g[9]) + g[5]);
            break;
        case 25:
            pick = (rand + pow(g[1],rand) + g[4]) - (winner - rand + g[2] * g[8]) + (g[3] % g[9] * pow(prev,g[5]));
            break;

    }
    pick = (pick % LOTTO_RANGE) + 1;

    return pick;
}


/**  Start.  ******************************************************************/

void kf(char* x)  {
    *(x+0) = 'a';
    *(x+1) = 'b';
    *(x+2) = 'c';
}

int main(int argc, char* argv[])  {
    queue_o<entity_o> entities;
    queue_o<entity_o> entitiesHold;
    sysinfo_o         sysinfo;
    rand_o            rand;
    int               x,y,z,j;


    if(argc < 4)  {
        cout << "usage: lottosort Colony PreviousWinningLottoFile PredictionFile\n";
        return -1;
    }


/**  Read in the Lotto winning number File.  **********************************/

    int**  NumberSets;
    int*   PreviousNumbers;
    int    NumberOfPreviousWinningNumberSets = 0;

    ifstream LottoFile(argv[2]);
    if(!LottoFile)  {
        cout << "lottosort: File not found: " << argv[2] << endl;
        return -1;
    }

    while(!LottoFile.eof())  {
        for(x=0;x<NUMBER_OF_PICKS;x++)  LottoFile >> y;
        if(LottoFile.eof())  break;
        NumberOfPreviousWinningNumberSets++;
    }
    LottoFile.close();
    NumberSets = new int*[NumberOfPreviousWinningNumberSets];
    LottoFile.open(argv[2]);

    for(x=0;x<NumberOfPreviousWinningNumberSets;x++)  {
        PreviousNumbers = new int[NUMBER_OF_PICKS];
        for(y=0;y<NUMBER_OF_PICKS;y++)  LottoFile >> PreviousNumbers[y];
        NumberSets[x] = PreviousNumbers;
    }
    LottoFile.close();

    cout << "lottosort: DNAfile:`" << argv[1] << "' LottoFile:`";
    cout << argv[2] << "' PredictionFile:`" << argv[3] << "'\n";
    cout << "lottosort: Number of Previous Winning Number Sets in LottoFile: ";
    cout << NumberOfPreviousWinningNumberSets << endl;


/**  Read in file of the entities' DNA.  **************************************/

    queue_o<entity_o> entitiesSorted;
    queue_o<entity_o> entitiesGenSort;
    entity_o*         entp;
    entity_o*         entq;
    colony_o          colony;
    ifstream          in;

    in.open(argv[1]);
    if(!in)  {
        cout << "lottosort: File not found: " << argv[1] << endl;
        return -1;
    }
    in >> colony;
    while(1)  {
        entp = new entity_o;
        in >> *entp;
        if(in.eof())  break;
        entities.put(entp);
    }
    delete entp;
    in.close();
    cout << "lottosort: Entity population: " << entities.cardinality() << endl;


/**  Generate number picks.  **************************************************/

    unsigned short  staticrand;
    unsigned short  pick;
    unsigned short  predict;
    unsigned short  slot;
    unsigned short  offset;
    lotto_o*  lotto;
    char genes[NOG];


    for(j=0;j<entities.cardinality();j++)  {
        lotto = new lotto_o;
        entp  = entities.get();
        entp->setObject((void*)lotto);
        entities.put(entp);
        for(slot=0;slot<NUMBER_OF_PICKS;slot=slot+1)  {
            staticrand = rand.i(LOTTO_RANGE) + 1;
            pick = 1;
            if((*(entp->Chromosomes[slot])).numberOfGenes()/NOG/NumberOfPreviousWinningNumberSets < 1)  {
                cout << "Insuffect gene error." << endl;
                exit(-1);
            }
            for(x=0;x<NumberOfPreviousWinningNumberSets-1;x++)  {
                offset = NOG * x;
                while(offset+NOG*NumberOfPreviousWinningNumberSets <= (*(entp->Chromosomes[slot])).numberOfGenes())  {
                    for(z=0;z<NOG;z++)  genes[z] = (*(entp->Chromosomes[slot]))[offset+z]->gene();
                    pick = geneformula(genes,
                                       pick,
                                       NumberSets[x][slot],
                                       staticrand);
//cout<<entp->name()<<" rand="<<staticrand<<" pwns="<<x<<" win="<<NumberSets[x][slot];
//cout<<" pick="<<pick<<" offset="<<offset<<endl;
                    offset = offset + NOG * NumberOfPreviousWinningNumberSets;
                }
            }

            predict = pick;
            offset = NOG * NumberOfPreviousWinningNumberSets;
            while(offset+NOG*NumberOfPreviousWinningNumberSets <= (*(entp->Chromosomes[slot])).numberOfGenes())  {
                for(z=0;z<NOG;z++)  genes[z] = (*(entp->Chromosomes[slot]))[offset+z]->gene();
                predict = geneformula(genes,
                                      predict,
                                      NumberSets[x][slot],
                                      staticrand);
//cout<<entp->name()<<" rand="<<staticrand<<" pwns="<<x<<" win="<<NumberSets[x][slot];
//cout<<" predict="<<predict<<" offset="<<offset<<endl;
                offset = offset + NOG * NumberOfPreviousWinningNumberSets;
            }

            lotto->picks[slot] = pick;
            lotto->predictions[slot] = predict;
//cout<<entp->name()<<" slot="<<slot<<" pick="<<pick<<" predi="<<predict<<endl;
        }
    }


/**  Score the results.  ******************************************************/

    int picked[NUMBER_OF_PICKS];
    int pickedIndex;

    for(z=0;z<entities.cardinality();z++)  {
        entp = entities.get();
        entp->iterate();
        entities.put(entp);
        lotto = (lotto_o*)entp->object();
        entp->setScore(0);
        for(y=0;y<NUMBER_OF_PICKS;y++)  picked[y] = 0;
        pickedIndex = 0;
        for(j=0;j<NUMBER_OF_PICKS;j++)  {
            for(x=0;x<NUMBER_OF_PICKS;x++)  {
                if(NumberSets[NumberOfPreviousWinningNumberSets-1][j]
                   == lotto->picks[x])  {
                    for(y=0;y<NUMBER_OF_PICKS;y++)
                        if(picked[y] == lotto->picks[x])  break;
                    if(y == NUMBER_OF_PICKS)  {
                        entp->setScore(entp->score()+1);
                        picked[pickedIndex] = lotto->picks[x];
                        pickedIndex++;
                    }
                }
            }
//cout << lotto->picks[j] << ' ';
        }

        for(x=0;x<NUMBER_OF_PICKS;x++)
            for(y=x+1;y<NUMBER_OF_PICKS;y++)
                if(lotto->predictions[x] == lotto->predictions[y])
                    entp->setScore(entp->score()-1);

//cout << ":: " << entp->score() << "  " << z << "  ";
//cout << entp->name() << "  " << entp->uniqueid() << endl;
    }


/**  Sort the results.  *******************************************************/

    
    while(entities.cardinality() > 0)  {
        entp = entities.get();
        entitiesHold.put(entp);
    }
    while(entitiesHold.cardinality() > 0)  {
        entp = entitiesHold.get();
        entp->inRunningScore(entp->score());
        entities.put(entp);
    }


    while(entities.cardinality() > 0)  {
        entq = entities.get();
        while(entities.cardinality() > 0)  {
            entp = entities.get();
            if(entp->trscore() > entq->trscore())  {
                entitiesHold.put(entq);
                entq = entp;
            }
            else  { 
                entitiesHold.put(entp);
            }

        }
        entitiesSorted.put(entq);
        while(entitiesHold.cardinality() > 0)  {
            entp = entitiesHold.get();
            entities.put(entp);
        }
    }




/*
    for(x=NUMBER_OF_PICKS;x>=-NUMBER_OF_PICKS;x--)  {
        while(entities.cardinality() > 0)  {
            entp = entities.get();
            if(entp->score() == x)  entitiesGenSort.put(entp);
            else  entitiesHold.put(entp);
        }
        if(entitiesGenSort.cardinality() > 0)  {
            while(entitiesGenSort.cardinality() > 0)  {
                entq = entitiesGenSort.get();
                for(y=0;y<entitiesGenSort.cardinality();y++)  {
                    entp = entitiesGenSort.get();
                    if(entp->generation() < entq->generation())  {
                        entitiesGenSort.put(entq);
                        entq = entp;
                    }
                    else  entitiesGenSort.put(entp);
                }
                entitiesSorted.put(entq);
            }
        }
        while(entitiesHold.cardinality() > 0)  entities.put(entitiesHold.get());
    }
*/


/**  Write order to the colony file.  *****************************************/

    char buf[64];

    x = 0;
    ofstream out(argv[1]);
    if(!out)  {
        cout << "lottosort: Cannot open file: " << argv[1] << endl;
        return -1;
    }

    sysinfo.currentTime(buf);
    colony.setChangeDate(buf);
    colony.setLastOperation("lottosort");
    out << colony;
    while(entitiesSorted.cardinality() > 0)  {
        entp = entitiesSorted.get();
        if(x++ < 10)  {
            cout << entp->score() << ' ';
            cout << "{"<< entp->runningScore();
            cout << "/"<<entp->iteration()<<"=";
            cout << ((double)entp->runningScore())/((double)entp->iteration()) << "}";
            entp->display(cout,12);
            cout << '\n';
        }
        out << *entp;
        entities.put(entp);
    }
    out.close();


/**  Write predictions to a file.  ********************************************/


    int  sort[NUMBER_OF_PICKS];
    int  duplicate = 0;
    ofstream outp(argv[3],ios::app);
    if(!outp)  {
        cout << "lottosort: Cannot open PredicitionFile: " << argv[3] << endl;
        return -1;
    }


    outp << buf << '\n';
    outp << "' ColonyFile: `" << argv[1] << "'       Size: ";
    outp << colony.size() << "   Last generation: ";
    outp << colony.lastGeneration() << '\n';
    outp << "LottoFile:  `" << argv[2] << "' Size: ";
    outp << NumberOfPreviousWinningNumberSets;
    outp << "  Last winning number set: ";
    outp << NumberSets[NumberOfPreviousWinningNumberSets-1][0] << ' ';
    outp << NumberSets[NumberOfPreviousWinningNumberSets-1][1] << ' ';
    outp << NumberSets[NumberOfPreviousWinningNumberSets-1][2] << ' ';
    outp << NumberSets[NumberOfPreviousWinningNumberSets-1][3] << ' ';
    outp << NumberSets[NumberOfPreviousWinningNumberSets-1][4] << ' ';
    outp << NumberSets[NumberOfPreviousWinningNumberSets-1][5] << endl;
    outp << "    prediction     ||    try          score name id generation\n";

int it = 0;
    while(entities.cardinality() > 0)  {
        entp = entities.get();
        lotto = (lotto_o*)entp->object();
        duplicate = 0;
        for(x=0;x<NUMBER_OF_PICKS;x++)  sort[x] = lotto->predictions[x];
        for(x=0;x<NUMBER_OF_PICKS;x++)
            for(y=x+1;y<NUMBER_OF_PICKS;y++)  {
                if(sort[x] == sort[y])  duplicate = 1;
                if(sort[x] > sort[y])  {
                    z = sort[x];
                    sort[x] = sort[y];
                    sort[y] = z;
                }
            }
        if(duplicate == 0 && entp->iteration() > 1)  {
            for(x=0;x<NUMBER_OF_PICKS;x++)  {
                if(sort[x] < 10)  outp << "  ";
                else  outp << ' ';
                outp << sort[x];
            }
            outp << " ||";
            for(x=0;x<NUMBER_OF_PICKS;x++)  {
                if(lotto->picks[x] < 10)  outp << "  ";
                else  outp << ' ';
                outp << lotto->picks[x];
            }
            outp << " [" << entp->score() << "] {"<<entp->runningScore();
            outp << "/" << entp->iteration()<<"=";
            outp << entp->trscore() << "} " << entp->name() << " ";
            outp << entp->uniqueid() << ' ' << entp->generation() << endl;

            it++;
        }
        if(it > 39)  break;
    }

    outp << endl;
    outp.close();
}


/******************************************************************************/
