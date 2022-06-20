#pragma once
#include "LinkedList.h"

template<class T>
class DataTable
{
public:
	Linkedlist<T>* pList;
	Node<T>* pTopData;
	Node<T>* pBottomData;
	Node<T>* pCurrentData;
	int totalPage;
	int currentPage;
	int tableLength;
	const int FRONT_PAGE = 1;
	const int DEFAULT_TABLE_LENGTH = 16;

public:
	DataTable();
	DataTable(const int tableLength);
	~DataTable();

	void ResetPosition();
	void SetBottomPosition();
	void SetBottomPosition(Node<T>* pTop);
	void SetTotalPageCount();
	void SetCurrentPageCount(bool bNext);
	void MoveCurrentPosition(bool bNext);
	void MoveNextPage(bool bNext);


	int GetDistanceToTail(Node<T>* pCurrentTop);

	void Append(T* data);
	void Append(Node<T>* pNode);
	void AppendAll(DataTable<T>* table);
	void Insert(Node<T>* target, T* data);
	void Insert(Node<T>* target, Node<T>* inserted);
	void InsertAll(Node<T>* target, DataTable<T>* table);
	void Remove(Node<T>* target);
	void RemoveAll();
};

template<class T>
DataTable<T>::DataTable()
{
	pList = new Linkedlist<T>();

	pTopData = nullptr;
	pBottomData = nullptr;
	pCurrentData = nullptr;

	tableLength = DEFAULT_TABLE_LENGTH;
	totalPage = FRONT_PAGE;
	currentPage = FRONT_PAGE;
}
template<class T>
DataTable<T>::DataTable(const int length)
{
	pList = new Linkedlist<T>();

	pTopData = nullptr;
	pBottomData = nullptr;
	pCurrentData = nullptr;

	tableLength = length;
	totalPage = FRONT_PAGE;
	currentPage = FRONT_PAGE;
}
template<class T>
DataTable<T>::~DataTable()
{
	delete pList;

	pList = nullptr;
	pTopData = nullptr;
	pBottomData = nullptr;
	pCurrentData = nullptr;

	tableLength = 0;
	totalPage = 0;
	currentPage = 0;
}

template<class T>
void DataTable<T>::ResetPosition()
{
	if (pList->mpHead == nullptr)
	{
		pTopData = nullptr;
		pBottomData = nullptr;
		pCurrentData = nullptr;

		currentPage = FRONT_PAGE;
		SetTotalPageCount();
		return;
	}

	pTopData = pList->mpHead;
	currentPage = FRONT_PAGE;
	SetBottomPosition();
	SetTotalPageCount();
}
template<class T>
void DataTable<T>::SetBottomPosition()
{
	Node<T>* pTail = pList->mpHead->mpPrev;
	pBottomData = pTopData;

	for (int count = 0; count < tableLength - 1; ++count)
	{
		if (pBottomData == pTail)
		{
			break;
		}

		pBottomData = pBottomData->mpNext;
	}
}

template<class T>
void DataTable<T>::MoveCurrentPosition(bool bNext)
{
	if (bNext && pCurrentData != pList->mpHead->mpPrev)
	{
		if (pCurrentData == pBottomData)
		{
			MoveNextPage(bNext);
		}
		pCurrentData = pCurrentData->mpNext;
	}
	else if (!bNext && pCurrentData != pList->mpHead)
	{
		if (pCurrentData == pTopData)
		{
			MoveNextPage(bNext);
		}

		pCurrentData = pCurrentData->mpPrev;
	}
}
template<class T>
void DataTable<T>::MoveNextPage(bool bNext)
{
	if (bNext && currentPage != tableLength)
	{
		pTopData = pBottomData->mpNext;

		SetBottomPosition();

		++currentPage;
	}
	else if (!bNext && currentPage != FRONT_PAGE)
	{
		pBottomData = pTopData->mpPrev;

		for (int count = 0; count < tableLength; ++count)
		{
			pTopData = pTopData->mpPrev;
		}

		--currentPage;
	}
}

template<class T>
void DataTable<T>::SetTotalPageCount()
{
	int count = pList->GetCount();

	if (count == 0)
	{
		totalPage = FRONT_PAGE;
		return;
	}

	totalPage = (count + tableLength - 1) / tableLength;
}
template<class T>
void DataTable<T>::SetCurrentPageCount(bool bNext)
{
	if (bNext && currentPage != tableLength)
	{
		++currentPage;
	}
	else if (!bNext && currentPage != FRONT_PAGE)
	{
		--currentPage;
	}
}

template<class T>
int DataTable<T>::GetDistanceToTail(Node<T>* pCurrentTop)
{
	if (pCurrentTop == nullptr)
	{
		return -1;
	}

	int distance = 0;
	Node<T>* pTail = pList->mpHead->mpPrev;

	if (pCurrentTop == pTail)
	{
		return distance;
	}

	while (pCurrentTop != pTail && distance < tableLength)
	{
		++distance;
		pCurrentTop = pCurrentTop->mpNext;
	}

	return distance;
}

template<class T>
void DataTable<T>::Append(T* pData)
{
	pList->AddLast(pData);

	if (pCurrentData == nullptr)
	{
		pTopData = pList->mpHead;
		pCurrentData = pTopData;
		pBottomData = pTopData;
	}

	SetBottomPosition();
	SetTotalPageCount();
}
template<class T>
void DataTable<T>::Append(Node<T>* pNode)
{
	pList->AddLast(pNode);

	if (pCurrentData == nullptr)
	{
		pTopData = pList->mpHead;
		pCurrentData = pTopData;
		pBottomData = pTopData;
	}

	SetBottomPosition();
	SetTotalPageCount();
}
template<class T>
void DataTable<T>::AppendAll(DataTable<T>* pTable)
{
	pList->AddLastRange(pTable->pList);

	if (pCurrentData == nullptr)
	{
		pTopData = pList->mpHead;
		pCurrentData = pTopData;
		pBottomData = pTopData;
	}

	SetBottomPosition();
	SetTotalPageCount();
}

template<class T>
void DataTable<T>::Insert(Node<T>* pTarget, T* pData)
{
	if (pTarget == nullptr || pData == nullptr)
	{
		return;
	}

	pList->AddBefore(pTarget, pData);

	pCurrentData = pCurrentData->mpPrev;
	if (pTarget == pTopData)
	{
		pTopData = pCurrentData;
	}

	SetBottomPosition();
	SetTotalPageCount();
}
template<class T>
void DataTable<T>::Insert(Node<T>* pTarget, Node<T>* pInserted)
{
	if (pTarget == nullptr || pInserted == nullptr)
	{
		return;
	}

	pList->AddBefore(pTarget, pInserted);
	
	pCurrentData = pCurrentData->mpPrev;
	if (pTarget == pTopData)
	{
		pTopData = pCurrentData;
	}

	SetBottomPosition();
	SetTotalPageCount();
}
template<class T>
void DataTable<T>::InsertAll(Node<T>* pTarget, DataTable<T>* pTable)
{
	if (pTarget == nullptr || pTable == nullptr || pTable->pList == nullptr || pTable->pList->mpHead == nullptr)
	{
		return;
	}

	Node<T>* temp = pCurrentData->mpPrev;

	pList->AddBeforeRange(pTarget, pTable->pList);

	pCurrentData = temp->mpNext;
	if (temp == pList->mpHead->mpPrev)
	{
		pTopData = pCurrentData;
	}

	SetBottomPosition();
	SetTotalPageCount();
}
template<class T>
void DataTable<T>::Remove(Node<T>* pTarget)
{
	if (pTarget == nullptr || pTarget != pCurrentData)
	{
		return;
	}

	Node<T>* pTail = pList->mpHead->mpPrev;

	if (pTarget->mpNext != pList->mpHead)
	{
		if (pTarget == pTopData)
		{
			pTopData = pTopData->mpNext;
		}

		pCurrentData = pTarget->mpNext;
		SetBottomPosition();
	}
	else if (pTarget->mpPrev != pTail)
	{
		if (pTarget == pTopData)
		{
			for (int count = 0; count < tableLength; ++count)
			{
				pTopData = pTopData->mpPrev;
			}
		}

		pCurrentData = pTarget->mpPrev;
		pBottomData = pCurrentData;

		pList->Remove(pTarget); // 코드중복 수정요망
		SetTotalPageCount();

		currentPage = totalPage;
		return;
	}
	else
	{
		pTopData = nullptr;
		pBottomData = nullptr;
		pCurrentData = nullptr;
	}

	pList->Remove(pTarget);
	SetTotalPageCount();
}
template<class T>
void DataTable<T>::RemoveAll()
{
	pList->Clear();
	pTopData = nullptr;
	pBottomData = nullptr;
	pCurrentData = nullptr;
	ResetPosition();
}