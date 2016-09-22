#include "PriorityQueue.hpp"
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

typedef PriorityQueue::DataType DataType;
// Implement the functions here.

  // Constructor initializes heap_ to an array of size "capacity + 1", so that
  // there are at most "capacity" elements in the heap.
  PriorityQueue::PriorityQueue(unsigned int capacity)
  {
  	capacity_ = capacity + 1;
  	heap_ = new int[capacity_];
  	size_ = 0;  	
  }
  // Destructor.
  PriorityQueue::~PriorityQueue()
  {
  	delete[] heap_;
  }
  
  // Enqueues "val" into the priority queue. Returns false if failed, true
  // otherwise. Assume no duplicate entries will be entered.
  bool PriorityQueue::enqueue(DataType val)
  {
  	if(full())
  		return false;
  		
  	heap_[size_+1] = val;  	// insert at right-most index
  	int* temp = new int; // temp variable to allow switching between nodes
  	int* index = new int; // allow for indexing of the priority queue
  	
	*index = size_+1; // start index at right-most node
	
	while(*index > 1) // stop when index = 1; i.e. reaching the parent node
	{
		if(heap_[*index]> heap_[*index/2]) // if child > parent
		{
			*temp = heap_[*index]; 
			heap_[*index] = heap_[*index/2]; // switch child and parent node; i.e. lesser node becomes child
			heap_[*index/2] = *temp;
			*index = *index/2;
			continue;
		}
		else
			break;
	}
	
  	size_++;
	  delete temp;
	  delete index;
	  temp = NULL;
	  index = NULL;	
  	return true;
  }
  // Dequeues the top element with the maximum value (priority) and rearranges
  // the resulting heap. Returns false if failed, true otherwise.
  bool PriorityQueue::dequeue()
  {
  	if(empty())
  		return false;
  	
  	int* temp = new int; // temp variable to allow switching of the top node with the rightmost node
  	*temp = heap_[1];
  	heap_[1] = heap_[size_];
  	heap_[size_] = *temp;
  	int* i = new int; // index for heap
  	*i = 1;  	
  	
  	while(2*(*i) < size_)
  	{
  		if(2*(*i) + 1 < size_) // if there is a right child, do subsequent comparison
  		{
  			if(heap_[2*(*i)] > heap_[2*(*i) + 1]) // temp stores the larger of the child values
  			{
				*temp = heap_[2*(*i)];
  				if(heap_[*i] < *temp) // if parent < child, switch
  				{
  					heap_[2*(*i)] = heap_[*i];
  					heap_[*i] = *temp;
  					*i = 2*(*i);
  					continue;
				}
				else
					break;
  			}
  			else
			{
				*temp = heap_[2*(*i) + 1];
  				if(heap_[*i] < *temp) // if parent < child, switch
  				{
  					heap_[2*(*i) + 1] = heap_[*i];
  					heap_[*i] = *temp;
  					*i = 2*(*i) + 1;
  					continue;
				}
				else
					break;
  			}
		}
		else
		{
			*temp = heap_[2*(*i)];
  			if(heap_[*i] < *temp) // if parent < child, switch
  			{
  				heap_[2*(*i)] = heap_[*i];
  				heap_[*i] = *temp;
  				*i = 2*(*i);
  				continue;
			}
			else
				break;
		} 				
	}
	
	size_--;
	delete temp;
	delete i;	
  	return true;	
  }
  
  // Returns the max element of the priority queue, but does not remove it.
  DataType PriorityQueue::max() const
  {
  	if(empty())
  		return -1;
  		
  	return heap_[1];
  }
  // Returns true if the priority queue is empty; false otherwise.
  bool PriorityQueue::empty() const
  {
  	return size_ == 0;
  }
  // Returns true if the priority queue is full; false otherwise.
  bool PriorityQueue::full() const
  {
  	return size_ == capacity_-1;
  }
  // Returns the number of elements in the priority queue.
  unsigned int PriorityQueue::size() const
  {
  	return size_;
  }
  // Print the contents of the priority queue.
  void PriorityQueue::print() const
  {
  	for(int i = 1; i<= size_ ; i++)
  	{
  		std::cout << heap_[i] << " ";
	}
	std::cout << std::endl;
  }

