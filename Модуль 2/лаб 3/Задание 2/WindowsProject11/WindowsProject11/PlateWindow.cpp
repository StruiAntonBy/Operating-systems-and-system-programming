#include "PlateWindow.h"
#include "board.h"

int RegisterPlateWindow(){
    WNDCLASS wcl;
    wcl.hInstance = GetModuleHandle(NULL);
    wcl.lpszClassName = L"PlateWindowClass";
    wcl.lpfnWndProc = PlateWindowProc;
    wcl.style = CS_HREDRAW | CS_VREDRAW;
    wcl.lpszMenuName = NULL;
    wcl.hIcon = NULL;
    wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcl.hbrBackground = (HBRUSH)(1 + COLOR_WINDOW);
    wcl.cbClsExtra = 0;
    wcl.cbWndExtra = 0;
    return RegisterClass(&wcl);
}

LRESULT CALLBACK PlateWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    static Board board(40);
    static int figure = 0;
    
    MouseState ms;
    ExtractMouseParams(wParam, lParam, &ms);

    switch (uMsg){
        case WM_PAINT:{
            PAINTSTRUCT ps;
            HDC hDC = BeginPaint(hWnd, &ps);  
            board.Draw(hDC);                  
            EndPaint(hWnd, &ps);             
            break;
        }
        case WM_LBUTTONDOWN:{
            HDC hdc = GetWindowDC(hWnd);
            if (figure!=0 && board.setFigure(hdc, ms.xPos, ms.yPos, figure)) {
                figure = 0;
            }
            else if(figure==0){
                switch (board.takeFigure(hdc, ms.xPos, ms.yPos)) {
                case 0:
                    break;
                case 1:
                    figure = 1;
                    break;
                case 2:
                    figure = 2;
                    break;
                }
            }
            ReleaseDC(hWnd, hdc);
            break;
        }
    case WM_RBUTTONDOWN:{
        HDC hdc = GetWindowDC(hWnd);
        if (figure!=0) {
            figure = 0;
        }
        else {
            board.deleteFigure(hdc, ms.xPos, ms.yPos);
        }
        ReleaseDC(hWnd, hdc);
        break;
    }
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}

void ExtractMouseParams(WPARAM wParam, LPARAM lParam, MouseState* ms) {
    ms->xPos = LOWORD(lParam);
    ms->yPos = HIWORD(lParam);

    ms->lButtonPressed = (wParam & MK_LBUTTON) != 0;
    ms->rButtonPressed = (wParam & MK_RBUTTON) != 0;
    ms->mButtonPressed = (wParam & MK_MBUTTON) != 0;
    ms->shiftPressed = (wParam & MK_SHIFT) != 0;
    ms->controlPressed = (wParam & MK_CONTROL) != 0;
}