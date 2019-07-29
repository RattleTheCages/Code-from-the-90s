/**  parse.cc  *****************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman




changes log
when      who       what
4.20.99   Dan       Creation.
4.28.99   Dan       Added:    Debug.
4.2.99    Dan       Changed:  Removed log_o object usage.

*******************************************************************************/


#include "parse.h"

parse_o::parse_o(const char* ps):stree(&parsetree)  {
    if(!ps)  return;
    char            assignment  = '=';
    char            delineator  = '\n';
    int             x,y;
    string_o        token;
    string_o*       value;
    string_o        message;

    x = 0;
    while(*(ps+x) != '\0' && x < PARSE_MAX_STRING_LENGTH)  {
        if(assignment == *(ps+x))  {
            y = x;
            while(*(ps+y) != delineator && y > 0)  y--;
            token = (ps+y+1);
            token.cut(assignment);
            value = new string_o(ps+x+1);
            value->cut(delineator);

            parsetree.insert(token,value);
            x++;
        }
        x++;
    }
}

parse_o::~parse_o()  {}

void parse_o::it(const char* t, string_o& value)  {
    string_o token(t);
    const string_o* v = stree.find(&token);
    if(v)  value = v;
}

void parse_o::it(const char* t, int& value)  {
    string_o token(t);
    string_o* v = (string_o*)stree.find(&token);
    if(v)  value = v->stoi();
}

void parse_o::it(const char* t, long int& value)  {
it(t,(int&)value);//!!!!!!!!!!!!!!!!

}

void parse_o::it(const char* t, short& value)  {
    string_o token(t);
    string_o* v = (string_o*)stree.find(&token);
    if(v)  value = v->stoi();
}

void parse_o::it(const char* t, double& value)  {
    string_o token(t);
    string_o* v = (string_o*)stree.find(&token);
    if(v)  value = v->stod();
}


/******************************************************************************/
