/*
* @author :  152120171108 Halitcan Turan
* @author :  152120181008 Yasin Binler
* @brief  :  This program is implementation of threaded bst.
* @date   :  30/12/2020
*/

#include "ThreadedBST.h"

///-----------------------------------------------
/// Erases all nodes in the tree
/// 
void ThreadedBST::eraseTreeNodes(BSTNode* node) {
	BSTNode* curr = this->min();

	while (curr != NULL) {

		BSTNode* n = this->next(curr);

		delete curr;

		curr = n;

	} // end-while
} //end-eraseTreeNodes

///-----------------------------------------------
/// Adds a given key to the BST
/// 
void ThreadedBST::add(int key) {
	BSTNode* p = root;
	BSTNode* pp = NULL;
	while (p != NULL) {

		if (key == (p->key)) {
			return;
		}

		pp = p;

		if (key < p->key) {
			if (p->leftLinkType == CHILD)
				p = p->left;
			else
				break;
		}

		else {
			if (p->rightLinkType == CHILD)
				p = p->right;
			else
				break;
		}
	}

	BSTNode* newNode = new BSTNode(key);
	newNode->key = key;
	newNode->leftLinkType = THREAD;
	newNode->rightLinkType = THREAD;

	if (pp == NULL) {
		root = newNode;
		newNode->left = NULL;
		newNode->right = NULL;
	}
	else if (key < (pp->key)) {
		newNode->left = pp->left;
		newNode->right = pp;
		pp->leftLinkType = CHILD;
		pp->left = newNode;
	}
	else {
		newNode->left = pp;
		newNode->right = pp->right;
		pp->rightLinkType = CHILD;
		pp->right = newNode;
	}
} // end-add

///-----------------------------------------------
/// Removes a given key from the BST (if it exists)
/// 
void ThreadedBST::remove(int key) {
	BSTNode* ptr1, *ptr2;
	if (key <= root->key) {
		ptr1 = root->left;
		ptr2 = root;
	}
	else {
		ptr1 = root->right;
		ptr2 = root;
	}
	for(;;)
	{
		if (ptr1->key < key)
		{
			if (ptr1->rightLinkType == THREAD) return;
			ptr2 = ptr1;
			ptr1 = ptr1->right;
		}
		else if (ptr1->key > key)
		{
			if (ptr1->leftLinkType == THREAD) return;
			ptr2 = ptr1;
			ptr1 = ptr1->left;
		}
		else
		{
			break;
		}
	}

	BSTNode* Node = ptr1;
	if (ptr1->rightLinkType != THREAD && ptr1->leftLinkType != THREAD)
	{
		ptr2 = ptr1;
		Node = ptr1->left;
		while (Node->rightLinkType != THREAD) {
			ptr2 = Node;
			Node = Node->right;
		}
		ptr1->key = Node->key;
	}

	if (ptr2->key >= Node->key) {
		if (Node->rightLinkType == THREAD && Node->leftLinkType == THREAD)
		{
			ptr2->left = Node->left;
			ptr2->leftLinkType = THREAD;
		}
		else if (Node->rightLinkType == THREAD)
		{
			BSTNode* biggestNode = Node->left;

			while (biggestNode->rightLinkType != THREAD)
			{
				biggestNode = biggestNode->right;
			}

			biggestNode->right = ptr1;
			ptr2->left = Node->left;
		}
		else {
			BSTNode* leastNode = Node->right;

			while (leastNode->leftLinkType != THREAD)
			{
				leastNode = leastNode->left;
			}
			leastNode->left = Node->left;
			ptr2->left = Node->right;
		}
	}
	else {
		if (Node->rightLinkType == THREAD && Node->leftLinkType == THREAD) {
			ptr2->right = Node->right;
			ptr2->rightLinkType = THREAD;
		}
		else if (Node->rightLinkType == THREAD) {
			BSTNode* biggestNode = Node->left;
			while (biggestNode->rightLinkType != THREAD) {
				biggestNode = biggestNode->right;
			}
			biggestNode->right = Node->right;
			ptr2->right = Node->left;
		}
		else {
			BSTNode* leastNode = Node->right;
			while (leastNode->leftLinkType != THREAD) {
				leastNode = leastNode->left;
			}
			leastNode->left = ptr2;
			ptr2->right = Node->right;
		}
	}
} // end-remove

///-----------------------------------------------
/// Searches a given key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::find(int key) {

	BSTNode* ptr = root;

	while (ptr) {
		if (key == ptr->key) return ptr;
		if (key < ptr->key) ptr = ptr->left;
		else              ptr = ptr->right;
	} //end-while

	return NULL;
} // end-find

///-----------------------------------------------
/// Returns the minimum key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::min() {
	if (root == NULL) return NULL;

	BSTNode* ptr = root;
	while (ptr->left != NULL) ptr = ptr->left;

	return ptr;
} // end-min

///-----------------------------------------------
/// Returns the maximum key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::max() {
	if (root == NULL) return NULL;

	BSTNode* ptr = root;
	while (ptr->right != NULL) ptr = ptr->right;

	return ptr;
} // end-max

///-----------------------------------------------
/// Given a valid pointer to a node in ThreadedBST,
/// returns a pointer to the node that contains the inorder predecessor
/// If the inorder predecessor does not exist, returns NULL
/// 
BSTNode* ThreadedBST::previous(BSTNode* node) {
	if (node->leftLinkType == THREAD) return node->left;
	else
	{
		node = node->left;
		while (node->rightLinkType == CHILD) node = node->right;
		return node;
	}
} // end-previous

///-----------------------------------------------
/// Given a valid pointer to a node in the ThreadedBST,
/// returns a pointer to the node that contains the inorder successor
/// If the inorder successor does not exist, returns NULL
/// 
BSTNode* ThreadedBST::next(BSTNode* node) {
	if (node->rightLinkType == THREAD) return node->right;
	else
	{
		node = node->right;
		while (node->leftLinkType == CHILD) node = node->left;
		return node;
	}
} // end-next