/********************************************************************
 * Eric Blasko
 * test2.cpp
 * 01/31/2018
 * This program test the functionality of the class String.h. It will
 * test the overload functions for that class 
 ********************************************************************/
#include <iostream>
#include "String.h"

using namespace std;

int main()
{
    String s1{"abcd"}, s2{"abe"};
    
    if (s1 == s2)
        cout << s1 << " == " << s2;
    else
        if (s1 <= s2)
            cout << s1 << " < " << s2 << endl;
        else
            cout << s1 << " > " << s2 << endl;

    s1 = move(s2);
    cout << "s1=" << s1 << " s2=" << s2 << endl;
    
    String s3 = move(s1);
    cout << "s1=" << s1 << " s3=" << s3 << endl;
}
