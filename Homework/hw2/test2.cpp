/***************************************************************************************
 * Eric Blasko
 * test2.cpp
 * 02/12/2018
 * This program takes an array and fills it with random numbers based on size of array.
 * A second array is used to check if the generated number has been used, if so, a new
 * number is generated. The process if filled until array is full
 ***************************************************************************************/

#include <iostream>

using namespace std;

//Main function that loops till array is filled with random numbers. Second array is
//of boolean type which becomes true after that number has been used
int main()
{
    int n = 0;
    int i = 0;
    int temp = 0;

    srand(time(0));

    cout << "Enter size: ";
    cin >> n;
    
    int *arr = new int[n];
    bool *used = new bool[n]{false};
   
    while(i < n)
    {
        temp = rand()%n;
        if(used[temp] == false)
        {
            arr[i] = temp;
            used[temp] = true;
            i++;
        }
    }

    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    delete [] arr;
    delete [] used;
}            
