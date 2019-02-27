/*******************************************************************************
 * Eric Blasko
 * hw1.cpp
 * 01/29/2018
 * This program finds the kth largest number from a group of numbers in 
 * inFile.txt. Initial k numbers are read into a vector, while remaining numbers
 * are read one by one. If numbers are greater the k, they are inserted into
 * correct location, removing smallest number. Numbers less than k are ignored
 *******************************************************************************/ 

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void selectSort(vector<int>&);
void print(vector<int>&);

//Main function that opens a file and inputs its data into a vector. Data is
//sorted and the kth number is printed to console
int main()
{
    vector<int> v;
    int next;
    int k;
    ifstream inFile;
    inFile.open("inFile.txt");
   
    if(!inFile)
    {
        cerr << "inFile.txt failed to open";
        exit(1);
    }
   
    cout << "Enter k: ";
    cin >> k;
    
    while(!inFile.eof() && v.size() !=k)
    {
        inFile >> next;
        v.push_back(next);
    }
    
    print(v);

    if(k>1)
    {
        selectSort(v);
        print(v);
    }

    while(!inFile.eof())
    {
        inFile >> next;
        if(next > v[k-1])                         
        {
            for(int i = 0; i < v.size(); i++)
            {
                if(next >= v[i])
                {
                    v.insert(v.begin()+i,next);     //put in correct spot 
                    v.pop_back();                   //removed lowest number
                    break;                          //no need to continue loop
                }
            }
        }
        print(v);
    }
    
    inFile.close();

    cout << "The " << k << " largest number is " << "'" << v[k-1] << "'" << endl;
}

//This function sorts a vector in decending order
void selectSort(vector<int>& v)
{
    for(int i = 0; i < v.size(); i++)
    {
        for(int j = i+1; j < v.size(); j++)
        {
            if(v[i] < v[j])
                swap(v[i], v[j]);
        }
    }
}   

//This function prints contents of vector
void print(vector<int>& v)
{
    for(auto& x: v)
        cout << x << " ";
    cout << endl;
}
