#include "FigureDrawer.h"

void DrawSquare(HDC hdc, Square square)
{
    POINT temp[4];
    for (int i = 0; i < 4; i++)
    {
        temp[i].x = square.squarePoints[i].x;
        temp[i].y = square.squarePoints[i].y;
    }
    //srand((unsigned int)time(NULL)); 
    //COLORREF randomColor = RGB(rand() % 256, rand() % 256, rand() % 256);

    HBRUSH hBrush = CreateSolidBrush(square.squareColor);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    Polygon(hdc, temp, 4);

    SelectObject(hdc, hOldBrush);
    DeleteObject(hBrush);
}