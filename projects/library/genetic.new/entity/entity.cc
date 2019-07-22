/**  entity.cc  ****************************************************************

    Performance Server Library v2.000    12.31.99    Daniel Huffman



    DNA Artifical Intellegence Entity Object.




when        who        what
8.24.96     Dan        Creation.
9.4.96      Dan        Removed:  NUMBER_OF_CHROMOSOMES define.
                       Changed:  All NUMBER_OF_CHROMOSOMES references to new
                                 privite data _number_of_chromosomes.
                       Added:    number_of_chromosomes().
6.22.98     Dan        Changed:  Arguments to the active constructors.
6.23.98     Dan        Added:    Doing mutations in duplicate.
7.14.98     Dan        Added:    Constructor entity_o(const entity_o&).
2.20.99     Dan        Added:    Data members RunningScore.
9.2.99      Dan        Removed:  Passing a rand_o argument.
                       Added:    Using global object.
12.24.99    Dan        Removed:  Using global object.

*******************************************************************************/



#define ENTITY_MAX_MUTATIONS         2250
#define ENTITY_DEFAULT_MUTATION_RATE 1000

#include "../../lib/parse/parse.h"
#include "../../lib/other/rand.h"
#include "../entity/entity.h"


extern rand_o rndm;


entity_o::entity_o()  {
    Uniqueid         = 0;
    Generation       = 0;
    MutationRate     = ENTITY_DEFAULT_MUTATION_RATE;
    Score            = 0;
    RunningScore     = 0;
    Iteration        = 0;
}


entity_o::entity_o(const char* cc)  {
    Uniqueid        = 0;
    Generation      = 0;
    MutationRate    = ENTITY_DEFAULT_MUTATION_RATE;
    Score           = 0;
    RunningScore    = 0;
    Iteration       = 0;

    *this << cc;
}

/*
entity_o::entity_o(const entity_o& e)  {
}
*/

entity_o::entity_o(entity_o& e)  {
    int x;
    chromosome_o* c1;
    chromosome_o* cn;

    Name            = e.Name;
    Uniqueid        = e.Uniqueid;
    Generation      = e.Generation;
    MutationRate    = e.MutationRate;
    Score           = e.Score;
    RunningScore    = e.RunningScore;
    Iteration       = e.Iteration;

    for(x=0;x<e.numberOfChromosomes();x++)  {
        c1 = e.Chromosomes.get();
        e.Chromosomes.put(c1);
        cn = new chromosome_o(*c1);
        Chromosomes.put(cn);
    }
}

entity_o::entity_o(queue_o<chromosome_o>& qc,const entity_o& e)  {
    Name            = e.Name;
    Uniqueid        = e.Uniqueid;
    Generation      = e.Generation;
    MutationRate    = e.MutationRate;
    Score           = e.Score;
    RunningScore    = e.RunningScore;
    Iteration       = e.Iteration;

    while(qc.cardinality())  Chromosomes.put(qc.get());
}

entity_o::entity_o(const char* na,int ui,int gen,int mr,int noc,int nog)  {
    Name            = na;
    Uniqueid        = ui;
    Generation      = gen;
    MutationRate    = mr;
    Score           = 0;
    RunningScore    = 0;
    Iteration       = 0;
    for(;noc>0;noc--)  Chromosomes.put(new chromosome_o(nog));
}

entity_o::~entity_o()  {}

entity_o* entity_o::reproduce(entity_o& male,int generation)  {
    int pair;
    int mbinary = rndm.i(2);
    int fbinary = rndm.i(2);

    entity_o*           baby;
    chromosome_o*       f;
    chromosome_o*       m;
    chromosome_o*       lbin;
    chromosome_o*       rbin;
    queue_o<chromosome_o> babyChromosomes;

    for(pair=0;pair<numberOfChromosomes();pair=pair+2)  {
        lbin = this->Chromosomes.get();
        rbin = this->Chromosomes.get();
        this->Chromosomes.put(lbin);
        this->Chromosomes.put(rbin);
        if(fbinary)  f = lbin;
        else  f = rbin;

        lbin = male.Chromosomes.get();
        rbin = male.Chromosomes.get();
        male.Chromosomes.put(lbin);
        male.Chromosomes.put(rbin);
        if(mbinary)  m = lbin;
        else  m = rbin;

        if(rndm.i(2))  f->reverse();
        if(rndm.i(2))  m->reverse();

        f->crossover(m);

        if(rndm.i(2))  {
            babyChromosomes.put(f);
            babyChromosomes.put(m);
        }
        else  {
            babyChromosomes.put(m);
            babyChromosomes.put(f);
        }
    }


    baby = new entity_o(babyChromosomes,male);
    baby->mutate();

    return baby;
}

void entity_o::mutate()  {
/*
    int           max;
    char          gene;
    chromosome_o* pick;
    int           pick1;
    int           pick2;

    if(MutationRate != 0)  {
        max = 0;
        while(rndm.i(MutationRate) == 0 && max++ < ENTITY_MAX_MUTATIONS)  {
            pick = Chromosomes[rndm.i(numberOfChromosomes())];
            switch(rndm.i(3))  {
                case 1:     // Random gene change.
                    pick->setGene(rndm.i(pick->numberOfGenes()),(char)rndm.i(26)+97);
                    break;

                default:    // Transpose neighbors.
                    pick1 = rndm.i(pick->numberOfGenes()-2)+1;
                    pick2 = rndm.i(2);
                    if(pick2 == 0)  pick2 = -1;
                    gene = (*pick)[pick1];
                    pick->setGene(pick1,(*pick)[pick1+pick2]);
                    pick->setGene(pick1+pick2,gene);
                    break;
            }
        }
    }
*/
}


void entity_o::display(string_o& s,int n) const  {
    s << Name;
    s << ' ';
    s << Uniqueid << ' ';
    s << Generation << " left:";
//  Chromosomes[0]->display(s,n);
    s << " right:";
//  Chromosomes[1]->display(s,n);
}

void entity_o::iterate()  {
    Iteration++;
}

void entity_o::operator >> (string_o& s)  {
    int x;
    string_o t;
    chromosome_o* c1;

    s << '\n' << ENTITY_OBJECT << ':';
    s << '\n' << ENTITY_NAME << '=' << Name;
    s << '\n' << ENTITY_UNIQUEID << '=' << Uniqueid;
    s << '\n' << ENTITY_GENERATION << '=' << Generation;
    s << '\n' << ENTITY_MUTATION_RATE << '=' << MutationRate;
    s << '\n' << ENTITY_SCORE << '=' << Score;
    s << '\n' << ENTITY_RUNNING_SCORE << '=' << RunningScore;
    s << '\n' << ENTITY_NUMBER_OF_CHROMOSOMES << '=' << numberOfChromosomes();
    for(x=0;x<numberOfChromosomes();x++)  {
        c1 = Chromosomes.get();
        Chromosomes.put(c1);
        t = "";
        *c1 >> t;
        s << '\n' << ENTITY_CHROMOSOME << '[' << x << ']' << '=' << t;
    }
    s << '\n';
}

void entity_o::operator << (const char* cc)  {
    int x;
    int numberOfChromosomes;
    string_o s,t;
    parse_o parse(cc);
    chromosome_o* c1;

    (void)parse.it(ENTITY_NAME,Name);
    (void)parse.it(ENTITY_UNIQUEID,Uniqueid);
    (void)parse.it(ENTITY_GENERATION,Generation);
    (void)parse.it(ENTITY_MUTATION_RATE,MutationRate);
    (void)parse.it(ENTITY_SCORE,Score);
    (void)parse.it(ENTITY_RUNNING_SCORE,RunningScore);
    (void)parse.it(ENTITY_NUMBER_OF_CHROMOSOMES,numberOfChromosomes);

    for(x=0;x<numberOfChromosomes;x++)  {
        s = cc;
        t = ENTITY_CHROMOSOME;
        t << '[' << x << ']';

        s.upcut(t.string());
        s.cut("\n\n\n");
        s << "\n\n\n";

        c1 = new chromosome_o;
        *c1 << s.string();
        Chromosomes.put(c1);
    }

}


/******************************************************************************/
