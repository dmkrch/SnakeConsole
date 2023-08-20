#include "MapHolder.h"

#include <windows.h>
#include <stdio.h>

MapHolder::MapHolder(int xSize, int ySize)
{

}

void MapHolder::MoveSnake(const MovementDirection & direction)
{
	m_snake.Move(direction);
	PrintSnake();
}

void MapHolder::PrintObjectsOnMap()
{
	int x = 0;
	int y = 0;
	char ch = '*';

	for (const auto & obj : m_objects)
	{
		x = obj->GetX();
		y = obj->GetY();

		if (!obj)
		{
			switch (obj->GetType())
			{
			case ObjectType::Food:
				ch = '1';
				break;
			case ObjectType::SnakeCell:
				ch = '*';
				break;
			default:
				return;
			}

			// now print in x, y coordinates of terminal ch character
			PrintCharacter(x, y, ch);
		}
	}
}

void MapHolder::PrintSnake()
{
	m_snake.ForEachCellInclHead([this](const SnakeCell& cell)
	{
		PrintCharacter(cell.GetX(), cell.GetY(), '*');
	});
}

void MapHolder::PrintCharacter(int xCoord, int yCoord, char ch)
{
	HANDLE screenBuffer = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL);

	if (screenBuffer == INVALID_HANDLE_VALUE)
	{
		printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
		return;
	}

	if (!SetConsoleActiveScreenBuffer(screenBuffer))
	{
		printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
		CloseHandle(screenBuffer);
		return;
	}

	const char* charact = &ch;
	DWORD numCharsWritten;
	WriteConsoleOutputCharacter(screenBuffer, LPCWSTR(charact), 1, COORD{short(xCoord), short(yCoord)}, &numCharsWritten);
}
