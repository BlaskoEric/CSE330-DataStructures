/****************************************************************************
 * Eric Blasko
 * select.cpp
 * 01/24/2018
 * This program creates a vector of random integers of size n, which is based
 * off of users input.The vector is then sorted and printed to console
 ***************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

void select(vector<int>&);

//Main function creates a vector of random integers, sorts it, and prints it
int main()
{
    srand(time(0));
    int n;
    cout << "enter n: ";
    cin >> n;

    vector<int> v(n);

    for(int i = 0; i < n; i++)
    {
        v[i] = rand()%1000000;
    }

    select(v);

    for(int i = 0; i < n; i++)
    {
        cout << v[i] << endl;
    } 
}

//This function sorts a vector that was passed by reference
void select(vector<int>& v)
{
    for(int i = 0; i < v.size()-1; i++)
    {
        for(int j = i+1; j < v.size(); j++)
        {
            if(v[i] > v[j])
            {
                swap(v[i], v[j]);
            }
        }
    }
}
