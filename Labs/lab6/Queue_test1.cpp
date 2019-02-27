/**********************************************************************
 * Eric Blasko
 * Queue_test1.cpp
 * 02/21/2018
 * This program test the functions in Queue.h. assert will verify that 
 * each function is acting as intended
 *********************************************************************/
#include <iostream>
#include <cassert>
#include "../lab3/String.h"
#include "Queue.h"
using namespace std;

//Main function that test functions of Queue.h
int main()
{
    Queue<int> s;
	s.push(5);
	s.push(6);
	cout << s.back() << endl;
	cout << s.front() << endl;

	Queue<double> v;
	v.push(1.5);
	v.push(2.3);
	v.pop();
	cout << v.back() << endl;
	cout << v.front() << endl;

	Queue<int> s1;
	assert(s1.size() == 0);
	assert(s1.empty());

	s1.push(16);
	assert(s1.size() == 1);
	assert(s1.front() == 16);
	assert(s1.back() == 16);

	s1.pop();
	assert(s1.size() == 0);

	s1.push(11);
	assert(s1.size() == 1);
	assert(s1.front() == 11);
	assert(s1.back() == 11);

	s1.push(22);
	assert(s1.size() == 2);
	assert(s1.front() == 11);
	assert(s1.back() == 22);

	s1.push(33);
	assert(s1.size() == 3);
	assert(s1.front() == 11);
	assert(s1.back() == 33);

	s1.pop();
	assert(s1.size() == 2);
	assert(s1.front() == 22);
	assert(s1.back() == 33);

	Queue<string> s2;
	s2.push("abc");
	s2.push("de");
	assert(s2.front() == "abc");
	assert(s2.back() == "de");
	s2.pop();
	assert(s2.back() == "de");

	cout << "SUCCESS\n";
}
