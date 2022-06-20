#pragma once
#include <iostream>
using namespace std;
//#include "Node.h"
//#include "LinkedList.h"
//#include "DataTable.h"
//#include "StudentTable.h"
#include "StudentManager.h"


struct TData
{
	int a;
	int b;
};

class TestCase
{
public:
	void Test_Linkedlist()
	{
		Linkedlist<TData>* tList = new Linkedlist<TData>();

		TData* a1 = new TData({ 1, 2 });
		TData* a2 = new TData({ 3, 4 });
		TData* a3 = new TData({ 5, 6 });
		TData* a4 = new TData({ 7, 8 });
		TData* a5 = new TData({ 9, 10 });

		tList->AddFirst(a1);
		tList->AddFirst(a2);
		tList->AddFirst(a3);
		tList->AddFirst(a4);
		tList->AddFirst(a5);

		int dataCount = tList->GetCount();

		Linkedlist<TData>* added = new Linkedlist<TData>();

		TData* b1 = new TData({ 11, 12 });
		TData* b2 = new TData({ 13, 14 });
		TData* b3 = new TData({ 15, 16 });
		TData* b4 = new TData({ 17, 18 });

		added->AddLast(b1);
		added->AddLast(b2);
		added->AddLast(b3);
		added->AddLast(b4);

		tList->AddLastRange(added);

		dataCount = tList->GetCount();

		int tIndex;
		tIndex = tList->GetIndex(tList->mpHead);
		tIndex = tList->GetIndex(tList->mpHead->mpNext);
		tIndex = tList->GetIndex(tList->mpHead->mpNext->mpNext);
		tIndex = tList->GetIndex(tList->mpHead->mpNext->mpNext->mpNext);
		tIndex = tList->GetIndex(tList->mpHead->mpNext->mpNext->mpNext->mpNext);
		tIndex = tList->GetIndex(tList->mpHead->mpNext->mpNext->mpNext->mpNext->mpNext);
		tIndex = tList->GetIndex(tList->mpHead->mpNext->mpNext->mpNext->mpNext->mpNext->mpNext);
		tIndex = tList->GetIndex(tList->mpHead->mpNext->mpNext->mpNext->mpNext->mpNext->mpNext->mpNext);
		tIndex = tList->GetIndex(tList->mpHead->mpNext->mpNext->mpNext->mpNext->mpNext->mpNext->mpNext->mpNext);

		TData* t1 = new TData({ 99, 99 });
		Node<TData>* tn1 = new Node<TData>();
		tn1->mpData = t1;

		tIndex = tList->GetIndex(tn1);

		tList->Clear();

		delete tList;
	}
	void Test_DataTable()
	{
		// Append() and Remove() at last index test
		{
			DataTable<TData>* tTable = new DataTable<TData>();

			for (int i = 0; i < 25; ++i)
			{
				tTable->Append(new TData{ i, i + 1 });
			}

			tTable->ResetPosition();

			// when defalutLength = 16
			for (int i = 0; i < 16; ++i)
			{
				tTable->MoveCurrentPosition(true);  // test MoveNextPage(true) next
			}
			for (int i = 0; i < 10; ++i)
			{
				tTable->MoveCurrentPosition(true);  // test move current when last page
			}
			for (int i = 0; i < 10; ++i)
			{
				tTable->MoveCurrentPosition(false); // test MoveNextPage(false) previous
			}
			for (int i = 0; i < 16; ++i)
			{
				tTable->MoveCurrentPosition(false); // test move current when first page
			}

			for (int i = 0; i < 26; ++i)
			{
				tTable->Remove(tTable->pCurrentData);
			}

			for (int i = 0; i < 25; ++i)
			{
				tTable->Append(new TData{ i, i + 1 });
			}

			delete tTable;
		}

		// Remove() at middel index test
		{
			DataTable<TData>* tTable = new DataTable<TData>(12);
			for (int i = 0; i < 25; ++i)
			{
				tTable->Append(new TData{ i, i + 1 });
			}
			tTable->ResetPosition();

			for (int i = 0; i < 12; ++i)
			{
				tTable->MoveCurrentPosition(true);  // test MoveNextPage(true) next
			}
			for (int i = 0; i < 14; ++i)
			{
				tTable->MoveCurrentPosition(true);  // test move current when last page
			}

			for (int i = 0; i < 26; ++i)
			{
				tTable->Remove(tTable->pCurrentData);
			}

			for (int i = 0; i < 25; ++i)
			{
				tTable->Append(new TData{ i, i + 1 });
			}
			for (int i = 0; i < 12; ++i)
			{
				tTable->MoveCurrentPosition(true);  // test Remove() at middle index
			}

			for (int i = 0; i < 26; ++i)
			{
				tTable->Remove(tTable->pCurrentData);
			}

			delete tTable;
		}

		// Insert() test
		{
			DataTable<TData>* tTable = new DataTable<TData>(12);

			for (int i = 0; i < 25; ++i)
			{
				tTable->Append(new TData{ i, i + 1 });
			}

			for (int i = 0; i < 12; ++i)
			{
				tTable->MoveCurrentPosition(true);  // test Remove() at middle index
			}

			for (int i = 0; i < 25; ++i)
			{
				tTable->Insert(tTable->pCurrentData, new TData{ i + 100, i + 101 });
			}
		}

	}
	void Test_StudentTable()
	{
		StudentTable tTable;
		
		for (int i = 0; i < 18; ++i)
		{
			tTable.Create();
		}
		
		tTable.AppendAll();

		tTable.Save(); // "test0.txt"

		for (int i = 0; i < 17; ++i)
		{
			tTable.Create();
		}

		tTable.loadDataTable->ResetPosition();
		tTable.InsertAll(tTable.loadDataTable->pCurrentData);

		tTable.Save(); // "test1.txt"


		tTable.DeleteAll();


		tTable.Load();
		for (int i = 0; i < 18; ++i)
		{
			tTable.Create();
		}

		tTable.MoveCurrent(DIRECTION_UP);

		tTable.MoveCurrent(DIRECTION_RIGHT);
		tTable.MoveCurrent(DIRECTION_RIGHT);

		tTable.MoveCurrent(DIRECTION_LEFT);
		tTable.MoveCurrent(DIRECTION_LEFT);

		for (int i = 0; i < 38; ++i)
		{
			tTable.MoveCurrent(DIRECTION_DOWN);
		}

		tTable.MoveCurrent(DIRECTION_RIGHT);
		tTable.MoveCurrent(DIRECTION_UP);

		for (int i = 0; i < 19; ++i)
		{
			tTable.MoveCurrent(DIRECTION_DOWN);
		}
		for (int i = 0; i < 19; ++i)
		{
			tTable.MoveCurrent(DIRECTION_UP);
		}

		tTable.DeleteAll(); // test pCurrent move next
		tTable.DeleteAll(); // test pCurrent being nullptr
	}

	void Test_StudentManager()
	{
		StudentManager* tManager = new StudentManager();

		tManager->Init();
	}
};