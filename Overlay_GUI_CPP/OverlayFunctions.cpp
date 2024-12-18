#include "framework.h"
#include "OverlayFunctions.h"
#include "Resource.h"

// Ensure hInst is declared as an external variable
extern HINSTANCE hInst;

void AddCircle(HWND hWnd) {
    // Implementation for adding a circle
    MessageBox(hWnd, L"Circle added!", L"Info", MB_OK);
}

void AddSquare(HWND hWnd) {
    // Implementation for adding a square
    HDC hdc = GetDC(hWnd);
    RECT rect;
    GetClientRect(hWnd, &rect);
    Rectangle(hdc, rect.left + 50, rect.top + 50, rect.left + 150, rect.top + 150);
    ReleaseDC(hWnd, hdc);
}

void LockOverlay(HWND hWnd) {
    // Implementation for locking the overlay
    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    MessageBox(hWnd, L"Overlay locked!", L"Info", MB_OK);
}
