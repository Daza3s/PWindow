#pragma once
#include "defines.h"
#include <windows.h>

template <class DERIVED_TYPE>
class BaseWindow {
    protected:

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static int WindowCount; 


    void MSG_HANDLE(UINT uMsg, WPARAM wParam, LPARAM lParam);

    HINSTANCE hInstance;
    const wchar_t* CLASS_NAME = L"Window";
    HWND hwnd;
    WNDCLASS wc;

    public:

    virtual PCWSTR  ClassName() const = 0;
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

    BaseWindow() : hwnd(NULL) {}

    void Create(
        PCWSTR lpWindowName = L"Window",
        DWORD dwStyle = WS_OVERLAPPEDWINDOW,
        DWORD dwExStyle = 0,
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int nWidth = CW_USEDEFAULT,
        int nHeight = CW_USEDEFAULT,
        HWND hWndParent = NULL,
        HMENU hMenu = NULL
    );

    HWND Window() const { return hwnd; }


    void showWindow(int nCmdShow = SW_SHOWNORMAL); //https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow
    static int getWindowCount() { return WindowCount; }
    static int msgLoop();
};