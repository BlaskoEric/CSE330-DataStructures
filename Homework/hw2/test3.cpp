/***************************************************************************************
 * Eric Blasko
 * test3.cpp
 * 02/12/2018
 * This program fills and array with non repeating number, then randomly swapped to 
 * create a random array of numbers of size N.
 **************************************************************************************/

#include <iostream>

using namespace std;

//Main function which fills an array of size N, then randomly swaps numbers around
int main()
{
    int n;

    srand(time(0));

    cout << "Enter size: ";
    cin >> n;
    
    int *arr = new int[n];

    for(int i = 0; i < n; i++)
        arr[i] = i;

    for(int i = 0; i < n; i++)
        swap(arr[i], arr[rand()%n]);

    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    delete [] arr;
}   
