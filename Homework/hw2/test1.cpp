/*****************************************************************************************
 * Eric Blasko
 * test1.cpp
 * 02/12/2018
 * This program takes an array and randomly fills it with random numbers. The rand() 
 * function is used to generate the random numbers. If numbers have been used already
 * in array, a new number that has not been used is generated until array is full
 ****************************************************************************************/

#include <iostream>

using namespace std;

//Main function that uses a while loop to insert the random numbers, with a for loop
//the checks if the numbers been used before
int main()
{
    int n = 0;
    int i = 0 ;
    int temp = 0;
    bool found = false; 

    srand(time(0));    

    cout << "Enter size: ";
    cin >> n;
    
    int *arr = new int[n];
   
    while(i < n)
    {
        temp = rand()%n;
        found = false;
        for(int j = 0; j < i; j++)
        {
            if(arr[j] == temp)
            {
                found = true;
                break;
            }
        }
        if(found == false)
        {
            arr[i] = temp;
            i++;
        }
    } 
 
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    delete [] arr;
}
