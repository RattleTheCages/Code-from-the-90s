/**  entity_o.cc  **************************************************************

    12.31.1999  Performance Server Library v2.000



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




                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/



#define ENTITY_MAX_MUTATIONS         2250
#define ENTITY_DEFAULT_MUTATION_RATE 1000

#include "parse_o"
#include "rand_o"
#include "name_o"
#include "entity_o"


extern rand_o rndm;
name_o name;


entity_o::entity_o()  {
    Uniqueid                = 0;
    Generation              = 100;
    MutationRate            = ENTITY_DEFAULT_MUTATION_RATE;
    NumberOfChromosomes     = 0;
    Chromosomes             = NULL;
    Score = 0;
    RunningScore = 0;
    Iteration = 0;
}


entity_o::entity_o(const char* cc)  {
    Uniqueid                = 0;
    Generation              = 100;
    MutationRate            = ENTITY_DEFAULT_MUTATION_RATE;
    NumberOfChromosomes     = 0;
    Chromosomes             = NULL;
    Score = 0;
    RunningScore = 0;
    Iteration = 0;

    *this << cc;
}

entity_o::entity_o(const entity_o& e)  {
    Uniqueid                = e.Uniqueid;
    Generation              = e.Generation;
    MutationRate            = e.MutationRate;
    NumberOfChromosomes     = e.NumberOfChromosomes;
    Chromosomes             = new chromosome_o*[NumberOfChromosomes];
    for(int x=0;x<NumberOfChromosomes;x++)
        Chromosomes[x] = new chromosome_o(*e.Chromosomes[x]);
    Score = e.Score;
    RunningScore = e.RunningScore;
    Iteration = e.Iteration;
}

entity_o::entity_o(int gen, int nc, int ng, int ui, const char* na, int mr)  {
    long int x;

    Name            = na;
    Uniqueid        = ui;
    Generation      = gen;
    MutationRate    = mr;

    if(nc > 1 && nc < ENTITY_MAX_NUMBER_OF_CHROMOSOMES)  NumberOfChromosomes = nc;
    else  NumberOfChromosomes = ENTITY_MAX_NUMBER_OF_CHROMOSOMES;

    Chromosomes = new chromosome_o*[NumberOfChromosomes];
    for(x=0;x<NumberOfChromosomes;x++)
        Chromosomes[x] = new chromosome_o;

    Score = 0;
    RunningScore = 0;
    Iteration = 0;
}

entity_o::~entity_o()  {
    delete[]  Chromosomes;
}

entity_o* entity_o::reproduce(const entity_o& male, int generation) const  {
    entity_o      f(*this);
    entity_o      m(male);
    int           pair,pick;
    entity_o*     baby;
    chromosome_o* chrr;
    chromosome_o* chrl;

    baby = new entity_o(generation,                       // Congratulations!
                        numberOfChromosomes(),
                        Chromosomes[0]->numberOfGenes(),  // Whaa, whaa, whaa
                        ::name.id(),                      // wu wu wu wu wu
                        ::name.name(),
                        male.mutationRate());

    for(pair=0;pair<numberOfChromosomes();pair=pair+2)  {
        m.crossover(f,pair,4,20,10);
        m.crossover(f,pair,4,20,10);
        f.crossover(m,pair,4,20,10);
        f.crossover(m,pair,4,20,10);
    }

    for(pair=0;pair<numberOfChromosomes();pair=pair+2)  {
        pick = rndm.i(4);
        switch(pick)  {
            case 0:
                chrr = Chromosomes[pair+1];
                break;
            case 1:
                chrr = Chromosomes[pair];
                break;
            case 2:
                chrr = f.Chromosomes[pair+1];
                break;
            case 3:
                chrr = f.Chromosomes[pair];
                break;
        }

        pick = rndm.i(4);
        switch(pick)  {
            case 0:
                chrl = male.Chromosomes[pair+1];
                break;
            case 1:
                chrl = male.Chromosomes[pair];
                break;
            case 2:
                chrl = m.Chromosomes[pair+1];
                break;
            case 3:
                chrl = m.Chromosomes[pair];
                break;
        } 
        baby->Chromosomes[pair]   = new chromosome_o(*chrl);
        baby->Chromosomes[pair+1] = new chromosome_o(*chrr);
    }

    baby->mutate();   // Aww, poor little thing...

    return  baby;
}

chromosome_o* entity_o::duplicate(int index)  {
    chromosome_o* newChromosome;
    if(index > numberOfChromosomes() || index < 0)  return NULL;
    newChromosome = new chromosome_o(*Chromosomes[index]);
    return newChromosome;
}

void entity_o::mutate()  {
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
}


void entity_o::display(string_o& s,int n) const  {
    s << Name;
    s.justifyLeft(9);
//  s << Uniqueid << ' ';
//  s.justifyLeft(14);
    s << Generation;
    s.justifyLeft(14);
    s << " left:";
    Chromosomes[0]->display(s,n);
    s << " right:";
    Chromosomes[1]->display(s,n);
}



void entity_o::iterate()  {
    Iteration++;
}

void entity_o::crossover(const entity_o& guest,
                         int             pair,
                         int             cross_max,
                         int             splice_monte,
                         int             splice_length)  {

    int           i,j;
    chromosome_o* left       = Chromosomes[pair];
    chromosome_o* right      = Chromosomes[pair+1];
    chromosome_o* guestLeft  = guest.Chromosomes[pair];
    chromosome_o* guestRight = guest.Chromosomes[pair+1];

/**  Make X's  ****************************************************************/

    int           crossoverplace_left;
    int           crossoverplace_right;
    int           crossoverplace_left_guest;
    int           crossoverplace_right_guest;
    int           rr,rl,rr_guest,rl_guest;
    chromosome_o* chromosome_left_half;
    chromosome_o* chromosome_right_half;

    crossoverplace_left        = rndm.i(left->numberOfGenes());
    crossoverplace_right       = rndm.i(right->numberOfGenes());
    crossoverplace_left_guest  = rndm.i(guestLeft->numberOfGenes());
    crossoverplace_right_guest = rndm.i(guestRight->numberOfGenes());

    rr         = rndm.i(2);
    rl         = rndm.i(2);
    rr_guest   = rndm.i(2);
    rl_guest   = rndm.i(2);

    if(rr       == 1)  left->reverse();
    if(rl       == 1)  right->reverse();
    if(rr_guest == 1)  guestLeft->reverse();
    if(rl_guest == 1)  guestRight->reverse();

    chromosome_left_half  = new chromosome_o(*left);
    chromosome_right_half = new chromosome_o(*right);

    chromosome_left_half->upcut(crossoverplace_left);
    chromosome_right_half->upcut(crossoverplace_right);
    left->cut(crossoverplace_left);
    right->cut(crossoverplace_right);

    left->append(*chromosome_right_half);
    right->append(*chromosome_left_half);

    delete chromosome_left_half;
    delete chromosome_right_half;

    chromosome_left_half  = new chromosome_o(*guestLeft);
    chromosome_right_half = new chromosome_o(*guestRight);

    chromosome_left_half->upcut(crossoverplace_left_guest);
    chromosome_right_half->upcut(crossoverplace_right_guest);
    guestLeft->cut(crossoverplace_left_guest);
    guestRight->cut(crossoverplace_right_guest);

    guestLeft->append(*chromosome_right_half);
    guestRight->append(*chromosome_left_half);

    delete chromosome_left_half;
    delete chromosome_right_half;

/**  Crossover.  **************************************************************/

    int length;
    int spot_this;
    int spot_guest;
    int splices;
    chromosome_o* chromosome_bottom;
    chromosome_o* chromosome_splice;
    chromosome_o* chromosome_bottom_guest;
    chromosome_o* chromosome_splice_guest;

    splices = rndm.i(cross_max);
    for(i=0;i<splices;i++)  {
        chromosome_bottom  = new chromosome_o(*left);
        chromosome_splice  = new chromosome_o(*left);
        chromosome_bottom_guest = new chromosome_o(*guestRight);
        chromosome_splice_guest = new chromosome_o(*guestRight);

        length     = rndm.i(splice_monte)+splice_length;
        spot_this  = rndm.i(left->numberOfGenes()-length);
        spot_guest = rndm.i(guestRight->numberOfGenes()-length);

        if(length <= left->numberOfGenes() &&
           length <= guestRight->numberOfGenes())  {
            left->cut(spot_this);
            chromosome_bottom->upcut(spot_this+length);
            chromosome_splice->splice(spot_this,length);

            guestRight->cut(spot_guest);
            chromosome_bottom_guest->upcut(spot_guest+length);
            chromosome_splice_guest->splice(spot_guest,length);

            left->append(*chromosome_splice_guest);
            left->append(*chromosome_bottom);
 
            guestRight->append(*chromosome_splice);
            guestRight->append(*chromosome_bottom_guest);

            delete chromosome_bottom;
            delete chromosome_bottom_guest;
            delete chromosome_splice;
            delete chromosome_splice_guest;
        }
    }

/**  Unmake X.  ***************************************************************/

    chromosome_left_half  = new chromosome_o(*left);
    chromosome_right_half = new chromosome_o(*right);

    chromosome_left_half->upcut(crossoverplace_left);
    chromosome_right_half->upcut(crossoverplace_right);
    left->cut(crossoverplace_left);
    right->cut(crossoverplace_right);

    left->append(*chromosome_right_half);
    right->append(*chromosome_left_half);

    delete chromosome_left_half;
    delete chromosome_right_half;

    chromosome_left_half  = new chromosome_o(*guestLeft);
    chromosome_right_half = new chromosome_o(*guestRight);

    chromosome_left_half->upcut(crossoverplace_left_guest);
    chromosome_right_half->upcut(crossoverplace_right_guest);
    guestLeft->cut(crossoverplace_left_guest);
    guestRight->cut(crossoverplace_right_guest);

    guestLeft->append(*chromosome_right_half);
    guestRight->append(*chromosome_left_half);

    delete chromosome_left_half;
    delete chromosome_right_half;

    if(rr       == 1)  right->reverse();
    if(rl       == 1)  left->reverse();
    if(rr_guest == 1)  guestRight->reverse();
    if(rl_guest == 1)  guestLeft->reverse();
}


void entity_o::operator >> (string_o& s) const  {
    long int x;
    string_o t;

    s << '\n' << ENTITY_OBJECT << ':';
    s << '\n' << ENTITY_NAME << '=' << Name;
    s << '\n' << ENTITY_UNIQUEID << '=' << Uniqueid;
    s << '\n' << ENTITY_GENERATION << '=' << Generation;
    s << '\n' << ENTITY_SCORE << '=' << Score;
    s << '\n' << ENTITY_RUNNING_SCORE << '=' << RunningScore;
    s << '\n' << ENTITY_MUTATION_RATE << '=' << MutationRate;
    s << '\n' << ENTITY_NUMBER_OF_CHROMOSOMES << '=' << NumberOfChromosomes;
    for(x=0;x<NumberOfChromosomes;x++)  {
        t = "";
        *Chromosomes[x] >> t;
        s << '\n' << ENTITY_CHROMOSOME << '[' << x << ']' << '=' << t;
    }
    s << '\n';
}

void entity_o::operator << (const char* cc)  {
    long int x;
    string_o s,t;
    parse_o parse(cc);

    (void)parse.it(ENTITY_MUTATION_RATE,MutationRate);
    (void)parse.it(ENTITY_NAME,Name);
    (void)parse.it(ENTITY_UNIQUEID,Uniqueid);
    (void)parse.it(ENTITY_GENERATION,Generation);
    (void)parse.it(ENTITY_SCORE,Score);
    (void)parse.it(ENTITY_RUNNING_SCORE,RunningScore);

    (void)parse.it(ENTITY_NUMBER_OF_CHROMOSOMES,NumberOfChromosomes);

    
    if(!Chromosomes)  {
        Chromosomes = new chromosome_o*[NumberOfChromosomes];
        for(x=0;x<NumberOfChromosomes;x++) 
            Chromosomes[x] = new chromosome_o;
    }
    else  {
        for(x=0;x<NumberOfChromosomes;x++)  {
            if(Chromosomes[x])  delete Chromosomes[x];
            Chromosomes[x] = new chromosome_o;
        }
    }


    for(x=0;x<NumberOfChromosomes;x++)  {
        s = cc;
        t = ENTITY_CHROMOSOME;
        t << '[' << x << ']';

        s.upcut(t.string());
        s.cut("\n\n\n");
        s << "\n\n\n";

        *Chromosomes[x] << s.string();
    }

}


/******************************************************************************/
