/*********************************************************************************
 * Eric Blasko
 * 01/24/2018
 * String.cpp
 * This class holds the implementation of constructors and member functions
 * defined in String.h
 *********************************************************************************/

#include <cassert>
#include "String.h"

//default constructor
String::String()
{
    size = 0;
    buffer = nullptr;
}

//copy constructor
String::String(const String & source)
{
    size = source.size;
    buffer = new char[size];
    assert(buffer != nullptr);

    for(int i = 0; i < size; i++)
        buffer[i] = source.buffer[i];
}

//move constructor
String::String(String && source): size{source.size}, buffer{source.buffer}
{
    source.size = 0;
    source.buffer = nullptr;
}

//constructor from "char string" to String
//find size of p, allocate space, assign p to buffer
String::String(const char *p)
{
    size = 0;
    for(const char *q = p; *q; q++)
        size++;
    buffer = new char[size];
    assert(buffer != nullptr);
    
    for(int i = 0; i < size; i++)
        buffer[i] = p[i];
}

String::~String()
{
    delete [] buffer;
}

//copy assignment
//similar to char string constructor, buut here
//create a temp buffer based on source, 
//delete existing buffer, then assign temp buffer to buffer
String & String::operator=(const String & source)
{
    char *temp = new char[source.size];
    assert(temp != nullptr);
    
    for(int i = 0; i < source.size; i++)
        temp[i] = source.buffer[i];

    delete [] buffer;
    buffer = temp;
    size = source.size;

    return *this;
}

//move assignment
String & String::operator=(String && source)
{
    size = source.size;
    source.size = 0;
    delete [] buffer;
    buffer = source.buffer;
    source.buffer = nullptr;
    return *this;
}

bool operator==(const String & left, const String &right)
{
    if(left.size != right.size)
        return false;

    for(int i = 0; i < left.size; i++)
        if(left.buffer[i] != right.buffer[i])
            return false;
    return true;
}

ostream & operator<<(ostream & out, const String & s)
{
    for(int i = 0; i < s.size; i++)
        out << s.buffer[i];
    return out;
}

char & String::operator[](const int pos)
{
    return buffer[pos];
}

String::String(char p)
{
    size = 1;
    buffer = new char(size);
    buffer[0] = p;
}

int String::length()
{
    return size;
}

//calls two other bool functions in this class
//operator== and operator<, if ether are true
//then statement is true
bool operator<=(const String & left, const String & right)
{
     if(left < right || left == right)
	return true;
     return false;
}

//create a temp buffer the size of current string
//and source. loop twice to copy both strings to
//one string. delete old buffer and assign temp to buffer
String & String::operator+=(const String & source)
{
    int tempSize = size + source.size;
    char *temp = new char[tempSize];
    assert(temp != nullptr);

    for(int i = 0; i < size; i++)
        temp[i] = buffer[i];

    for(int i = 0; i < tempSize; i++)
        temp[size + i] = source.buffer[i];

    delete [] buffer;
    buffer = temp;
    size += source.size;
    
    return *this;
}

//check if each array char is equal to eachother.
//return boolean when difference is found
bool operator<(const String & left, const String & right)
{   
    int n = 0;
     
    while(left.buffer[n] == right.buffer[n])
        n++;
    
    if(left.buffer[n] < right.buffer[n])
        return true;
    else
        return false;
}

String String::operator-(String second) const
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (buffer[i] == second[0])
		{
			count++;
		}
	}
	int newsize = size - count*second.size;
	char *temp = new char[newsize];
	
	int j = 0;
	int i = 0;
	while (j < newsize)
	{
		bool found = false;
		if (buffer[i] == second[0])
		{
			found = true;
			i += second.size;
		}
		if (found == false)
		{
			temp[j] = buffer[i];
			j++;
			i++;
		}
	}
	return temp;
}


