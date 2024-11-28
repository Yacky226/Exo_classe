#include<iostream>
#include<stdexcept>
#include<vector>
#pragma once
using namespace std;
template<class T>
class Stack
{
private:
	T* tab;
	int nbelemt;
	int capacite;
public:
	Stack();
	bool is_empty()const;
	bool is_full()const;
	int size()const;
	void pop();
	T top();
	void print();
	void push(T);
   

	~Stack();
};


template<class T>
inline Stack<T>::Stack() :nbelemt(-1), capacite(100)
{
	tab = new T[capacite];

}

template<class T>
inline bool Stack<T>::is_empty() const
{

	return nbelemt == -1;
}

template<class T>
inline bool Stack<T>::is_full() const
{
	return nbelemt == capacite;
}

template<class T>
inline int Stack<T>::size() const
{

	return nbelemt+1;
}

template<class T>
inline void Stack<T>::pop()
{
	if (!is_empty())
	{
		nbelemt--;
	}
	else
	{
		throw std::underflow_error("La pile est vide");

	}
		

}

template<class T>
inline T Stack<T>::top()
{
	T elm;
	if (is_empty())
	{
		throw std::underflow_error("error la pile est vide");
	}
	else
	{
		 elm = tab[nbelemt];
	}
	return elm;
}

template<class T>
inline void Stack<T>::print()
{
	while (!is_empty())
	{
		std::cout << tab[nbelemt] <<" ";
		pop();
	}
}

template<class T>
inline void Stack<T>::push(T elm)
{
	if (!this->is_full())
		tab[++nbelemt] = elm;
	else
		throw std::overflow_error("la pile est pleine");

}




template<class T>
inline Stack<T>::~Stack()
{
	delete[] this->tab;
}
