#pragma once
#include <iostream>
#include "StudentData.h"
#include "DataTable.h"
using namespace std;

enum DIRECTION
{
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT
};

class StudentTable
{
public:
	DataTable<StudentData>* loadDataTable;
	DataTable<StudentData>* newDataTable;
	Node<StudentData>* pCurrent;

	unsigned char  buffer[1024];
	unsigned char* pChar;

public:
	StudentTable();
	~StudentTable();

	void Load();
	void Save();
	void Create();
	void Append();
	void AppendAll();
	void Insert(Node<StudentData>* pTarget);
	void InsertAll(Node<StudentData>* pTarget);
	void Delete(Node<StudentData>* pTarget);
	void DeleteAll();

	void SetCurrent(bool bRoadTable);
	void MoveCurrent(DIRECTION direction);
};