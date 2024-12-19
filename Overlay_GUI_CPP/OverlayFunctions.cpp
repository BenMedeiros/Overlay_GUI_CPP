#include "framework.h"
#include "OverlayFunctions.h"
#include "Resource.h"
#include <random>

// Ensure hInst is declared as an external variable
extern HINSTANCE hInst;
HHOOK keyboardHook = NULL;

// Function to add a circle to the overlay
void AddCircle(HWND hWnd)
{
    // Implementation for adding a circle
    MessageBox(hWnd, L"Circle added!", L"Info", MB_OK);
}

// Function to add a square to the overlay
void AddSquare(HWND hWnd)
{
    // Implementation for adding a square
    HDC hdc = GetDC(hWnd);
    RECT rect;
    GetClientRect(hWnd, &rect);
    Rectangle(hdc, rect.left + 50, rect.top + 50, rect.left + 150, rect.top + 150);
    ReleaseDC(hWnd, hdc);
}

// Function to lock the overlay in place
void LockOverlay(HWND hWnd)
{
    // Implementation for locking the overlay
    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    MessageBox(hWnd, L"Overlay locked!", L"Info", MB_OK);
}

// Function to start keylogging
void StartKeylogging(HWND hWnd)
{
    // Implementation for starting keylogging
    MessageBox(hWnd, L"Keylogging started!", L"Info", MB_OK);
    OutputDebugString(L"Keylogging has been initiated.\n");
    OutputDebugString(L"Attempting to set keyboard hook...\n");
    // Hook for keyboard events
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, [](int nCode, WPARAM wParam, LPARAM lParam) -> LRESULT
    {
        OutputDebugString(L"Keyboard hook triggered.\n");
        wchar_t wParamBuffer[256];
        wsprintf(wParamBuffer, L"wParam: %lld\n", static_cast<long long>(wParam));
        OutputDebugString(wParamBuffer);

        wchar_t lParamBuffer[256];
        wsprintf(lParamBuffer, L"lParam: %ld\n", lParam);
        OutputDebugString(lParamBuffer);
        
        if (nCode == HC_ACTION) {
            KBDLLHOOKSTRUCT* pKeyboard = (KBDLLHOOKSTRUCT*)lParam;
			
            if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
                wchar_t buffer[256];
                wsprintf(buffer, L"Key Pressed: %d", pKeyboard->vkCode);
                OutputDebugString(buffer);
                // MessageBox(NULL, buffer, L"Key Press", MB_OK);
            }
        }
        return CallNextHookEx(NULL, nCode, wParam, lParam); 
    }, hInst, 0);

    if (keyboardHook == NULL) {
        DWORD error = GetLastError();
        wchar_t errorMsg[256];
        wsprintf(errorMsg, L"Failed to set keyboard hook. Error: %lu\n", error);
        OutputDebugString(errorMsg);
    } else {
        OutputDebugString(L"Keyboard hook set successfully.\n");
    }
}

// Function to stop keylogging
void StopKeylogging()
{
    if (keyboardHook != NULL) {
        UnhookWindowsHookEx(keyboardHook);
        keyboardHook = NULL;
        OutputDebugString(L"Keyboard hook unhooked.\n");
    }
}

UINT_PTR timerId = 1;
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> disX(0, 800); // Assuming screen width is 800
std::uniform_int_distribution<> disY(0, 600); // Assuming screen height is 600

void DrawRandomCircle(HWND hWnd)
{
    HDC hdc = GetDC(hWnd);
    int x = disX(gen);
    int y = disY(gen);
    Ellipse(hdc, x - 25, y - 25, x + 25, y + 25);
    ReleaseDC(hWnd, hdc);
}

void CALLBACK TimerProc(HWND hWnd, UINT message, UINT_PTR idEvent, DWORD dwTime)
{
    if (idEvent == timerId)
    {
        InvalidateRect(hWnd, NULL, TRUE);
        DrawRandomCircle(hWnd);
    }
}

void StartDrawingCircles(HWND hWnd)
{
    // Set a timer to refresh at the monitor's refresh rate (e.g., 60 Hz)
    timerId = SetTimer(hWnd, timerId, 1000 / 60, TimerProc);
    if (timerId == 0)
    {
        MessageBox(hWnd, L"Failed to create timer!", L"Error", MB_OK);
    }
}

void StopDrawingCircles(HWND hWnd)
{
    KillTimer(hWnd, timerId);
}

