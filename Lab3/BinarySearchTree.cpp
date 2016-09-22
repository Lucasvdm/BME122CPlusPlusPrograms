#include "BinarySearchTree.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef BinarySearchTree::DataType DataType;

// Implement the functions here.

BinarySearchTree::Node::Node(DataType newval)
{
	val = newval;
	left = NULL;
	right = NULL;
}

BinarySearchTree::BinarySearchTree()
{
	root_ = NULL;
	size_ = 0;
}

BinarySearchTree::~BinarySearchTree()
{
	while(root_ != NULL) remove(root_ -> val);
}

bool BinarySearchTree::insert(DataType val)
{
	Node* currentNode = root_;
	if(currentNode == NULL)
	{
		root_ = new Node(val);
		size_++;
		return true;
	}
	
	while(currentNode -> left != NULL || currentNode -> right != NULL)
	{
		if(val < currentNode -> val)
		{
			if(currentNode -> left != NULL)	currentNode = currentNode -> left;
			else
			{
				currentNode -> left = new Node(val);
				size_++;
				return true;
			}
		}
		else if(val > currentNode -> val)
		{
			if(currentNode -> right != NULL) currentNode = currentNode -> right;
			else
			{
				currentNode -> right = new Node(val);
				size_++;
				return true;
			}
		}
		else return false;
	}
	
	if(val < currentNode -> val)
	{
		currentNode -> left = new Node(val);
		size_++;
		return true;
	}
	else if(val > currentNode -> val)
	{
		currentNode -> right = new Node(val);
		size_++;
		return true;
	}
	else return false;
}

bool BinarySearchTree::remove(DataType val)
{
	Node* currentNode = root_;
	if(currentNode == NULL) return false;
	if(!exists(val)) return false;
	
	Node* prevNode;
	int lastMove = 0; //0 = no moves (root), 1 = left, 2 = right
	while(currentNode -> left != NULL || currentNode -> right != NULL)
	{
		if(val < currentNode -> val && currentNode -> left != NULL)
		{
			prevNode = currentNode;
			currentNode = currentNode -> left;
			lastMove = 1;
		}
		else if(val > currentNode -> val && currentNode -> right != NULL)
		{
			prevNode = currentNode;
			currentNode = currentNode -> right;
			lastMove = 2;
		}
		else //currentNode -> val == val, time to remove
		{
			if(currentNode -> right != NULL && currentNode -> left != NULL) //Node to remove has 2 children
			{
				Node* minNode = currentNode -> right;
				while(minNode -> left != NULL) minNode = minNode -> left;
				DataType tempVal = minNode -> val;
				remove(tempVal);
				currentNode -> val = tempVal;
				return true;
			}
			else //Node to remove has one child
			{
				if(lastMove == 0 && currentNode -> left != NULL)
				{
					root_ = currentNode -> left;
					currentNode -> left = NULL;
					delete currentNode;
				}
				else if(lastMove == 0 && currentNode -> right != NULL)
				{
					root_ = currentNode -> right;
					currentNode -> right = NULL;
					delete currentNode;
				}
				if(lastMove == 1 && currentNode -> left != NULL)
				{
					prevNode -> left = currentNode -> left;
					currentNode -> left = NULL;
					delete currentNode;
				}
				else if(lastMove == 1 && currentNode -> right != NULL)
				{
					prevNode -> left = currentNode -> right;
					currentNode -> right = NULL;
					delete currentNode;
				}
				else if(lastMove == 2 && currentNode -> left != NULL)
				{
					prevNode -> right = currentNode -> left;
					currentNode -> left = NULL;
					delete currentNode;
				}
				else if(lastMove == 2 && currentNode -> right != NULL)
				{
					prevNode -> right = currentNode -> right;
					currentNode -> right = NULL;
					delete currentNode;
				}
				size_--;
				return true;
			}
		}
	}
	
	if(currentNode -> val = val)
	{
		if(root_ == currentNode) root_ = NULL;
		delete currentNode;
		currentNode = NULL;
		if(lastMove == 1) prevNode -> left = NULL;
		if(lastMove == 2) prevNode -> right = NULL;
		size_--;
		return true;
	}
	else return false;
}

bool BinarySearchTree::exists(DataType val) const
{
	Node* currentNode = root_;
	if(currentNode -> val == val) return true;
	while(currentNode -> left != NULL || currentNode -> right != NULL)
	{
		if(currentNode -> val < val) 
		{
			if(currentNode -> right != NULL) currentNode = currentNode -> right;
			else return false;
		}
		else if(currentNode -> val > val)
		{
			if(currentNode -> left != NULL) currentNode = currentNode -> left;
			else return false;
		}
		else if(currentNode -> val == val) return true;
	}
	if(currentNode -> val == val) return true;
	return false;
}

DataType BinarySearchTree::min() const
{
	Node* currentNode = root_;
	while(currentNode -> left != NULL) currentNode = currentNode -> left;
	return currentNode -> val;
}

DataType BinarySearchTree::max() const
{
	Node* currentNode = root_;
	while(currentNode -> right != NULL) currentNode = currentNode -> right;
	return currentNode -> val;
}

unsigned int BinarySearchTree::size() const
{
	return size_;
}

unsigned int BinarySearchTree::depth() const
{
	return getNodeDepth(root_);
}

int BinarySearchTree::getNodeDepth(Node* n) const
{
	if(n == NULL) return -1;
	int l = 1 + getNodeDepth(n -> left);
	int r = 1 + getNodeDepth(n -> right);
	if(l > r) return l;
	else return r;
}

void BinarySearchTree::print() const
{
	
}
