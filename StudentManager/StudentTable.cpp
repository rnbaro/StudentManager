#include <string.h>
#include "StudentTable.h"

StudentTable::StudentTable()
{
	loadDataTable = new DataTable<StudentData>();
	newDataTable = new DataTable<StudentData>();
	pCurrent = nullptr;
	memset(buffer, 0, sizeof(buffer) / sizeof(char));
	pChar = nullptr;
}

StudentTable::~StudentTable()
{
	delete loadDataTable;
	delete newDataTable;
	pCurrent = nullptr;
	memset(buffer, 0, sizeof(char) * 1024);
	pChar = nullptr;
}

void StudentTable::Save()
{
	FILE* fpWrite;

	if (fopen_s(&fpWrite, "test.txt", "w+b"))
	{
		return;
	}

	if (loadDataTable->pList->mpHead == nullptr)
	{
		fclose(fpWrite);
		return;
	}

	Node<StudentData>* current = loadDataTable->pList->mpHead;

	pChar = (unsigned char*)&loadDataTable->pList->mCount;
	int count = sizeof(int) / sizeof(char);
	for (int i = 0; i < count; ++i)
	{
		buffer[i] = pChar[i];
	}

	fwrite(buffer, sizeof(int), 1, fpWrite);

	do
	{
		pChar = (unsigned char*)current->mpData;
		int count = sizeof(StudentData) / sizeof(char);

		for (int i = 0; i < count; ++i)
		{
			buffer[i] = pChar[i];
		}

		fwrite(buffer, sizeof(StudentData), 1, fpWrite);
		current = current->mpNext;

	} while (current != loadDataTable->pList->mpHead);

	fclose(fpWrite);
}
void StudentTable::Load()
{
	if (loadDataTable->pCurrentData != nullptr)
	{
		pCurrent = loadDataTable->pCurrentData;
		DeleteAll();
	}

	FILE* fpRead;

	if (fopen_s(&fpRead, "test.txt", "r+b"))
	{
		return;
	}

	memset(buffer, 0, sizeof(buffer) / sizeof(char));

	int dataSize = sizeof(StudentData) / sizeof(char);
	int count;
	fread(buffer, sizeof(int), 1, fpRead);
	_memccpy(&count, buffer, 1, sizeof(int));
	memset(buffer, 0, sizeof(buffer) / sizeof(char));

	for (int i = 0; i < count; ++i)
	{
		fread(buffer, sizeof(StudentData), 1, fpRead);

		StudentData* newData = new StudentData;
		memset(newData, 0, sizeof(StudentData));

		pChar = (unsigned char*)newData;

		for (int i = 0; i < dataSize; ++i)
		{
			pChar[i] = buffer[i];
		}

		loadDataTable->Append(newData);
		memset(buffer, 0, sizeof(buffer) / sizeof(char));
	}

	fclose(fpRead);
	loadDataTable->ResetPosition();
	pCurrent = loadDataTable->pCurrentData;
}

void StudentTable::Create()
{
	StudentData* newData = new StudentData;
	memset(newData, 0, sizeof(StudentData));

	char temp[3] = { 0, };
	temp[0] = 65 + rand() % 26;
	temp[1] = 65 + rand() % 26;
	temp[2] = 65 + rand() % 26;
	strncpy_s(newData->name, temp, sizeof(char) * 3);

	newData->scoreKor = rand() % 101;
	newData->scoreEng = rand() % 101;
	newData->scoreMath = rand() % 101;
	newData->scoreTotal = newData->scoreKor + newData->scoreEng + newData->scoreMath;
	newData->scoreAverage = newData->scoreTotal / 3.0f;

	newDataTable->Append(newData);

	newDataTable->MoveCurrentPosition(true);

	pCurrent = newDataTable->pCurrentData;
}
void StudentTable::Append()
{
	if (newDataTable->pCurrentData == nullptr)
	{
		return;
	}

	Node<StudentData>* newTableNode = newDataTable->pCurrentData;

	StudentData* newData = new StudentData;
	memcpy(newData, newTableNode->mpData, sizeof(StudentData));
	loadDataTable->Append(newData);
	newDataTable->Remove(newTableNode);

	SetCurrent(false);
}

void StudentTable::AppendAll()
{
	if (newDataTable->pCurrentData == nullptr || newDataTable->pList == nullptr || newDataTable->pList->mpHead == nullptr)
	{
		return;
	}

	loadDataTable->AppendAll(newDataTable);
	newDataTable->ResetPosition();

	SetCurrent(true);
}
void StudentTable::Insert(Node<StudentData>* pTarget)
{
	if (pTarget != loadDataTable->pCurrentData || newDataTable->pCurrentData == nullptr)
	{
		return;
	}

	Node<StudentData>* newTableNode = newDataTable->pCurrentData;

	StudentData* newData = new StudentData;
	memcpy(newData, newTableNode->mpData, sizeof(StudentData));
	loadDataTable->Insert(pTarget, newData);
	newDataTable->Remove(newTableNode);

	pCurrent = loadDataTable->pCurrentData;
}

void StudentTable::InsertAll(Node<StudentData>* pTarget)
{
	if (pTarget != loadDataTable->pCurrentData || newDataTable->pCurrentData == nullptr || newDataTable->pList == nullptr || newDataTable->pList->mpHead == nullptr)
	{
		return;
	}
	loadDataTable->InsertAll(pTarget, newDataTable);
	newDataTable->ResetPosition();

	pCurrent = loadDataTable->pCurrentData;
}
void StudentTable::Delete(Node<StudentData>* pTarget)
{
	if (pCurrent == loadDataTable->pCurrentData)
	{
		loadDataTable->Remove(loadDataTable->pCurrentData);
		SetCurrent(true);
	}
	else if (pCurrent == newDataTable->pCurrentData)
	{
		newDataTable->Remove(newDataTable->pCurrentData);
		SetCurrent(false);
	}
}
void StudentTable::DeleteAll()
{
	if (pCurrent == loadDataTable->pCurrentData)
	{
		loadDataTable->RemoveAll();
		SetCurrent(false);
	}
	else if (pCurrent == newDataTable->pCurrentData)
	{
		newDataTable->RemoveAll();
		SetCurrent(true);
	}
}

void StudentTable::SetCurrent(bool bLoadTable)
{
	if (bLoadTable)
	{
		if (loadDataTable->pCurrentData != nullptr)
		{
			pCurrent = loadDataTable->pCurrentData;
		}
		else if (newDataTable->pCurrentData != nullptr)
		{
			pCurrent = newDataTable->pCurrentData;
		}
		else
		{
			pCurrent = nullptr;
		}
	}
	else
	{
		if (newDataTable->pCurrentData != nullptr)
		{
			pCurrent = newDataTable->pCurrentData;
		}
		else if (loadDataTable->pCurrentData != nullptr)
		{
			pCurrent = loadDataTable->pCurrentData;
		}
		else
		{
			pCurrent = nullptr;
		}
	}
}

void StudentTable::MoveCurrent(DIRECTION direction)
{
	if (pCurrent == nullptr)
	{
		return;
	}

	switch (direction)
	{
	case DIRECTION_UP:
		if (pCurrent == loadDataTable->pCurrentData)
		{
			loadDataTable->MoveCurrentPosition(false);
			pCurrent = loadDataTable->pCurrentData;
		}
		else
		{
			newDataTable->MoveCurrentPosition(false);
			pCurrent = newDataTable->pCurrentData;
		}
		break;

	case DIRECTION_DOWN:
		if (pCurrent == loadDataTable->pCurrentData)
		{
			loadDataTable->MoveCurrentPosition(true);
			pCurrent = loadDataTable->pCurrentData;
		}
		else
		{
			newDataTable->MoveCurrentPosition(true);
			pCurrent = newDataTable->pCurrentData;
		}
		break;

	case DIRECTION_LEFT:
		if (loadDataTable->pCurrentData != nullptr && pCurrent == newDataTable->pCurrentData)
		{
			pCurrent = loadDataTable->pCurrentData;
		}
		break;
	case DIRECTION_RIGHT:
		if (newDataTable->pCurrentData != nullptr && pCurrent == loadDataTable->pCurrentData)
		{
			pCurrent = newDataTable->pCurrentData;
		}
		break;
	default:
		_ASSERT(false);
		break;
	}
}
