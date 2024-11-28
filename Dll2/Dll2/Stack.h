#include<iostream>
#include<stdexcept>
#include<vector>
#pragma once
using namespace std;
template<class T>
class Stack
{
private:
	T* tab;//la pile
	int nbelemt;//le nombre d'element de la pile
	int capacite;//la capacité de la pile
public:
	Stack();//Constructeur
	bool is_empty()const;//Tester si la pile est vide 
	bool is_full()const;//Tester si la pile est pleine
	int size()const;//retourne la taille de la pile
	void pop();//retirer l'element en tête de la pile
	T top();//renvoie l'element en tête de la pile
	void print();//Afficher tous les elements de la pile
	void push(T);//ajouter un element à la pile
	~Stack();//Destructeur
};


//Initialiser la pile
template<class T>
inline Stack<T>::Stack() :nbelemt(-1), capacite(100)
{
	tab = new T[capacite];
}

//Verifier si la pile est vide
template<class T>
inline bool Stack<T>::is_empty() const
{
	return nbelemt == -1;
}
//Verifier si la pile est pleine
template<class T>
inline bool Stack<T>::is_full() const
{
	return nbelemt == capacite;
}
//la taille de la pile
template<class T>
inline int Stack<T>::size() const
{
	return nbelemt+1;
}
//Retirer un element de la pile
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

// retourne l'element en tête
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

// afficher tous les elements de la pile
template<class T>
inline void Stack<T>::print()
{
	while (!is_empty())
	{
		std::cout << tab[nbelemt] <<" ";
		pop();
	}
}

//Ajouter un element à la pile
template<class T>
inline void Stack<T>::push(T elm)
{
	if (!this->is_full())
		tab[++nbelemt] = elm;
	else
		throw std::overflow_error("la pile est pleine");
}

//Destructeur
template<class T>
inline Stack<T>::~Stack()
{
	delete[] this->tab;
}
