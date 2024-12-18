#pragma once

#include "resource.h"

// ...existing code...
void                AddSquare(HWND hWnd);
void                LockOverlay(HWND hWnd);
// ...existing code...

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void                AddCircle(HWND hWnd);

// ...existing code...
