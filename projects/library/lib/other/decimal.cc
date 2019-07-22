/**  decimal.cc  ***************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman





changes log
when       who      what
2.8.99     Dan      Creation.


*******************************************************************************/


#include "../other/decimal.h"

decimal_o::decimal_o():Whole(0),Fraction(0),Denominator(1),Negitive(0),
                       Precision(DECIMAL_DEFAULT_PRECISION)  {}

decimal_o::decimal_o(const decimal_o& d)  {
    copy(d);
}

decimal_o::~decimal_o()  {}

decimal_o& decimal_o::operator = (const decimal_o& d)  {
    copy(d);
    return *this;
}

void decimal_o::operator = (const int i)  {
    int x = i;
    Negitive    = 0;
    if(x < 0)  {
        Negitive = 1;
        x = x * -1;
    }
    Whole       = x;
    Fraction    = 0;
    Denominator = 1;
    Precision   = DECIMAL_DEFAULT_PRECISION;
}

void decimal_o::operator = (const double dd)  {
    double d(dd);
    int f,g;
    Precision   = DECIMAL_DEFAULT_PRECISION;
    Negitive = 0;
    if(d < 0)  {
        d = d * -1;
        Negitive = 1;
    }
    Whole = d;
    d = (d - Whole);
    Denominator = 1;
    for(int x=0;x<Precision;x++)  {
        d = d * 10;
        Denominator = Denominator * 10;
    }
    f = d;
    d = d - f;
    g = d * 10.0001;
    if(g >= 5)  f++;
    Fraction = f;
    if(Fraction / Denominator > 0)  {
        Fraction = Fraction - Denominator;
        Whole++;
    }
}

void decimal_o::copy(const decimal_o& d)  {
    Whole       = d.Whole;
    Fraction    = d.Fraction;
    Denominator = d.Denominator;
    Precision   = d.Precision;
    Negitive    = d.Negitive;
}

double decimal_o::Double() const  {
    double d = (double)Whole + (double)Fraction / (double)Denominator;
    if(Negitive)  d = d * -1;
    return d;
}

void decimal_o::operator >> (string_o& s) const  {
    string_o f,dd;
    if(Negitive)  s << '-';
    s << Whole;
    if(Fraction > 0)  {
        f << Fraction;
        dd << Denominator;
        if(dd.length()-1 != f.length())  {
            f.reverse();
            for(int x=0;x<dd.length()-1-f.length();x++)  f << '0';
            f.reverse();
        }
        s << '.' << f;
    }
    else  {
        s << ".00";
    }
}

void decimal_o::operator << (const char* cc)  {
    int x,f,frac;
    string_o s(cc);
    string_o t;
    char z;
    Precision = DECIMAL_DEFAULT_PRECISION;
    if(s.charat(0) == '-')  {
        s.upcut(1);
        Negitive = 1;
    }
    Whole = s.stoi();
    s.upcut('.');
    Denominator = 1;
    x = 0;
    while(x < Precision)  {
        if(!(s.charat(x) >= '0' && s.charat(x) <= '9'))  break;
        Denominator = Denominator * 10;
        x++;
    }
    t = s;
    s.cut(x);
    t.upcut(x);
    t.cut(1);
    Fraction = s.stoi();
    if(t.length() > 0)  {
      x = t.stoi();
      if(x > 4)  Fraction++;
    }
    if(Fraction / Denominator > 0)  {
        Fraction = Fraction - Denominator;
        Whole++;
    }
}

string_o& operator << (string_o& s,const decimal_o& d)  {
    string_o ss;
    d >> ss;
    s << ss;
    return s;
}


/******************************************************************************/
