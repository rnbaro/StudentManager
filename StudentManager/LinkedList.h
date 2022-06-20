#pragma once
#include "Node.h"

template<class T>
class Linkedlist
{
public:
	int mCount;
	Node<T>* mpHead;

public:
	Linkedlist();
	~Linkedlist();

	int GetCount();
	int GetIndex(Node<T>* pNode);

	void AddFirst(T* pData);
	void AddFirst(Node<T>* pNode);
	void AddFirstRange(Linkedlist<T>* pList);

	void AddLast(T* pData);
	void AddLast(Node<T>* pNode);
	void AddLastRange(Linkedlist<T>* pList);

	bool AddBefore(Node<T>* target, T* pData);
	bool AddBefore(Node<T>* target, Node<T>* newNode);
	bool AddBeforeRange(Node<T>* target, Linkedlist<T>* pList);

	void Remove(Node<T>* node);
	void Clear();

private:
	void InsertNodeToEmptyList(Node<T>* pNewNode);
	void InsertNode(Node<T>* pNode, Node<T>* pNewNode);
	void InsertRangeToEmptyList(Linkedlist<T>* pList);
	void InsertRange(Node<T>* pNode, Linkedlist<T>* pList);
};

template<class T>
int Linkedlist<T>::GetCount()
{
	return mCount;
}
template<class T>
int Linkedlist<T>::GetIndex(Node<T>* pNode)
{
	if (mpHead == nullptr || pNode == nullptr)
	{
		return -1;
	}

	int index = 0;
	Node<T>* find = mpHead;

	while (find != pNode)
	{
		++index;
		find = find->mpNext;

		if (find == mpHead)
		{
			return -1;
		}
	}

	return index;
}

template<class T>
Linkedlist<T>::Linkedlist()
{
	mCount = 0;
	mpHead = nullptr;
}
template<class T>
Linkedlist<T>::~Linkedlist()
{
	Clear();
}

template<class T>
void Linkedlist<T>::AddFirst(T* pData)
{
	if (pData == nullptr)
	{
		return;
	}

	Node<T>* pNewNode = new Node<T>();
	pNewNode->mpData = pData;

	if (mpHead == nullptr)
	{
		InsertNodeToEmptyList(pNewNode);
	}
	else
	{
		InsertNode(mpHead, pNewNode);
		mpHead = pNewNode;
	}
}
template<class T>
void Linkedlist<T>::AddFirst(Node<T>* pNode)
{
	if (pNode == nullptr)
	{
		return;
	}

	if (mpHead == nullptr)
	{
		InsertNodeToEmptyList(pNode);
	}
	else
	{
		InsertNode(mpHead, pNode);
		mpHead = pNode;
	}
}
template<class T>
void Linkedlist<T>::AddFirstRange(Linkedlist<T>* pList)
{
	if (pList == nullptr || pList->mpHead == nullptr)
	{
		return;
	}

	if (this->mpHead == nullptr)
	{
		InsertRangeToEmptyList(pList);
	}
	else
	{
		InsertRange(this->mpHead, pList);
		this->mpHead = pList->mpHead;
	}

	pList->mCount = 0;
	pList->mpHead = nullptr;
}

template<class T>
void Linkedlist<T>::AddLast(T* pData)
{
	if (pData == nullptr)
	{
		return;
	}

	Node<T>* pNewNode = new Node<T>();
	pNewNode->mpData = pData;

	if (mpHead == nullptr)
	{
		InsertNodeToEmptyList(pNewNode);
	}
	else
	{
		InsertNode(mpHead, pNewNode);
	}
}
template<class T>
void Linkedlist<T>::AddLast(Node<T>* pNode)
{
	if (pNode == pNode)
	{
		return;
	}

	if (mpHead == nullptr)
	{
		InsertNodeToEmptyList(pNode);
	}
	else
	{
		InsertNode(mpHead, pNode);
	}
}
template<class T>
void Linkedlist<T>::AddLastRange(Linkedlist<T>* pList)
{
	if (pList == nullptr || pList->mpHead == nullptr)
	{
		return;
	}

	if (mpHead == nullptr)
	{
		InsertRangeToEmptyList(pList);
	}
	else
	{
		InsertRange(mpHead, pList);
	}

	pList->mCount = 0;
	pList->mpHead = nullptr;
}
template<class T>
bool Linkedlist<T>::AddBefore(Node<T>* target, T* pData)
{
	if (target == nullptr || pData == nullptr)
	{
		return false;
	}

	Node<T>* pNewNode = new Node<T>();
	pNewNode->mpData = pData;

	InsertNode(target, pNewNode);

	if (target == mpHead)
	{
		mpHead = pNewNode;
	}

	return true;
}
template<class T>
bool Linkedlist<T>::AddBefore(Node<T>* target, Node<T>* newNode)
{
	if (target == nullptr || newNode == nullptr)
	{
		return false;
	}

	InsertNode(target, newNode);

	if (target == mpHead)
	{
		mpHead = newNode;
	}

	return true;
}
template<class T>
bool Linkedlist<T>::AddBeforeRange(Node<T>* target, Linkedlist<T>* pList)
{
	if (target == nullptr || pList == nullptr || pList->mpHead == nullptr)
	{
		return false;
	}

	InsertRange(target, pList);

	if (target == mpHead)
	{
		this->mpHead = pList->mpHead;
	}

	pList->mCount = 0;
	pList->mpHead = nullptr;

	return true;
}

template<class T>
void Linkedlist<T>::Remove(Node<T>* pNode)
{
	if (pNode == nullptr)
	{
		return;
	}

	if (pNode->mpNext == pNode)
	{
		mpHead = nullptr;
	}
	else
	{
		pNode->mpPrev->mpNext = pNode->mpNext;
		pNode->mpNext->mpPrev = pNode->mpPrev;

		if (mpHead == pNode)
		{
			mpHead = pNode->mpNext;
		}
	}

	--mCount;
	delete pNode;
}
template<class T>
void Linkedlist<T>::Clear()
{
	while (mpHead != nullptr)
	{
		Remove(mpHead);
	}

	mCount = 0;
	mpHead = nullptr;
}

template<class T>
void Linkedlist<T>::InsertNodeToEmptyList(Node<T>* pNewNode)
{
	mpHead = pNewNode;
	pNewNode->mpPrev = pNewNode;
	pNewNode->mpNext = pNewNode;

	++mCount;
}
template<class T>
void Linkedlist<T>::InsertNode(Node<T>* pNode, Node<T>* pNewNode)
{
	pNewNode->mpPrev = pNode->mpPrev;
	pNewNode->mpNext = pNode;
	pNode->mpPrev->mpNext = pNewNode;
	pNode->mpPrev = pNewNode;

	++mCount;
}
template<class T>
void Linkedlist<T>::InsertRangeToEmptyList(Linkedlist<T>* pList)
{
	this->mpHead = pList->mpHead;
	this->mCount = pList->mCount;

	pList->mpHead = nullptr;
	pList->mCount = 0;
}
template<class T>
void Linkedlist<T>::InsertRange(Node<T>* pNode, Linkedlist<T>* pList)
{
	Node<T>* temp = pList->mpHead->mpPrev;

	pList->mpHead->mpPrev->mpNext = pNode;
	pList->mpHead->mpPrev = pNode->mpPrev;
	pNode->mpPrev->mpNext = pList->mpHead;
	pNode->mpPrev = temp;

	this->mCount += pList->mCount;
}