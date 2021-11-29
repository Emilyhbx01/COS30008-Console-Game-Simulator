#pragma once
#include <iostream>
using namespace std;

template <class T> class BTree 
{
	private:
		T* key;
		BTree<T>* left;
		BTree<T>* right;
		BTree() 
		{
			key = (T*)0;
			left = &NIL;
			right = &NIL;
		}

	public:
		static BTree<T> NIL;

		~BTree() {

			if (left != &NIL)
			{
				delete left;
			}
			if (right != &NIL)
			{
				delete right;
			}
		}

		BTree(T& keyTree) 
		{
			key = &keyTree;
			left = &NIL;
			right = &NIL;
		}

		bool isEmpty() 
		{
			return this == &NIL;
		}

		T& getKey() 
		{
			if (isEmpty()) 
			{
				throw domain_error("Empty node");
			}
			return *key;
		}

		BTree<T>& getLeft() 
		{
			if (isEmpty()) 
			{
				throw domain_error("Empty node");
			}

			return *left;
		}

		BTree<T>& getRight()
		{
			if (isEmpty())
			{
				throw domain_error("Empty node");
			}

			return *right;
		}

		void attachLeft(BTree& node) 
		{
			if (isEmpty()) 
			{
				throw domain_error("Empty node");
			}

			if (left != &NIL) 
			{
				throw domain_error("Empty node");
			}
			left = &node;
		}

		void attachRight(BTree& node) 
		{
			if (isEmpty()) 
			{
				throw domain_error("Empty node");
			}

			if (right != &NIL) 
			{
				throw domain_error("Empty node");
			}
			right = &node;
		}


		BTree& search(T str)
		{
			if (isEmpty())
			{
				throw domain_error("Empty node");
			}

			BTree* temp = &NIL;

			if (left != &NIL) 
			{
				if (left->getKey() == str)
				{
					temp = right;
				}
				else
				{
					if (left != &NIL)
					{
						temp = &(left->search(str));
					}

					if (temp == &NIL && right != &NIL)
					{
						temp = &(right->search(str));
					}

				}
			}
			
			
			return *temp;
		}

		void display() 
		{
			if (left != &NIL) 
			{
				cout << left->getKey() << endl;
				left->display();
			}

		}
};

template<class T> BTree<T> BTree<T>::NIL;