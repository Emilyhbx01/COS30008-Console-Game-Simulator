#pragma once
#include "SingleNode.h"

template <class T> class SinglyLinkedList 
{
	private:
		SingleNode<T>* head;
		SingleNode<T>* tail;

	public:
		~SinglyLinkedList()
		{
			SingleNode<T>* temp;
			while (head != &SingleNode<T>::NIL) 
			{
				temp = head->next;
				delete head;
				head = temp;

			}
		}

		SinglyLinkedList() 
		{
			head = &SingleNode<T>::NIL;
			tail = &SingleNode<T>::NIL;
		}

		void append(SingleNode<T> &node) 
		{
			if (isEmpty())
			{
				head = &node;
				tail = &node;
			}
			else
			{
				tail->next = &node;
				tail = &node;
			}
		}

		SingleNode<T>* getHead() 
		{
			return head;
		}

		bool isEmpty() 
		{
			if (head == &SingleNode<T>::NIL && tail == &SingleNode<T>::NIL) 
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		
		void removeHead() 
		{
			if (head != &SingleNode<T>::NIL) 
			{
				
				if (head == tail)	//if there is only 1 node
				{
					head = &SingleNode<T>::NIL;
					tail = &SingleNode<T>::NIL;
				}
				else 
				{
					SingleNode<T>* temp = head->next;
					delete head;
					head = temp;
				}
				
			}
			
		}

};