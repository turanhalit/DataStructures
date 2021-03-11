/*
* @author :  152120171108 Halitcan Turan
* @author :  152120181008 Yasin Binler
* @brief  :  This program is implementation of deque.
* @date   :  14/12/2020
*/
#include "Deque.h"
#include <iostream>

using namespace std;

///------------------------------------------------------
/// Default constructor
/// 
Deque::Deque() {
	head = tail = NULL;
	noOfItems = 0;
} //end-Deque

///------------------------------------------------------
/// Destructor
/// 
Deque::~Deque() {
	while (this->head) {
		DequeNode* node = this->head;
		this->head = this->head->next;
		delete node;
	}
} //end-~Deque

///------------------------------------------------------
/// Adds a new item to the front of the Deque
/// 
void Deque::AddFront(int item) {
	DequeNode* newNode = new DequeNode(item);

	if (head == NULL)
		tail = head = newNode;

	else
	{
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}

	noOfItems++;
} //end-AddFront

///------------------------------------------------------
/// Adds a new item to the end of the Deque
/// 
void Deque::AddRear(int item) {
	DequeNode* newNode = new DequeNode(item);

	if (tail == NULL)
		head = tail = newNode;

	else
	{
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}
	noOfItems++;
} //end-AddRear

///------------------------------------------------------
/// Remove and return the item at the front of the Deque
/// If the Deque is empty, throw an exception
/// 
int Deque::RemoveFront() {

	if (this->head == NULL) throw std::exception("Deque::RemoveFront: Empty deque");

	int item = this->head->item;
	DequeNode* node = this->head;
	this->head = this->head->next;
	if (this->head == NULL) this->tail = NULL;
	else
		head->prev = NULL;

	delete node;
	this->noOfItems--;
	return item;

} //end-RemoveFront

int Deque::RemoveRear() {

	if (this->tail == NULL) throw std::exception("Deque::RemoveRear: Empty deque");

	int item = this->tail->item;
	DequeNode* node = this->tail;
	this->tail = this->tail->prev;
	if (this->tail == NULL) this->head = NULL;
	else
		tail->next = NULL;

	delete node;
	this->noOfItems--;
	return item;

} //end-RemoveRear

///------------------------------------------------------
/// Return the item at the front of the Deque (do not remove the item)
/// If the Deque is empty, throw an exception
/// 
int Deque::Front() {
	if (this->head == NULL)throw std::exception("Deque::Front: Empty deque");
	return this->head->item;
} //end-Front

///------------------------------------------------------
/// Return the item at the rear of the Deque (do not remove the item)
/// If the Deque is empty, throw an exception
/// 
int Deque::Rear() {
	if (this->tail == NULL)throw std::exception("Deque::Rear: Empty deque");
	return this->tail->item;
} //end-Rear