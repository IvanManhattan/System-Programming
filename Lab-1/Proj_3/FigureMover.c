#include "FigureMover.h"

Point rotateSquareMatrix(Point currentPoint, Point center, float angle)
{
    double cosA = cos(angle);
    double sinA = sin(angle);

    // —мещение точки относительно центра
    double deltaX = currentPoint.x - center.x;
    double deltaY = currentPoint.y - center.y;

    // ѕрименение матрицы поворота
    double rotatedX = (deltaX * cosA) + (deltaY * sinA);
    double rotatedY = (deltaX * -sinA) + (deltaY * cosA);

    // —мещение обратно к оригинальному положению
    Point relativeCentreDisplacementPoint;
    relativeCentreDisplacementPoint.x = rotatedX + center.x;
    relativeCentreDisplacementPoint.y = rotatedY + center.y;

    return relativeCentreDisplacementPoint;
}

void MoveSquare(Point* points, int val, BOOLEAN dir)
{
    if (dir)
    {
        for (int i = 0; i < 4; i++)
        {
            points[i].x += val;
        }
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            points[i].y += val;
        }
    }
    return;
}