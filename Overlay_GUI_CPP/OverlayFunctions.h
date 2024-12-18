#pragma once

#include "framework.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void AddCircle(HWND hWnd);
void AddSquare(HWND hWnd);
void LockOverlay(HWND hWnd);
void StartKeylogging(HWND hWnd);
void StopKeylogging();