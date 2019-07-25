/**  string.h  *****************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman



    Performance String Object.


    This String Object is optimized for small memory use.




changes log
when      who      what
4.28.99   Dan      Creation.
8.31.99   Dan      Added:    Some manipulation methods.
12.25.99  Dan      Added:    Method setCharat(), and Treat as Lower Case state.
                   Removed:  Methods using iostream.h.


*******************************************************************************/


#ifndef STRINGOBJECT_API
#define STRINGOBJECT_API


#define STRINGOBJECT_MAX_LENGTH                 1048576

#define STRINGOBJECT_STATE_VOID                       0
#define STRINGOBJECT_STATE_NORMAL                     2
#define STRINGOBJECT_STATE_TREAT_AS_LOWER_CASE       16
#define STRINGOBJECT_STATE_DATA                      32


class string_o  {

  private:
    char*       Stuff;
    long int    Length;
    short int   State;


  public:
    string_o();                                         // Default constructor.
    string_o(const char);
    string_o(const char*);
    string_o(const string_o&);                          // Copy constructor.
    string_o(const string_o*);
    virtual  ~string_o();                               // Default destuctor.
    string_o& operator = (const string_o&);             // Assignment operator.
    string_o& operator = (const char);
    string_o& operator = (const char*);

    string_o& operator << (const char);
    string_o& operator << (const char*);
    string_o& operator << (const string_o&);
    string_o& operator << (const string_o*);
    string_o& operator << (int);
    string_o& operator << (unsigned int);
    string_o& operator << (long);
    string_o& operator << (unsigned long);
    string_o& operator << (double);

    int operator == (const string_o&)  const;
    int operator == (const char*)      const;
    int operator  > (const string_o&)  const;
    int operator  < (const string_o&)  const;
                                        // If State is set to Treat as Lower
                                        // Case, all uppercase chars in this
                                        // string as will as the given string
                                        // will be consitered as lowercase
                                        // chars in the lexigraphical
                                        // compairison.



    long int     length()        const; // Returns the length of the contents.
    const char*  string()        const; // Returns the string as a const char*.
    int          state()         const; // Returns the current state.


    char         charat(long int)const;
    char         charat(int)     const; // Returns the char at the index int.
                                        // If state is set to Treat as Lower
                                        // Case, uppercase chars are returned
                                        // as lower case.
    void         utos(unsigned long);   // Converts unsigned to (this) string.
    void         itos(int);             // Converts given int to (this) string.
    void         ltos(long);            // Converts given long to (this) string.
    void         dtos(double);          // Converts a positive double to this.
                                        // Only converts 6 significant digits.
    int          stoi()          const; // Converts first encountered contiguous
    long int     stol()          const; // string of numbers to an int and
                                        // returns it, returns zero if no digits
                                        // are found.
    double       stod()          const; // Returns the first found number,
                                        // double or int as a double.

    int          contains(const char*) const;
                                        // Returns the index of the first
                                        // occurrence of the given string, zero
                                        // otherwise.  If State is set to Treat
                                        // as Lower Case, all uppercase chars
                                        // in this string as will as the given
                                        // string will be consitered as
                                        // lowercase chars in the lexigraphical
                                        // search.
    int          isdigit() const;       // Returns the digit if first char is a
                                        // digit, otherwise returns negetive
                                        // one.
    int          cut(int);              // Starting at the given index, remove
    long int     cut(long int);         // the remainer of the string making the
                                        // string as long as the given int.
                                        // Return the number of chars cut off.
    int          cut(const char);       // Remove the part of the string after
    int          cut(const char*);      // and including the first encountered
                                        // given char.  Return the number of
                                        // chars removed.
    int          upcut(const char);     // Starting at index 0 remove chars
    int          upcut(const char*);    // until the given char is encountered.
                                        // The encountered given char is
                                        // removed.  Return the number of chars
                                        // removed.
                                        // If State is set to Treat as Lower
                                        // Case, all uppercase chars in this
                                        // string as will as the given string
                                        // will be consitered as lowercase
                                        // chars in these lexigraphical
                                        // search and manipulate methods.
    int          upcut(int);            // Starting at index 0 remove chars
    long int     upcut(long int);       // until counting up to the given.
                                        // Return the number of chars removed.
    int          justifyLeft(int);      // Left justifies the string adding up
    int          justifyRight(int);     // Left justifies the string adding up
    int          trim();
                                        // given int number of spaces.  Returns
                                        // the number of spaces added.
    int          boxears();             // Removes the preceding and trialing
                                        // spaces in the string.  Returns the
                                        // number of spaces removed.
    void         reverse();             // Reverses the contents.
    int          transpose(const char*, const char*);
                                        // Change all ordered sets of
                                        // characters given by the first char*
                                        // to the ordered set of characters
                                        // given by the second char*.  Return
                                        // the number of sets transposed.
    int          setCharat(int, char);
    long int     setCharat(long int, char);
                                        // Set the char at index to given.
    int          setState(int);         // Set the state.

    int          fill(long int, const char*);
                                        // Fill the string with data.



  private:
  static char  digitize(unsigned long); // Converts a single digit to a char.
  static char  tolower(char);           // Converts a char to lower case.
    void       pdtos(double);           // Converts a positive double to this.


};


/******************************************************************************/

inline long int string_o::length() const  {
    return  Length;
}

inline const char* string_o::string() const  {
    return  Stuff;
}

inline int string_o::state() const  {
    return  (int)State;
}


#endif

/******************************************************************************/
