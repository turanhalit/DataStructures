/*
* @author :  152120171108 Halitcan Turan
* @author :  152120181008 Yasin Binler
* @brief  :  This program converts infix to postfix and also evaluates  postfix expression
* @date   :  09/12/2020
*/

#include <string>
#include <stack>
#include <iostream>
#include <stdlib.h>

using namespace std;

///----------------------------------------------------------------------------------
/// Given an expression in infix-notation, converts it to a string in post-fix notation 
/// 
string Infix2Postfix(string &s) {

	stack <char> Stk;
	string result= "";
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == ' ') {
			continue;
		}
		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
			result += ' ';

			int pow1 = 0;
			int pow2 = 0;
			if (Stk.empty())
			{
				pow1 = 0;
			}
			else
			{
				char ch = Stk.top();
				if (ch == '*' || ch == '/') {
					pow1 = 2;
				}
				else if (ch == '+' || ch == '-') {
					pow1 = 1;
				}
			}

			if (s[i] == '*' || s[i] == '/') {
				pow2 = 2;
			}
			else if (s[i] == '+' || s[i] == '-') {
				pow2 = 1;
			}

			while (!Stk.empty() && Stk.top() != '(' && pow1 >= pow2)
			{
				result += Stk.top();
				result += ' ';
				Stk.pop();

			}
			Stk.push(s[i]);
		}
		else if (s[i] >= '0' && s[i] <= '9') {
			result += s[i];
		}
		else if (s[i] == '(') {
			Stk.push(s[i]);
		}
		else if (s[i] == ')') {
			while (!Stk.empty() && Stk.top() != '(') {
				result += ' ';
				result += Stk.top();
				Stk.pop();
			}
			Stk.pop();
		}
	}
	while (!Stk.empty()) {
		result += ' ';
		result += Stk.top();
		Stk.pop();
	}
	return result;
} // end-Infix2Postfix

///----------------------------------------------------------------------------------
/// Given a string in post-fix notation, evaluates it and returns the result
/// 
int EvaluatePostfixExpression(string& s) {

	stack <int> Stk;
	int result = 0;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ' ') {
			continue;
		}
		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
			int operand2 = Stk.top();  Stk.pop();
			int operand1 = Stk.top();  Stk.pop();

			if (s[i] == '+')
				result = (operand1 + operand2);
			else if (s[i] == '-')
				result = (operand1 - operand2);
			else if (s[i] == '*')
				result = (operand1 * operand2);
			else if (s[i] == '/')
				result = (operand1 / operand2);
			Stk.push(result);
		}
		else if (isdigit(s[i])) {
			int operand3 = 0;
			while (i < s.length() && isdigit(s[i])) {
				operand3 = (operand3 * 10) + (s[i] - '0');
				i++;
			}
			i--;
			Stk.push(operand3);
		}
	}
	return Stk.top();
} // end-EvaluatePostfixExpression