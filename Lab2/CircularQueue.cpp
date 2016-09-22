#include<cstring>
#include<iostream>
#include "CircularQueue.hpp"

typedef CircularQueue::QueueItem QueueItem;
const QueueItem CircularQueue::EMPTY_QUEUE = -999;

CircularQueue::CircularQueue()
{
	capacity_ = 16;
	items_ = new int[capacity_];
	size_ = 0;
	head_ = 0;
	tail_ = 0;
}

CircularQueue::CircularQueue(unsigned int capacity)
{
	capacity_ = capacity;
	items_ = new int[capacity];
	size_ = 0;
	head_ = 0;
	tail_ = 0;
}

CircularQueue::~CircularQueue()
{
	delete []items_;
}

bool CircularQueue::empty() const
{   
	return size_== 0; 
}

bool CircularQueue::full() const
{
	return size_== capacity_;
}

int CircularQueue::size() const
{  
	return size_;
}

bool CircularQueue::enqueue(QueueItem value)
{
	if(full())
	{
		return false;
	}

	items_[tail_] = value;	
	tail_ = (tail_+1)%capacity_;	
	size_++;
	return true;
}

QueueItem CircularQueue::dequeue()
{
	if(empty())	
	{
		return EMPTY_QUEUE;
	}
	
	size_--;	
	head_ = (head_+1)%capacity_;
	
	if(head_ == 0)	return items_[capacity_-1]; // if rearranged head is set to 0, previous head must be at capacity_-1; therefore return that index
	
	return items_[head_-1];
		
}

QueueItem CircularQueue::peek() const
{
	if(empty())
		return EMPTY_QUEUE;
	return items_[head_];	
}

void CircularQueue::print() const
{
	if(empty())
		return;
		
	if(head_< tail_)
	{
		for(int i = head_; i<tail_; i++)
		{
			std::cout << items_[i] << std::endl;
		}
	}
	else if(head_>=tail_)
	{
		for(int i = head_; i< capacity_;i++)
		{
			std::cout << items_[i] << std::endl;
		}
		for(int i = 0; i< tail_; i++)
		{
			std::cout << items_[i] << std::endl;
		}
	}
	
}
