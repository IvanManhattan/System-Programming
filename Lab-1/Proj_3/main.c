#include "Includes.h"
#include "FigureDrawer.h"
#include "FigureMover.h"

// Values
ACCEL accelTable[] = {
    { FVIRTKEY | FCONTROL, 'X', ID_CLOSE },
};

float angle = 0.01f;

Point points[4] = 
{
    {100, 100},
    {100, 200},
    {200, 200},
    {200, 100},
};

COLORREF squareColor;
Square mySquare;

// Functions
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam);
int MessageBoxQuit(HWND hwnd);
void initializeSquare();

// Code
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    HWND hwnd; 
    MSG msg; 
    WNDCLASS w; 
    HACCEL haccelTable;

    memset(&w, 0, sizeof(WNDCLASS));
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.lpfnWndProc = WndProc; 
    w.hInstance = hInstance;
    w.hbrBackground = (HBRUSH)(WHITE_BRUSH);
    w.lpszClassName = _T("My Class");
    RegisterClass(&w);
    initializeSquare();

    hwnd = CreateWindow(_T("My Class"), _T("Window"),
        WS_OVERLAPPEDWINDOW, 200, 200, 800, 600, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow); 
    haccelTable = CreateAcceleratorTable(accelTable, ARRAYSIZE(accelTable));
    UpdateWindow(hwnd);   

    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!TranslateAccelerator(hwnd, haccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam)
{
	switch (Message) {
    case WM_COMMAND:
    case ID_CLOSE:
    {
        if (MessageBoxQuit(hwnd) == IDYES) 
        {
            PostQuitMessage(0);
        }
        break;
    }
    break;
    case WM_PAINT:
    {
        
        PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		HBRUSH hBrush = (HBRUSH)(COLOR_WINDOW + 1); 
		FillRect(hdc, &ps.rcPaint, hBrush);

		DrawSquare(hdc, mySquare);
		EndPaint(hwnd, &ps);
		break;
        
		
	} 
	case WM_KEYDOWN: 
    {
		if (wparam == 'A') 
        {
			MoveSquare(mySquare.squarePoints, -10, TRUE);
		}
		if (wparam == 'D') 
        {
			MoveSquare(mySquare.squarePoints, 10, TRUE);
		}
		if (wparam == 'W') 
        {
			MoveSquare(mySquare.squarePoints, -10, FALSE);
		}
		if (wparam == 'S') 
        {
			MoveSquare(mySquare.squarePoints, 10, FALSE);
		}
		if (wparam == 'E') 
        {
			Point temp;
			temp.x = (mySquare.squarePoints[0].x + mySquare.squarePoints[2].x) / 2;
			temp.y = (mySquare.squarePoints[0].y + mySquare.squarePoints[2].y) / 2;
			for (int i = 0; i < 4; i++) 
                mySquare.squarePoints[i] = rotateSquareMatrix(mySquare.squarePoints[i], temp, -angle);
		}
		if (wparam == 'Q')
        {
			Point temp;
			temp.x = (mySquare.squarePoints[0].x + mySquare.squarePoints[2].x) / 2;
			temp.y = (mySquare.squarePoints[0].y + mySquare.squarePoints[2].y) / 2;
			for (int i = 0; i < 4; i++) 
                mySquare.squarePoints[i] = rotateSquareMatrix(mySquare.squarePoints[i], temp, angle);
		}
        if (wparam == 'Z')
        {
            mySquare.squareColor = RGB(rand() % 256, rand() % 256, rand() % 256);
        }
		InvalidateRect(hwnd, NULL, TRUE); 
		if (wparam == 'M' || wparam == 'N') 
        {

			BOOLEAN isOPressed = (GetAsyncKeyState('M') & 0x8000) != 0;
			BOOLEAN isPPressed = (GetAsyncKeyState('N') & 0x8000) != 0;

			if (isOPressed && isPPressed) {
                if (MessageBoxQuit(hwnd) == IDYES)
                {
                    PostQuitMessage(0);
                }
			}
		}
		if (wparam == VK_ESCAPE) 
        {
            if (MessageBoxQuit(hwnd) == IDYES)
            {
                PostQuitMessage(0);
            }
		}
	} break;

	case WM_MOUSEWHEEL: 
    {

		if ((GetAsyncKeyState(VK_MENU) & 0x8000))
        {
			MoveSquare(mySquare.squarePoints, GET_WHEEL_DELTA_WPARAM(wparam) > 0 ? +10 : -10, TRUE);
		}
		else 
        {
			MoveSquare(mySquare.squarePoints, GET_WHEEL_DELTA_WPARAM(wparam) > 0 ? +10 : -10, FALSE);
		}

		InvalidateRect(hwnd, NULL, TRUE); 
	} break;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		return DefWindowProc(hwnd, Message, wparam, lparam);
	}
}

int MessageBoxQuit(HWND hwnd)
{
    int msgboxID;
        
    msgboxID = MessageBox
    (
        hwnd,
        _T("Close the app?"),
        _T("Exit?"),
        MB_YESNO | MB_ICONQUESTION
    );
    return msgboxID;

}

void initializeSquare()
{
    for (int i = 0; i < 4; i++)
    {
        mySquare.squarePoints[i] = points[i];
    }
    mySquare.squareColor = squareColor;
}
