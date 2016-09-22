#include "DoublyLinkedList.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

DoublyLinkedList::Node::Node(DataType data)
{
	value = data;
	next = NULL;
	prev = NULL;
}

DoublyLinkedList::DoublyLinkedList()
{
	head_ = NULL;
	tail_ = NULL;
	size_ = 0;
}

DoublyLinkedList::~DoublyLinkedList()
{
	if(empty()) return;
	else
	{
		Node* tempPtr1 = tail_;
		Node* tempPtr2 = tempPtr1 -> prev;
		while(tempPtr2 != NULL)
		{
			delete tempPtr1;
			tempPtr1 = tempPtr2;
			tempPtr2 = tempPtr2 -> prev;
		}
		delete tempPtr1;
	}
}

bool DoublyLinkedList::empty() const
{
	if(head_ == NULL) return true;
	else return false;
}

unsigned int DoublyLinkedList::size() const
{
	return size_;
}

void DoublyLinkedList::print() const
{
	if(empty()) return;
	else
	{
		Node* tempPtr = head_;
		while(tempPtr != NULL)
		{
			cout << tempPtr -> value << " ";
			tempPtr = tempPtr -> next;
		}
		cout << endl;
	}
}

bool DoublyLinkedList::insert_front(DataType value)
{
	if(full()) return false;
	else if(empty())
	{
		head_ = new Node(value);
		tail_ = head_;
	}
	else
	{
		Node* tempPtr = new Node(value);
		tempPtr -> next = head_;
		head_ -> prev = tempPtr;
		head_ = tempPtr;
	}
	size_++;
	return true;
}

bool DoublyLinkedList::remove_front()
{
	if(empty()) return false;
	else
	{
		Node* tempPtr = head_ -> next;
		delete head_;
		if(tempPtr == NULL)
		{
			head_ = NULL;
			tail_ = NULL;
		}
		else
		{
			head_ = tempPtr;
			head_ -> prev = NULL;
		}
		size_--;
		return true;
	}
}

bool DoublyLinkedList::insert_back(DataType value)
{
	if(full()) return false;
	else if(empty())
	{
		tail_ = new Node(value);
		head_ = tail_;
	}
	else
	{
		Node* tempPtr = new Node(value);
		tempPtr -> prev = tail_;
		tail_ -> next = tempPtr;
		tail_ = tempPtr;
	}
	size_++;
	return true;
}

bool DoublyLinkedList::remove_back()
{
	if(empty()) return false;
	else
	{
		Node* tempPtr = tail_ -> prev;
		delete tail_;
		if(tempPtr == NULL)
		{
			tail_ = NULL;
			head_ = NULL;
		}
		else
		{
			tail_ = tempPtr;
			tail_ -> next = NULL;
		}
		size_--;
		return true;
	}
}

bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
	if(full() || index > size()) return false;
	else if(index == 0) insert_front(value);
	else if(index == size()) insert_back(value);
	else
	{
		Node* nodeAtIndex = getNode(index);
		Node* prevNode = nodeAtIndex -> prev;
		Node* newNode = new Node(value);
		newNode -> prev = prevNode;
		prevNode -> next = newNode;
		newNode -> next = nodeAtIndex;
		nodeAtIndex -> prev = newNode;
		size_++;
	}
	return true;
}

bool DoublyLinkedList::remove(unsigned int index)
{
	if(empty() || index >= size()) return false;
	else if(index == 0) remove_front();
	else if(index == size() - 1) remove_back();
	else
	{
		Node* nodeAtIndex = getNode(index);
		Node* prevNode = nodeAtIndex -> prev;
		Node* nextNode = nodeAtIndex -> next;
		delete nodeAtIndex;
		prevNode -> next = nextNode;
		nextNode -> prev = prevNode;
		size_--;
	}
	return true;
}

unsigned int DoublyLinkedList::search(DataType value) const
{
	if(empty()) return 0;
	else
	{
		Node* tempPtr = head_;
		int index = 0;
		while(tempPtr != NULL)
		{
			if(tempPtr -> value == value) return index;
			else
			{
				tempPtr = tempPtr -> next;
				index++;
			}
		}
		return size();
	}
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
	if(empty()) return NULL;
	else if(index >= size()) return tail_ -> value;
	else
	{
		Node* nodeAtIndex = getNode(index);
		return nodeAtIndex -> value;
	}
}

bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
	if(empty() || index >= size()) return false;
	else
	{
		Node* nodeAtIndex = getNode(index);
		nodeAtIndex -> value = value;
		return true;
	}
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
	if(empty() || index >= size()) return NULL;
	else
	{
		Node* tempPtr = head_;
		for(int i = 0; i < index; i++)
		{
			tempPtr = tempPtr -> next;
		}
		return tempPtr;
	}
}

bool DoublyLinkedList::full() const
{
	if(size() >= CAPACITY) return true;
	else return false;
}
