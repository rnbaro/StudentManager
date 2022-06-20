#include "StudentManager.h"

StudentManager::StudentManager()
{
	studentTable = new StudentTable();
	bRun = true;
}

StudentManager::~StudentManager()
{
	delete studentTable;
	bRun = false;
}

void StudentManager::Init()
{
	while (bRun)
	{
		ConsoleDraw();

		char key = _getch();
		if (key == KEY_DIRECTION)
		{
			key = _getch();

			switch (key)
			{
			case KEY_UP:
				studentTable->MoveCurrent(DIRECTION_UP);
				break;
			case KEY_DOWN:
				studentTable->MoveCurrent(DIRECTION_DOWN);
				break;
			case KEY_LEFT:
				studentTable->MoveCurrent(DIRECTION_LEFT);
				break;
			case KEY_RIGHT:
				studentTable->MoveCurrent(DIRECTION_RIGHT);
				break;
			default:
				break;
			}
		}
		else if (key >= '0' && key <= '9')
		{
			switch (key)
			{
			case KEY_LOAD:
				studentTable->Load();
				break;
			case KEY_SAVE:
				studentTable->Save();
				break;
			case KEY_CREATE:
				studentTable->Create();
				break;
			case KEY_APPEND:
				studentTable->Append();
				break;
			case KEY_APPEND_ALL:
				studentTable->AppendAll();
				break;
			case KEY_INSERT:
				if (studentTable->loadDataTable->pCurrentData == nullptr || studentTable->pCurrent != studentTable->newDataTable->pCurrentData)
				{
					break;
				}
				InsertController();
				studentTable->Insert(studentTable->pCurrent);
				break;
			case KEY_INSERT_ALL:
				if (studentTable->loadDataTable->pCurrentData == nullptr || studentTable->pCurrent != studentTable->newDataTable->pCurrentData)
				{
					break;
				}
				InsertController();
				studentTable->InsertAll(studentTable->pCurrent);
				break;
			case KEY_DELETE:
				studentTable->Delete(studentTable->pCurrent);
				break;
			case KEY_DELETE_ALL:
				studentTable->DeleteAll();
				break;
			case KEY_QUIT:
				bRun = false;
				break;
			default:
				_ASSERT(false);
				break;
			}
		}
	}
}

void StudentManager::ConsoleDraw()
{
	// total length : 100
	//                                                        == middle of line 
	system("cls");

	cout << endl;
	cout << " ====================================================================================================" << endl;
	cout << " =                                      STUDENT MANAGE PROGRAM                                      =" << endl;
	cout << " ====================================================================================================" << endl;
	cout << " =                ROAD DATA TABLE                 ==                 NEW DATA TABLE                 =" << endl;
	cout << " ====================================================================================================" << endl;
	cout << " =  INDEX   NAME  KOR ENG MATH    TOTAL  AVERAGE  ==  INDEX   NAME  KOR ENG MATH    TOTAL  AVERAGE  =" << endl;
	cout << " ====================================================================================================" << endl;
	for (int i = 0; i < 17; ++i)
	{
		cout << " =                                                ==                                                =" << endl;

	}
	cout << " ====================================================================================================" << endl;
	cout << " =     1) LOAD   2) SAVE   3) CREATE   4) APPEND       6) INSERT       8) DELETE       0) QUIT      =" << endl;
	cout << " =                                     5) APPEND ALL   7) INSERT ALL   9) DELETE ALL                =" << endl;
	cout << " ====================================================================================================" << endl;

	DrawLoadTable();
	DrawNewTable();
	DrawPage();
}

void StudentManager::InsertController()
{
	studentTable->MoveCurrent(DIRECTION_LEFT);
	ConsoleDraw();

	char key = _getch();
	while (key != '\r')
	{
		if (key == KEY_DIRECTION)
		{
			key = _getch();

			switch (key)
			{
			case KEY_UP:
				studentTable->MoveCurrent(DIRECTION_UP);
				break;
			case KEY_DOWN:
				studentTable->MoveCurrent(DIRECTION_DOWN);
				break;
			default:
				break;
			}
		}

		ConsoleDraw();
		key = _getch();
	}
}


void StudentManager::SetCursorPosition(int x, int y)
{
	COORD position = { (short)x, (short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
void StudentManager::SetColor()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 | (0 << 4));
}
void StudentManager::SetColor(Node<StudentData>* current)
{
	if (current == studentTable->pCurrent)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | (15 << 4));
	}
	else if (current == studentTable->loadDataTable->pCurrentData || current == studentTable->newDataTable->pCurrentData)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | (8 << 4));
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 | (0 << 4));
	}
}


void StudentManager::DrawLoadTable()
{
	if (studentTable->loadDataTable->pCurrentData == nullptr)
	{
		return;
	}

	int index = 1 + (studentTable->loadDataTable->currentPage - 1) * 16;
	int count = 0;

	Node<StudentData>* currentLoad = studentTable->loadDataTable->pTopData;
	Node<StudentData>* head = studentTable->loadDataTable->pList->mpHead;

	do
	{
		StudentData* current = currentLoad->mpData;
		SetCursorPosition(4, 8 + count);
		SetColor(currentLoad);
		cout << setw(5) << index++
			<< setw(7) << current->name
			<< setw(5) << current->scoreKor
			<< setw(4) << current->scoreEng
			<< setw(5) << current->scoreMath
			<< setw(9) << current->scoreTotal
			<< setw(9) << setprecision(2) << current->scoreAverage << endl;

		currentLoad = currentLoad->mpNext;
	} while (++count < 16 && currentLoad != head);

	SetColor();
}
void StudentManager::DrawNewTable()
{
	if (studentTable->newDataTable->pCurrentData == nullptr)
	{
		return;
	}

	int index = 1 + (studentTable->newDataTable->currentPage - 1) * 16;
	int count = 0;

	Node<StudentData>* currentNew = studentTable->newDataTable->pTopData;
	Node<StudentData>* head = studentTable->newDataTable->pList->mpHead;

	do
	{
		StudentData* current = currentNew->mpData;
		SetCursorPosition(54, 8 + count);
		SetColor(currentNew);
		cout << setw(5) << index++
			<< setw(7) << current->name
			<< setw(5) << current->scoreKor
			<< setw(4) << current->scoreEng
			<< setw(5) << current->scoreMath
			<< setw(9) << current->scoreTotal
			<< setw(9) << setprecision(2) << current->scoreAverage << endl;

		currentNew = currentNew->mpNext;
	} while (++count < 16 && currentNew != head);

	SetColor();
}
void StudentManager::DrawPage()
{
	int loadCurrent = studentTable->loadDataTable->currentPage;
	int loadTotal = studentTable->loadDataTable->totalPage;
	int newCurrent = studentTable->newDataTable->currentPage;
	int newTotal = studentTable->newDataTable->totalPage;

	SetCursorPosition(23, 24);
	cout << setw(2) << loadCurrent << " / " << setw(2) << loadTotal;
	SetCursorPosition(73, 24);
	cout << setw(2) << newCurrent << " / " << setw(2) << newTotal;
}