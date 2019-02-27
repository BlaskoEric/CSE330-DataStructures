/**************************************************************************
*Eric Blasko
*bubble.cpp
*01/24/2018
*This program creates a vector of random integers of size n, which is based 
*off of users input.The vector is then sorted and printed to console 
***************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

void bubble(vector<int>&);

//Main function creates a vector of random integers, sorts it, and prints it
int main()
{
	srand(time(0));
	int n;
	cout << "Enter n: ";
	cin >> n;

	vector<int> v(n);

	for(int i = 0; i < n; i++)
	{
		v[i] = rand()% 1000000;
	}

	bubble(v);

	for(int i = 0; i < n; i++)
	{
		cout << v[i] << endl;
	}
}

//This function sorts a vector that was passed by reference
void bubble(vector<int>& v)
{
	for(int i = v.size()-1; i > 0; i--)
	{
		for(int j = 0; j < i; j++)
		{
			if (v[j] > v[j+1])
				swap(v[j], v[j+1]);
		}
	}
}
