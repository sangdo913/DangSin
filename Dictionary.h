#pragma once
#include<iostream>
template <typename T>
class ListValue;

template<typename key,typename value>
class Dictionary
{
	
};

template<typename T>
class List
{
private:
	ListValue<T> start;
	int size;

public:
	List();
	bool hasNext();
	T getValue(int num);
	int hasValue(T value);
	T* getNext();
	T* getPrevious();
};

template<typename T>
class ListValue
{
private:

public:
	ListValue();
	ListValue(T* next, T* previous);
	T value;
	ListValue<T>* next;
	ListValue<T>* previous;
};
