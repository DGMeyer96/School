/*****************************************************************
*Daniel Meyer
*expr.cpp
*9/25/17
*Lab 1: Infix-to-Postfix Expression Conversion
*Implement an algorithm that converts infix expressions to postfix expressions.
*CSE 330
*Fall 2017
*****************************************************************/


#include <stack>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*
Function to test precedence of each operand in the stack
to determine if operands to to be popped off or stored.
*/
int prec(char c)
{
	switch (c){
	case '(': return 0;
	case '*': 
	case '/': return 1;
	case '+':
	case '-': return 2;
	default: return 3;
	}
}

/*
Main function that implements infix to postfix expression conversion.
*/
int main()
{
    stack<char> operators;
    char next_character;

    ifstream inFile("test.txt"); //allows for more versatility vs single input
    if (!inFile) { //checks for file existence
        cout << "Error reading file" << endl;
    }
	//cin >> next_character; //single caracter style input

    //while (!cin.eof()) {
    while(inFile.get(next_character)) {

        if (next_character >= 'A' && next_character <= 'Z' || next_character >= 'a' &&
            next_character <= 'z' || next_character >= '0' && next_character <= '9') {

            cout << next_character;
        }
        else {
            if (next_character == '(') {
                operators.push(next_character);
            }
            else if (next_character == ')') {
                while (!operators.empty() && operators.top() != '(') {

                    cout << operators.top();
                    operators.pop();
                }
                if (!operators.empty()) {
                    operators.pop();
                }
                else {
                    cout << "Error" << endl;
                }
            }
            else if (next_character == '*' || next_character == '/' ||
                     next_character == '+' || next_character == '-') {

                if (operators.empty() || prec(operators.top()) < prec(next_character))
                    operators.push(next_character);
                else {
                    while (!operators.empty() && prec(operators.top()) >= prec(next_character)) {
                        
                        cout << operators.top();
                        operators.pop();
                    }
                    operators.push(next_character);
                 }
            }
            else {
                cout << "Error" << endl;
            }
        }
    }

    while (!operators.empty()) {
        cout << operators.top();
        operators.pop();
    }

    cout << endl; //Cleans up final output
    inFile.close();

    return 0;
}
