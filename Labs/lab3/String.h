#ifndef STRING_H
#define STRING_H

/*****************************************************************************
 * Eric Blasko
 * 01/24/2018
 * string.h
 * This is the header file for class string. Includes private data member and 
 * functions that hold an array of char. 
 ****************************************************************************/

#include <iostream>

using namespace std;

class String
{
    int size;
    char *buffer;
public:
    String();                       //default constructor
    String(const String &);         //copy constructor
    String(String &&);              //move constructor
    String(const char *);
    String(char);
    ~String();                      //destructor

    int length();
    char & operator[](const int);
    String & operator=(const String &); //copy assignment
    String & operator=(String &&);      //move assingment
    String & operator+=(const String &);
    String operator-(String) const;

    friend bool operator==(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator<(const String &, const String &);

    friend ostream & operator<<(ostream &, const String &);
};

#endif
