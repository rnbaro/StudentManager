#pragma once
#include <iomanip>
#include <conio.h>
#include <Windows.h> // gotoxy(), SetConsoleCursorPosition()
#include "StudentTable.h"

enum KEY
{
	KEY_DIRECTION = -32,
	KEY_UP        = 72,
	KEY_DOWN      = 80,
	KEY_LEFT      = 75,
	KEY_RIGHT     = 77,

	KEY_LOAD       = '1',
	KEY_SAVE       = '2',
	KEY_CREATE     = '3',
	KEY_APPEND     = '4',
	KEY_APPEND_ALL = '5',
	KEY_INSERT     = '6',
	KEY_INSERT_ALL = '7',
	KEY_DELETE     = '8',
	KEY_DELETE_ALL = '9',
	KEY_QUIT       = '0'
};
class StudentManager
{
public:
	StudentTable* studentTable;
	bool bRun;

	StudentManager();
	~StudentManager();

	void Init();
	void ConsoleDraw();
	void SetCursorPosition(int x, int y);
	void DrawLoadTable();
	void DrawNewTable();
	void DrawPage();
	void SetColor();
	void SetColor(Node<StudentData>* current);
	void InsertController();
};