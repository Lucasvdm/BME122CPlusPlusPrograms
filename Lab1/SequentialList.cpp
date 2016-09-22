#include "SequentialList.hpp"
#include <cstdlib>
#include <string>
#include <iostream>

SequentialList::SequentialList(unsigned int cap)
{	
	data_ = new DataType[cap];
	capacity_ = cap;
	size_ = 0;
}

SequentialList::~SequentialList()
{
	delete []data_;
}

bool SequentialList::empty() const
{
	return size_ == 0;
}

unsigned int SequentialList::size() const
{
	return size_;
}

unsigned int SequentialList::capacity() const
{
	return capacity_;
}

bool SequentialList::full() const
{
	return size_ == capacity_;
}

void SequentialList::print() const
{
	if(!empty()) // if not empty, print all values in sequence
	{
		for(int i = 0; i<size_; i++)
		{
			std::cout << data_[i] << " ";
		}
		std::cout << std::endl;
	}	
	else
		std::cout << "List is empty" << std::endl;
}

bool SequentialList::insert_front(DataType val)
{	
	if(!full())
	{		
		size_++;
		for(int i = size_ - 1; i > 0; i--)
		{
			data_[i] = data_[i-1];
		}
		data_[0] = val; 
		return true;
	}
	else
	{
		return false;
	}
}

bool SequentialList::remove_front()
{
	if(!empty()) // can only remove if list is not empty
	{
		for(unsigned int i = 0; i<size_-1; i++) // shift all elements 1 index to left, thereby cutting off last element
		{
			data_[i] = data_[i+1]; 
		}
		size_--;
		return true;
	}
	else 
		return false;
}

bool SequentialList::insert_back(DataType val)
{
	if(!full())
	{
		size_++;
		data_[size_- 1] = val; // set last element in sequence to val
		return true;
	}
	else
	{
		return false;
	}
}

bool SequentialList::remove_back()
{
	if(empty()) // if list is empty, nothing to remove and return false
	{
		return false;
	}
	else
	{
		size_--;
		return true;
	}
}

bool SequentialList::insert(DataType val, unsigned int index)
{
	if(index > size_)
	{
		return false;
	}
	else if(size_ == capacity_)
	{
		return false;
	}
	else
	{
		size_++; // increment sequence size
		for(unsigned int i = size_ - 1; i>index; i--) // set the new last value of the sequence, and shift all values 1 index to right
		{
			data_[i] = data_[i-1];
		}
		data_[index] = val;
		return true;
	}
}

bool SequentialList::remove(unsigned int index)
{
	if(index >= size_) // if index >= size, the index is referring to an index in the list that has not been initialized or out of bounds; therefore return false
	{
		return false;
	}
	else
	{
		for(unsigned int i = index; i < size_ - 1; i++) // shift elements 1 to left
		{
			data_[i] = data_[i + 1];
		}
		size_--;
		return true;
	}
}

unsigned int SequentialList::search(DataType val) const
{
	if(!empty()) // if list is not empty, search through sequence; if empty, return size, which is 0
	{
		for(unsigned int i = 0; i< size_; i++)
		{
			if(data_[i] == val)
			{
				return i;
			}
		}		
	}
	return size();
}

SequentialList::DataType SequentialList::select(unsigned int index) const
{
	if(empty()) // if empty return -1 to show list has no elements
	{
		return -1;
	}
	else if(index >=size_)
	{
		return data_[size_-1]; // return index of last element if index is invalid
	}	
	
	return data_[index];		
}

bool SequentialList::replace(unsigned int index, DataType val)
{
	if(index >= size_ ) // you can only replace an element at an index that has already been initialized (i.e. index < size)
	{
		return false;
	}
	else
	{
		data_[index] = val;
		return true;
	}
}
