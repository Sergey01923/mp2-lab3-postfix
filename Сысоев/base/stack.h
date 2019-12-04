#ifndef __STACK_H__
#define __STACK_H__
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
const int MaxStackSize = 100;

template <class T>
class TStack
{
	T pMem[MaxStackSize];
	int top;
public:
	TStack()
	{
		top = -1;
	}
	~TStack() {
	}
	bool isFull()
	{
		return top == MaxStackSize - 1;
	}
	bool isEmpty()
	{
		return top == -1;
	}
	void push(const T &a)
	{
		if (isFull())
			throw 1;
		pMem[++top] = a;
	}
	T pop()
	{
		if (isEmpty())
			throw 1;
		return pMem[top--];
	}
	T gettop()
	{
		if (isEmpty())
			throw 1;
		return pMem[top];
	}

};

#endif
