#ifndef INCLUDES_H
#define INCLUDES_H

#include <windows.h>
#include <tchar.h>
#include <math.h>
#include <stdlib.h>

#define ID_CLOSE 100001

typedef struct 
{
	double x;
	double y;
} Point;

typedef struct 
{
	Point squarePoints[4];
	COLORREF squareColor;
} Square;
typedef DWORD COLORREF;


#endif // !INCLUDES_H


