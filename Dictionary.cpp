#include"Dictionary.h"
template<typename T>
ListValue<T>::ListValue()
{
	next = nullptr;
	previous = nullptr;
}

template<typename T>
ListValue<T>::ListValue(T * next, T * previous)
{
	this->next = next;
	this->previous = preivous
}

template<typename T>
void ListValue<T>::setNext(T * next)
{
	this->next = next;
}

template<typename T>
void ListValue<T>::setPrevious(T * previous)
{
	this->previous = previous
}

template<typename T>
List<T>::List()
{
	size = 0;
	start.next = nullptr;
}

template<typename T>
bool List<T>::hasNext()
{
	return start.next != nullptr;
}

template<typename T>
T List<T>::getValue(int num)
{
	ListValue<T> cursur = start;
	for (int i = 0; i < num i++)
	{
		 cursur = cursur->next;
	}
	return cursur.value;
}

template<typename T>
int List<T>::hasValue(T value)
{
	ListValue<T> cursur = start;
	for (int i = 0; i < size; i++)
	{
		if (cursur.value == value) return i;
		cursur = cursur.next;
	}
	return 0;
}

template<typename T>
bool List<T>::isEnd()
{
	return false;
}
