/***************************************************************************************
 *Eric Blasko
 *lab1.cpp
 *01/17/2018
 *This program runs an algorithm to convert infix expressions into a postfix expression.
 *A stack is used to hold operators in order to reverse the order of the operators in 
 *the expression.
 ***************************************************************************************/

#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool IsOperator(char a);
int Precedence(char a);
void postfix(string);

//Main function to get infix expression and run algorithm to convert to postfix expression
int main()
{
    string infix = "";
    cout << "Enter Expression: ";
    getline(cin,infix);
    postfix(infix);

    return 0;
}

//This function determines if the current char is a operator and returns a boolean
bool IsOperator(char a)
{
    if(a == '+' ||
        a == '-' ||
        a == '*' ||
        a == '/' ||
        a == '(' ||
        a == ')')
        return true;
    else
        return false;
}

//This function returns a numerical value based on operators precedence scale
int Precedence(char a)
{
    if(a == '(' || a == ')')
        return 1;
    else if(a == '+' || a == '-')
        return 2;
    else if(a == '*' || a == '/')
        return 3;
    else
        {
            cerr << "Invalid input" << endl;
            return 0;
        }
}

//This function takes a infix expression and prints the converted postfix expression 
void postfix(string expression)
{
    stack<char> operators;

    while(!cin.eof())
    {  
        for(int i = 0; i < expression.size(); i++)
        {
            if(IsOperator(expression[i]) == false)
            {       
                cout << expression[i];
            }
            else
            {   
                if(expression[i] == '(')
                {   
                    operators.push(expression[i]);
                }
	            else if(expression[i] == ')')
	            {
        	        while (!operators.empty() && operators.top() != '(')
		            {
                        cout << operators.top();
                        if(!operators.empty())
                        {
            			    operators.pop();
                        }
                        else
                        {
                            cerr << "no matching (" << endl;
                        }
                    }      
                    operators.pop();
                }
                else if(IsOperator(expression[i]) == true)
                {
                    if(operators.empty() || Precedence(operators.top()) < Precedence(expression[i]))
                    {
                        operators.push(expression[i]);
                    }
                    else
                    {
                        while(!operators.empty() && Precedence(operators.top()) >= Precedence(expression[i]))
                        {
                            cout << operators.top();
                            operators.pop();
                        }
                        operators.push(expression[i]);
                    }
                }
                else
                {
                    cerr << "Invalid Input" << endl;
                }
            }
        }

        while(!operators.empty())
        {
            cout << operators.top();
            operators.pop();
        }
    
        cout << endl << "Enter Expression: ";
        getline(cin,expression);
    }
}

