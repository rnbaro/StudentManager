#pragma once

template<class T>
class Node
{
public:
	T* mpData;
	Node<T>* mpPrev;
	Node<T>* mpNext;

public:
	Node();
	Node(T* data);
	~Node();
};

template<class T>
Node<T>::Node(void)
{
	mpData = nullptr;
	mpPrev = nullptr;
	mpNext = nullptr;
}
template<class T>
Node<T>::Node(T* data)
{
	mpData = data;
	mpPrev = nullptr;
	mpNext = nullptr;
}
template<class T>
Node<T>::~Node(void)
{
	delete mpData;

	mpData = nullptr;
	mpPrev = nullptr;
	mpNext = nullptr;
}