/*
* @author :  152120171108 Halitcan Turan
* @author :  152120181008 Yasin Binler
* @brief  :  This program calculates polynomials using linkedLists
* @date   :  20/11/2020
*/
#include <stdio.h>
#include "Poly.h"
#include <stdlib.h>
#include <malloc.h>
#include <iostream>
#include <string.h>
#include<sstream>

using namespace std;

typedef struct PieceOfPoly {
	const char* str;
};

PolyNode* newTerm(double, int);
PolyNode* parseTerm(PieceOfPoly*);
double parse_Coefficient(PieceOfPoly*);
int parse_exponent(PieceOfPoly*);
void parse_space(PieceOfPoly*);
double parse_sign(PieceOfPoly*);
double parse_number(PieceOfPoly*);
//----------------
//-------------------------------------------------
// Creates a polynomial from an expression.
// Returns a pointer to the first PolyNode in the list (head of the list)
//
// Expression will be of the following sort:
// Ex1: 2.3x^4 + 5x^3 - 2.64x - 4
// Ex2: -4.555x^10 - 45.44
// Ex3: x^6 + 2x^4 - x^3 - 6.3x + 4.223 
// Ex4: 34
// Ex5: -x+1
// Ex6: -3x^4    +   4x
// Ex7: -2x  - 5
//

PolyNode *CreatePoly(char *expr) {
	PolyNode* poly;
	PolyNode* term;
	PieceOfPoly	context;

	poly = NULL;
	term = NULL;
	context.str = expr;

	while (*context.str) {
		if (term == NULL) {

			term = parseTerm(&context);
			poly = term;
		}
		else {
			term->next = parseTerm(&context);
			term = term->next;
		}
	}
	return poly;
} //end-CreatePoly
PolyNode* newTerm(double coeff, int expo)
{
	PolyNode* poly;

	poly = new(PolyNode);

	poly->coef = coeff;
	poly->exp = expo;
	poly->next = NULL;

	return poly;
}

PolyNode* parseTerm(PieceOfPoly* context)
{
	PolyNode* term;
	double coeff;
	int	expo;

	coeff = parse_Coefficient(context);
	expo = parse_exponent(context);
	term = newTerm(coeff, expo);

	return term;
}
double parse_Coefficient(PieceOfPoly* context)
{
	double	coeff, sign_op;

	sign_op = parse_sign(context);
	coeff = parse_number(context);

	return coeff * sign_op;
}

int parse_exponent(PieceOfPoly* context)
{
	int	expo = 0;

	parse_space(context);
	if (*context->str == 'x') {
		expo = 1;
		context->str++;

		if (*context->str == '^') {
			context->str++;
			expo = parse_number(context);
		}
	}
	return expo;
}

void parse_space(PieceOfPoly* context)
{
	while (isspace(*context->str))
		context->str++;
}
double parse_sign(PieceOfPoly* context)
{
	double sign = 1.0;

	parse_space(context);

	if (*context->str == '-') {
		sign = -1.0;
		context->str++;
	}
	else if (*context->str == '+') {
		context->str++;
	}
	return sign;
}

double parse_number(PieceOfPoly* context)
{
	double	number;
	char* last;

	number = strtod(context->str, &last);
	if (context->str == last) {
		number = 1.0;
	}
	context->str = last;

	return number;
}
/// -------------------------------------------------
/// Walk over the poly nodes & delete them
///
void DeletePoly(PolyNode* poly) {
	PolyNode* curr = new PolyNode;
	curr = poly;
	PolyNode* next = new PolyNode;

	while (curr->next != NULL)
	{
		next = curr->next;
		delete curr;
		curr = next;
	}
} // end-DeletePoly

//-------------------------------------------------
// Adds a node (coefficient, exponent) to poly. If there already 
// is a node with the same exponent, then you simply add the coefficient
// to the existing coefficient. If not, you add a new node to polynomial
// Returns a pointer to the possibly new head of the polynomial.
//
PolyNode* AddNode(PolyNode *head, double coef, int exp) {
	PolyNode* node = new PolyNode();
	node->coef = coef;
	node->exp = exp;
	node->next = NULL;

	PolyNode** p = &head;
	while (*p != NULL && exp <= (*p)->exp) {
		p = &(*p)->next;
	}
	node->next = *p;
	*p = node;

	PolyNode* first = head;
	PolyNode* second = NULL;

	while (first != NULL && first->next != NULL) {
		second = first;
		first = first->next;
		if (second->exp == first->exp) {

			second->coef = second->coef + first->coef;
			second->next = first->next;
		}
	}
	PolyNode* prev_node = NULL;
	PolyNode* curr_node = head;

	while (curr_node && curr_node->coef != 0.0) {
		prev_node = curr_node;
		curr_node = curr_node->next;
	}
	if (curr_node) {
		if (prev_node) {
			prev_node->next = curr_node->next;
			delete curr_node;
		}
		else {
			head = curr_node->next;
			delete curr_node;
		}
	}
	return head;
} // end-AddNode

//-------------------------------------------------
// Adds two polynomials and returns a new polynomial that contains the result
// Computes: poly3 = poly1 + poly2 and returns poly3
//
PolyNode *Add(PolyNode *poly1, PolyNode *poly2) {
	struct PolyNode* head = NULL, *ptr1 = NULL, *ptr2 = NULL;
	while (poly1 && poly2)
	{
		ptr2 = new(PolyNode);
		ptr2->next = NULL;
		if (poly1->exp > poly2->exp)
		{
			ptr2->coef = poly1->coef;
			ptr2->exp = poly1->exp;
			poly1 = poly1->next;
		}
		else if (poly1->exp < poly2->exp)
		{
			ptr2->coef = poly2->coef;
			ptr2->exp = poly2->exp;
			poly2 = poly2->next;
		}
		else
		{
			ptr2->coef = poly1->coef + poly2->coef;
			ptr2->exp = poly1->exp;
			poly2 = poly2->next;
			poly1 = poly1->next;
		}
		if (head == NULL) {
			head = ptr2;
			ptr1 = head;
		}
		else
		{
			ptr1->next = ptr2;
			ptr1 = ptr2;
		}
	}
	return head;
} //end-Add

//-------------------------------------------------
// Subtracts poly2 from poly1 and returns the resulting polynomial
// Computes: poly3 = poly1 - poly2 and returns poly3
//
PolyNode *Subtract(PolyNode *poly1, PolyNode *poly2) {

	struct PolyNode* head = NULL, *ptr1 = NULL, *ptr2 = NULL;
	while (poly1 && poly2)
	{
		ptr2 = new(PolyNode);
		ptr2->next = NULL;
		if (poly1->exp > poly2->exp)
		{
			ptr2->coef = poly1->coef;
			ptr2->exp = poly1->exp;
			poly1 = poly1->next;
		}
		else if (poly1->exp < poly2->exp)
		{
			ptr2->coef = poly2->coef;
			ptr2->exp = poly2->exp;
			poly2 = poly2->next;
		}
		else
		{
			ptr2->coef = poly1->coef - poly2->coef;
			ptr2->exp = poly1->exp;
			poly2 = poly2->next;
			poly1 = poly1->next;
		}
		if (head == NULL) {
			head = ptr2;
			ptr1 = head;
		}
		else
		{
			ptr1->next = ptr2;
			ptr1 = ptr2;
		}
	}
	return head;
} //end-Substract

//-------------------------------------------------
// Multiplies poly1 and poly2 and returns the resulting polynomial
// Computes: poly3 = poly1 * poly2 and returns poly3
//
PolyNode* Multiply(PolyNode* poly1, PolyNode* poly2) {
	struct PolyNode* P1, *P2, *multiply_poly;
	P1 = poly1;
	P2 = poly2;
	multiply_poly = NULL;
	struct PolyNode* temp = P2;
	while (P1 != NULL)
	{
		P2 = temp;
		while (P2 != NULL)
		{
			multiply_poly = AddNode(multiply_poly, P1->coef * P2->coef, P1->exp + P2->exp);

			P2 = P2->next;
		}
		P1 = P1->next;
	}
	return multiply_poly;
} //end-Multiply

//-------------------------------------------------
// Evaluates the polynomial at a particular "x" value and returns the result
//
double Evaluate(PolyNode *poly, double x) {
	struct PolyNode* p;
	double result = 0;

	for (p = poly; p != NULL; p = p->next)
		result = result + (p->coef * pow(x, p->exp));
	return result;
} //end-Evaluate

//-------------------------------------------------
// Computes the derivative of the polynomial and returns it
// Ex: poly(x) = 3x^4 - 2x + 1-->Derivative(poly) = 12x^3 - 2
//
PolyNode *Derivative(PolyNode *poly) {
	PolyNode* node = new PolyNode;
	node = poly;

	while (node != NULL) {
		if (node->exp == 0) {
			node->coef = 0;
			node->exp = 0;
			node = node->next;
		}
		else {
			node->coef = node->coef * node->exp;
			node->exp = node->exp - 1;
			node = node->next;
		}
		PolyNode* prev_node = NULL;
		PolyNode* curr_node = poly;

		while (curr_node && curr_node->coef != 0.0) {
			prev_node = curr_node;
			curr_node = curr_node->next;
		}
		if (curr_node) {
			if (prev_node) {
				prev_node->next = curr_node->next;
				delete curr_node;
			}
			else {
				poly = curr_node->next;
				delete curr_node;
			}
		}
	}
	return poly;
} //end-Derivative

//-------------------------------------------------
// Plots the polynomial in the range [x1, x2].
// -39<=x1<x2<=39
// -12<=y<=12
// On the middle of the screen you gotta have x & y axis plotted
// During evaluation, if "y" value does not fit on the screen,
// then just skip it. Otherwise put a '*' char depicting the curve
//
void Plot(PolyNode *poly, int x1, int x2) {
	int Y;
	cout << endl;
	for (int y = 12; y >= -12; y--) {
		for (int x = -39; x <= 39; x++) {
			if (x2 > x && x > x1) {
				Y = Evaluate(poly, x);
				if (Y == y && x != 0 && y != 0) {
					cout << "*";
				}
				else if (y == 0 && x == 0) {
					cout << "+";
				}
				else if (y == 0) {
					if (x % 5 == 0)cout << "+";
					else cout << "-";
				}
				else if (x == 0) {
					if (y % 5 == 0)cout << "+";
					else cout << "|";
				}
				else {
					cout << " ";
				}
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
} //end-Plot