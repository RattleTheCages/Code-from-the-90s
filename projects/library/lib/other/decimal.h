/**  decimal.h  ****************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman



    Decimal Object.


changes log
when      who       when
5.9.99    Dan       Creation.

*******************************************************************************/


#ifndef DECIMALOBJECT_API
#define DECIMALOBJECT_API

#define DECIMAL_DEFAULT_PRECISION   2

#include "../string/string.h"


class decimal_o  {
  private:
    unsigned short       Whole;
    unsigned short       Fraction;
    unsigned short       Denominator;
    unsigned short       Precision;
    unsigned short       Negitive;

  public:
    decimal_o();                                    // Default constructor.
    decimal_o(const decimal_o&);                    // Copy constructor.
   ~decimal_o();                                    // Default destructor.
    decimal_o& operator = (const decimal_o&);       // Assignment operator.
    void       operator >> (string_o&) const;       // Object Grammer.
    void       operator << (const char*);           // Parse Object Grammer.

    void       operator = (const int);
    void       operator = (const double);
    void       copy(const decimal_o&);

    int    whole()       const;
    int    fraction()    const;
    int    denominator() const;
    int    precision()   const;
    double Double()      const;

};
string_o& operator << (string_o&,const decimal_o&);


/******************************************************************************/


inline int decimal_o::whole() const  {
    return Whole;
}

inline int decimal_o::fraction() const  {
    return Fraction;
}

inline int decimal_o::precision() const  {
    return Precision;
}

inline int decimal_o::denominator() const  {
    return Denominator;
}



#endif

/******************************************************************************/
