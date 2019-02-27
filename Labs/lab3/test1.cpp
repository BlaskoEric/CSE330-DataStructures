/*************************************************************************
 * Eric Blasko
 * test1.cpp
 * 01/31/2018
 * This program test the String.h functions. If assert catchs an error it
 * will end the program. If success is printed to screen then implentation
 * of String class is functioning properly
 ************************************************************************/


#include <iostream>
#include <cassert>
#include "String.h"

using namespace std;

int main()
{
    String s1;
    assert(s1.length() == 0);
   
    String s2{"hi"};
    assert(s2.length() == 2);

    String s3{s2};
    assert(s3.length() == 2);
    assert(s3[0] == 'h');
    assert(s3[1] == 'i');

    s1 = s2;
    assert(s1 == s2);

    s3 = "bye";
    assert(s3.length() == 3);
    assert(s3[0] == 'b');
    assert(s3[1] == 'y');
    assert(s3[2] == 'e');

    s1 += "re";
    assert(s1 == "hire");

    s1 += "d";
    assert(not (s1 == "hire"));
        
    cout << "SUCCESS" << endl;

	String str1 = "abcdbcef";
	String str2 = "bc";
	String r;

	r = str1 - str2;

	cout << r;
}
