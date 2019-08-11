/**  traits_o.cc  *************************************************************

    08.08.2019  Performance Server Library v2.000          (The Lost Episodes.)


    Traits interface.


    DNA Artifical Intellegence Traits Object.



                           Copyright 2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#include "traits_o.h"


traits_o::traits_o()  {}

traits_o::traits_o(const traits_o& t)  {}

traits_o::~traits_o()  {}

traits_o& traits_o::operator = (const traits_o& t)  {
    return  *this;
}

//int trait_o::operator [](int t)  const  {

int traits_o::trait(int g,  entity_o& e)  {
    int r = 0;
    int x;

    for(x = 0; x < e.chromosomes()[g]->numberOfGenes(); x++)  {

        //worddleft = ((int) ((*(colony.Entities[i]->Chromosomes[pair]))[k]) - 97 + worddleft) % 26;

        r += (((int) (*e.chromosomes()[g])[x]) - 97 + r) % 26;
    }

    return  r % 26;


/*
    int f,i,b,p,r,x,y,z;
    f = i = b = p = 0;
    int* mat = new int[e.numberOfChromosomes()];
    for(x = 0; x < e.numberOfChromosomes(); x++)  mat[x] = 0;

    y = 0;
    f = 1;
    for(z=0; z<e.Chromosomes[0]->numberOfGenes()/20; z++)  {
        f += i + b;
        i = b;
        b = f;
        for(x = 0; x < e.numberOfChromosomes(); x++)  {
            mat[x] = (mat[x] + (((*e.Chromosomes[x])[(f + g) % e.Chromosomes[0]->numberOfGenes()]) - 97)) % 24;
        }
        y++;
    }

    r = 0;
    for(x = 0; x < e.numberOfChromosomes(); x++)  {
        r = r + mat[x];
        r = r % 24;
    }


    delete  mat;
    return  r;
*/
}


/******************************************************************************/
