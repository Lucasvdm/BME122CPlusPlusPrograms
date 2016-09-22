#include "DynamicStack.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef DynamicStack::StackItem StackItem;  // for simplicity
const StackItem DynamicStack::EMPTY_STACK = -999;

DynamicStack::DynamicStack()
{
	size_ = 0;
	capacity_ = 16;
	init_capacity_ = 16;
	items_ = new StackItem[16];
}

DynamicStack::DynamicStack(unsigned int capacity)
{
	size_ = 0;
	capacity_ = capacity;
	init_capacity_ = capacity;
	items_ = new StackItem[capacity];
}

DynamicStack::~DynamicStack()
{
	delete[] items_;
}

bool DynamicStack::empty() const
{
	if(size() == 0) return true;
	else return false;
}

int DynamicStack::size() const
{
	return size_;
}

void DynamicStack::push(StackItem value)
{
	if(size() < capacity_)
	{
		items_[size()] = value;
	}
	else
	{
		capacity_ *= 2;
		StackItem* temp = new StackItem[capacity_];
		for(int i = 0; i < capacity_ / 2; i++)
		{
			temp[i] = items_[i];
		}
		temp[size()] = value;
		delete[] items_;
		items_ = temp;
	}
	size_++;
}

StackItem DynamicStack::pop()
{
	StackItem returnValue = EMPTY_STACK;
	if(empty()) return returnValue;
	else
	{
		returnValue = items_[size() - 1];
		items_[size() - 1] = 0;
		size_--;
	}
	if(size() <= capacity_ / 4 && capacity_ / 2 >= init_capacity_)
	{	
		capacity_ /= 2;
		StackItem* temp = new StackItem[capacity_];
		for(int i = 0; i < size_; i++)
		{
			temp[i] = items_[i];
		}
		delete[] items_;
		items_ = temp;
	}
	return returnValue;
}

StackItem DynamicStack::peek() const
{
	if(empty()) return EMPTY_STACK;
	else
	{
		return items_[size() - 1];
	}
}

void DynamicStack::print() const
{
	for(int i = 0; i < size(); i++)
	{
		cout << items_[0] << " ";
	}
	cout << endl;
}
