#pragma once
#include <iostream>
using namespace std;

template <class T> class SingleNode 
{
	public:
		T data;
		SingleNode<T>* next;
		static SingleNode<T> NIL;
		
		//to initialize NIL later on
		SingleNode() 
		{
			data = T();
			next = &NIL;
		}

		SingleNode(T nodeData) 
		{
			data = nodeData;
			next = &NIL;
		}
};

template <class T> SingleNode<T> SingleNode<T>::NIL;

