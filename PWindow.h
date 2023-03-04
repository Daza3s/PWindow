#pragma once
#include "Shape/ExtendedShapes.h"
#include "FWindow.h"

class PWindow : public FWindow {
    public:
    PWindow(PCWSTR lpWindowName = L"Window",
        DWORD dwStyle = WS_OVERLAPPEDWINDOW,
        DWORD dwExStyle = 0,
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int nWidth = CW_USEDEFAULT,
        int nHeight = CW_USEDEFAULT,
        HWND hWndParent = NULL,
        HMENU hMenu = NULL) : FWindow() {
            this->Create(lpWindowName, dwStyle, dwExStyle, x, y, nWidth, nHeight, hWndParent, hMenu);
        }
};
