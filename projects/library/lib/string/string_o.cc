/**  string_o.cc  **************************************************************

    12.31.1999  Performance Server Library v2.000





changes log
when      who      what
4.28.99   Dan      Creation.
8.31.99   Dan      Added:    Method upcut(const char*).
9.16.99   Dan      Added:    Method cut(const char*).
12.25.99  Dan      Added:    Method setCharat(), and Treat as Lower Case state.
                   Removed:  Methods using iostream.h.



                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#include "string_o.h"

string_o::string_o()  {
    Stuff  = new char[1];
    *Stuff = '\0';
    Length = 0;
    State  = StringOBJECT_STATE_NORMAL;
}

string_o::string_o(const char c)  {
    Stuff      = new char[2];
    *Stuff     = c;
    *(Stuff+1) = '\0';
    Length     = 1;
    State      = StringOBJECT_STATE_NORMAL;
}

string_o::string_o(const char* cc)  {
    Length = 0;
    if(cc)  {
        while(Length<StringOBJECT_MAX_LENGTH && *(cc+Length) != '\0')  Length++;
        Stuff = new char[Length+1];
        for(long int x=0;x<Length;x++)  *(Stuff+x) = *(cc+x);
        *(Stuff+Length) = '\0';
    }
    else  {
        Stuff  = new char[1];
        *Stuff = '\0';
    }
    State = StringOBJECT_STATE_NORMAL;
}

string_o::string_o(const string_o* s)  {
    int long x;
    if(s)  {
        Stuff   = new char[s->length()+1];
        Length  = s->length();
        for(x=0;x<Length;x++)  *(Stuff+x) = s->charat(x);
        *(Stuff+x) = '\0';
    }
    else  {
        Stuff  = new char[1];
        *Stuff = '\0';
    }
    State = StringOBJECT_STATE_NORMAL;
}

string_o::string_o(const string_o& s)  {
    int long x;
    Stuff   = new char[s.length()+1];
    Length  = s.length();
    for(x=0;x<Length;x++)  *(Stuff+x) = s.charat(x);
    *(Stuff+x) = '\0';
    State = StringOBJECT_STATE_NORMAL;
}

string_o::~string_o()  {
    delete[] Stuff;
}

char string_o::charat(int index) const  {
    return charat((long int)index);
}

char string_o::charat(long int index) const  {
    if(index < 0 || index > Length)  return '\0';
    if(State == StringOBJECT_STATE_TREAT_AS_LOWER_CASE)  {
        return tolower(*(Stuff+index));
    }

    else  {
        return *(Stuff+index);
    }
}

string_o& string_o::operator = (const char c)  {
    delete[] Stuff;
    Stuff      = new char[2];
    *Stuff     = c;
    *(Stuff+1) = '\0';
    Length     = 1;
    State      = StringOBJECT_STATE_NORMAL;
    return *this;
}

string_o& string_o::operator = (const char* cc)  {
    delete[] Stuff;
    Length = 0;
    if(cc)  {
        while(Length<StringOBJECT_MAX_LENGTH && *(cc+Length) != '\0')  Length++;
        Stuff = new char[Length+1];
        for(long int x=0;x<Length;x++)  *(Stuff+x) = *(cc+x);
        *(Stuff+Length) = '\0';
    }
    else  {
        Stuff  = new char[1];
        *Stuff = '\0';
    }
    State = StringOBJECT_STATE_NORMAL;
    return *this;
}

string_o& string_o::operator = (const string_o& s)  {
    long int x;
    if(this == &s)  return *this;  // Assign to self?
    if(s.length() == 0)  *this = "";
    else if(s.state() == StringOBJECT_STATE_DATA)  {
        Length = 0;
        fill(s.length(),s.string());
    }

    else  {
        delete[] Stuff;
        Length = s.length();
        Stuff = new char[length()+1];
        for(x=0;x<length();x++)  *(Stuff+x) = s.charat(x);
        *(Stuff+x) = '\0';
    }
    return *this;
}

string_o& string_o::operator << (const char c)  {
    char* newStuff = new char[length()+2];
    for(long int x=0;x<Length;x++)  *(newStuff+x) = *(Stuff+x);
    delete[] Stuff;
    *(newStuff+Length) = c;
    *(newStuff+Length+1) = '\0';
    Stuff = newStuff;
    Length++;
    return *this;
}

string_o& string_o::operator << (const char* c)  {
    long int  x,l;
    char*     newStuff;
    if(c)  {
        l = 0;
        while(l<StringOBJECT_MAX_LENGTH-Length && *(c+l) != '\0')  l++;
        newStuff = new char[Length+l+1];
        for(x=0;x<Length;x++)  *(newStuff+x) = *(Stuff+x);
        delete[] Stuff;
        for(x=0;x<l;x++)  *(newStuff+x+Length) = *(c+x);
        *(newStuff+Length+l) = '\0';
        Stuff = newStuff;
        Length += l;
    }
    return *this;
}

string_o& string_o::operator << (const string_o* s)  {
    if(s)  {
        if(s->state() == StringOBJECT_STATE_DATA)  {
            fill(s->length(),s->string());
        }
        else  *this << s->string();
    }
    return  *this;
}

string_o& string_o::operator << (const string_o& s)  {
    if(s.state() == StringOBJECT_STATE_DATA)  {
        fill(s.length(),s.string());
    }

    else  {
        *this << s.string();
    }
    return *this;
}

string_o& string_o::operator << (int i)  {
    string_o s;
    s.itos(i);
    return  *this << s.string();
}

string_o& string_o::operator << (unsigned int i)  {
    string_o s;
    s.utos((long)i);
    return  *this << s.string();
}

string_o& string_o::operator << (long l)  {
    string_o s;
    s.ltos(l);
    return  *this << s.string();
}

string_o& string_o::operator << (unsigned long ul)  {
    string_o s;
    s.utos(ul);
    return  *this << s.string();
}

string_o& string_o::operator << (double d)  {
    string_o s;
    s.dtos(d);
    return  *this << s.string();
}

void string_o::reverse()  {
    char* newStuff = new char[Length+1];
    for(long int x=0;x<Length;x++)
        *(newStuff+x) = *(Stuff+(Length-x-1));
    *(newStuff+Length) = '\0';
    delete[] Stuff;
    Stuff = newStuff;
}

void string_o::utos(unsigned long u)  {
    unsigned long int U = u;
    unsigned long int V;
    if(U == 0)  *this = '0';
    else  *this = "";
    while(U > 0)  {
        V = U % 10;
        U = U / 10;
        *this << digitize(V);
    }
    reverse();
}

void string_o::pdtos(double d)  {
    int           count = 0;
    double        D = d;
    unsigned long int E;
    if(D == 0)  {
        *this = "0.0";
        return;
    }
    else  *this = "";
    D = D * 100;
    while(D >= 1)  {
        E = (unsigned long int)D % 10;
        D = D / 10;
        *this << digitize(E);
        if(count++ == 1)  *this << '.';
    }
    if(count == 1)  *this << "0.";
    if(Length < 1)  *this = "00.";
    this->reverse();
}

void string_o::itos(int i)  {
    string_o  utos;
    int       negitive = 0;
    if(i < 0)  {
        negitive = 1;
        i = i * -1;
    }
    utos.utos((unsigned long)i);
    if(negitive)  *this = "-";
    else  *this = "";
    *this = utos.string();
}

int string_o::stoi() const  {
    int ret;
    ret = 0;
    string_o s(*this);
    char negitive;
    if(length() == 0)  return 0;
    while(s.isdigit() == -1 && s.length() != 0)  {
        negitive = s.charat(0);
        s.upcut(1);
    }
    if(s.length() == 0)  return 0;
    while(s.isdigit() != -1)  {
        ret = ret * 10;
        ret = ret + s.isdigit();
        s.upcut(1);
    }
    if(negitive == '-')  ret = ret * -1;
    return ret;
}

long int string_o::stol() const  {
    long int ret;
    ret = 0;
    string_o s(*this);
    char negitive;
    if(length() == 0)  return 0;
    while(s.isdigit() == -1 && s.length() != 0)  {
        negitive = s.charat(0);
        s.upcut(1);
    }
    if(s.length() == 0)  return 0;
    while(s.isdigit() != -1)  {
        ret = ret * 10;
        ret = ret + s.isdigit();
        s.upcut(1);
    }
    if(negitive == '-')  ret = ret * -1;
    return ret;
}

double string_o::stod() const  {
    double ret;
    ret = 0;
    string_o s(*this);
    char negitive;
    if(length() == 0)  return 0;
    while(s.isdigit() == -1 && s.length() != 0)  {
        negitive = s.charat(0);
        s.upcut(1);
    }
    if(s.length() == 0)  return 0;
    while(s.isdigit() != -1)  {
        ret = ret * 10;
        ret = ret + s.isdigit();
        s.upcut(1);
    }
    if(negitive == '-')  ret = ret * -1;
    return ret;
}
    
void string_o::ltos(long l)  {
    string_o  utos;
    int       negitive = 0;
    if(l < 0)  {
        negitive = 1;
        l = l * -1;
    }
    utos.utos((unsigned long)l);
    if(negitive)  *this = "-";
    else  *this = "";
    *this = utos.string();
}

void string_o::dtos(double d)  {
    string_o  dtos;
    int       negitive = 0;
    if(d < 0)  {
        negitive = 1;
        d = d * -1;
    }
    dtos.pdtos(d);
    if(negitive)  *this = "-";
    else  *this = "";
    *this << dtos.string();
}

char string_o::digitize(unsigned long u)  {
    if(u == 1)  return '1';
    if(u == 2)  return '2';
    if(u == 3)  return '3';
    if(u == 4)  return '4';
    if(u == 5)  return '5';
    if(u == 6)  return '6';
    if(u == 7)  return '7';
    if(u == 8)  return '8';
    if(u == 9)  return '9';
    return '0';
}

int string_o::isdigit()  const  {
    if(length() == 0)  return -1;
    if(*Stuff == '1')  return 1;
    if(*Stuff == '2')  return 2;
    if(*Stuff == '3')  return 3;
    if(*Stuff == '4')  return 4;
    if(*Stuff == '5')  return 5;
    if(*Stuff == '6')  return 6;
    if(*Stuff == '7')  return 7;
    if(*Stuff == '8')  return 8;
    if(*Stuff == '9')  return 9;
    if(*Stuff == '0')  return 0;
    return -1;
}

int string_o::contains(const char* find) const  {
    if(!find)  return 0;
    long int      x,y,z,count = 0;
    string_o s;

    x = 0;
    while(x<Length && x<StringOBJECT_MAX_LENGTH)  {
        if(*find == *(Stuff+x))  {
            y = 0;
            z = x;
            while(*(find+y) != '\0' && y<StringOBJECT_MAX_LENGTH+x+y 
                  && *(find+y) == *(Stuff+z))  {
                y++;
                z++;
            }
            if(*(find+y) == '\0')  return x+y;
        }
        x++;
    }

    return 0;
}

int string_o::transpose(const char* find, const char* replace)  {
    if(!find || !replace)  return 0;
    long int      x,y,z,count = 0;
    string_o s;
    x = 0;
    while(x<Length && x<StringOBJECT_MAX_LENGTH)  {
        if(*find == *(Stuff+x))  {
            y = 0;
            z = x;
            while(*(find+y) != '\0' && y<StringOBJECT_MAX_LENGTH+x+y 
                  && *(find+y) == *(Stuff+z))  {
                y++;
                z++;
            }
            if(*(find+y) == '\0')  {
                count++;
                z = 0;
                while(*(replace+z) != '\0' && z<StringOBJECT_MAX_LENGTH+x+z)  {
                    s << *(replace+z);
                    z++;
                }
            }
            else  for(z=0;z<y;z++)  s << *(Stuff+x+z);
            x += y;
        }
        s << *(Stuff+x);
        x++;
    }
    *this = s;
    return count;
}

int string_o::operator == (const char* ccp) const  {
    string_o s(ccp);
    return  (*this == s);
}

int string_o::operator == (const string_o& s) const  {
    long int x;
    if(length() != s.length())  return 0;
    for(x=0;x<length();x++)  if(charat(x) != s.charat(x))  break;
    if(x == length())  return 1;
    return 0;
}

int string_o::operator < (const string_o& s) const  {
    long int x;
    for(x=0;x<length();x++)  if(charat(x) != s.charat(x))  break;
    if(x == length())  return 0;
    if(charat(x) < s.charat(x))  return 1;
    return 0;
}

int string_o::operator > (const string_o& s) const  {
    long int x;
    for(x=0;x<length();x++)  if(charat(x) != s.charat(x))  break;
    if(x == length())  return 0;
    if(charat(x) > s.charat(x))  return 1;
    return 0;
}

int string_o::cut(int index)  {
    return (int)cut((long int)index);
}

long int string_o::cut(long int index)  {
    long int numberOfCharsCutOff,x;
    if(index < 0 || index > length() || index > StringOBJECT_MAX_LENGTH)  return 0;
    if(index == 0)  {
        numberOfCharsCutOff = length();
        *this = "";
    }
    else  {
        char* newStuff = new char[index+1];
        for(x=0;x<index;x++)  *(newStuff+x) = charat(x);
        *(newStuff+x)       = '\0';
        delete[] Stuff;
        Stuff               = newStuff;
        numberOfCharsCutOff = Length - index;
        Length              = index;
    }
    return numberOfCharsCutOff;
}

int string_o::cut(const char c)  {
    int place = 0;
    while(*(Stuff + place) != c && place < length())  place++;
    return cut(place);
}
    
int string_o::upcut(const char c)  {
    int upto = 0;
    while(*(Stuff+upto) != c && upto < length())  upto++;
    upto++;
    return upcut(upto);
}

int string_o::upcut(int upto)  {
    return (int)upcut((long int)upto);
}

long int string_o::upcut(long int upto)  {
    long int numberRemoved,x;
    if(upto < 1)  return 0;
    if(upto >= length())  {
        numberRemoved = length();
        *this = "";
    }
    else  {
        char* newStuff     = new char[length()-upto+1];
        for(x=upto;x<length();x++)  *(newStuff+x-upto) = charat(x);
        *(newStuff+x-upto) = '\0';
        numberRemoved      = length()-upto;
        delete[] Stuff;
        Stuff              = newStuff;
        Length             = length()-upto;
    }
    return numberRemoved;
}

int string_o::upcut(const char* pat)  {
    if(!pat)  return 0;
    long int    x,y,z;
    x = 0;
    while(x<Length && x<StringOBJECT_MAX_LENGTH)  {
        if(*pat == *(Stuff+x))  {
            y = 0;
            z = x;
            while(*(pat+y) != '\0' && y<StringOBJECT_MAX_LENGTH+x+y 
                  && *(pat+y) == *(Stuff+z))  {
                y++;
                z++;
            }
            if(*(pat+y) == '\0')  {
                this->upcut(x+y);
                return (int)x+y;
            }
            x += y;
        }
        x++;
    }
    return 0;
}

int string_o::cut(const char* pat)  {
    if(!pat)  return 0;
    long int      x,y,z;
    x = 0;
    while(x<Length && x<StringOBJECT_MAX_LENGTH)  {
        if(*pat == *(Stuff+x))  {
            y = 0;
            z = x;
            while(*(pat+y) != '\0' && y<StringOBJECT_MAX_LENGTH+x+y 
                  && *(pat+y) == *(Stuff+z))  {
                y++;
                z++;
            }
            if(*(pat+y) == '\0')  {
                return  this->cut(x+y);
                return x+y;
            }
            x += y;
        }
        x++;
    }
    return 0;
}

int string_o::justifyLeft(int in)  {
    long int x;
    if(length() >= in || in < 1)  return 0;
    int howmany = in - length();
    char* newStuff = new char[length()+howmany+1];
    for(x=0;x<length();x++)  *(newStuff+x) = charat(x);
    for(x=0;x<howmany;x++)  *(newStuff+length()+x) = ' ';
    *(newStuff+length()+howmany) = '\0';
    delete[] Stuff;
    Stuff   = newStuff;
    Length  = Length+howmany;
    return howmany; 
}

int string_o::justifyRight(int in)  {
    int ii;
    reverse();
    ii = justifyLeft(in);
    reverse();
    return ii;
}

int string_o::boxears()  {  // Fix this.!!!!!
    while(charat(0) == ' ' || charat(0) == '\t')  upcut(1);
    reverse();
    while(charat(0) == ' ' || charat(0) == '\t')  upcut(1);
    reverse();
    return 0;
}

int string_o::trim()  {  //!! ineffecent!!
    long int  x = Length-1;
    while(*(Stuff+x) == ' ')  x--;
    cut(Length - (Length - x) + 1);
    x = 0;
    while(*(Stuff+x) == ' ')  x++;
    upcut(x);
    return 1;//!!
}

int string_o::setState(int s)  {
    State = (short int)s;
    return (int)State;
}


int string_o::setCharat(int i, char c)  {
    return setCharat((long int)i,c);
}

long int string_o::setCharat(long int i, char c)  {
    if(i >= 0 && i < Length)  {
        *(Stuff+i) = c;
        return 1;
    }
    return 0;
}

int string_o::fill(long int l, const char* s)  {
    long int x;
    char* newStuff;
    if(l>0)  {
        State = StringOBJECT_STATE_DATA;
        newStuff = new char[Length+l+1];
        for(x=0;x<Length;x++)  *(newStuff+x) = *(Stuff+x);
        delete[] Stuff;
        Stuff = newStuff;
        for(x=Length;x<Length+l;x++)  *(Stuff+x) = *(s+x-Length);
        *(Stuff+x) = '\0';
        Length = Length + l;
    }
    return Length;
}

char string_o::tolower(char ch)  {
    if(ch >= 'A' && ch <= 'Z')  {
        if(ch == 'A')  return 'a';
        else  if(ch == 'B')  return 'b';
        else  if(ch == 'C')  return 'c';
        else  if(ch == 'D')  return 'd';
        else  if(ch == 'E')  return 'e';
        else  if(ch == 'F')  return 'f';
        else  if(ch == 'G')  return 'g';
        else  if(ch == 'H')  return 'h';
        else  if(ch == 'I')  return 'i';
        else  if(ch == 'J')  return 'j';
        else  if(ch == 'K')  return 'k';
        else  if(ch == 'L')  return 'l';
        else  if(ch == 'M')  return 'm';
        else  if(ch == 'N')  return 'n';
        else  if(ch == 'O')  return 'o';
        else  if(ch == 'P')  return 'p';
        else  if(ch == 'Q')  return 'q';
        else  if(ch == 'R')  return 'r';
        else  if(ch == 'S')  return 's';
        else  if(ch == 'T')  return 't';
        else  if(ch == 'U')  return 'u';
        else  if(ch == 'V')  return 'v';
        else  if(ch == 'W')  return 'w';
        else  if(ch == 'X')  return 'x';
        else  if(ch == 'Y')  return 'y';
        else  return 'z';
    }
    else  {
        return ch;
    }
}


/******************************************************************************/
