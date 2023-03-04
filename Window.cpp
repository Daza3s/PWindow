#include <iostream>
#include "Window.h"
#include "FWindow.h"


template <class DERIVED_TYPE>
int BaseWindow <DERIVED_TYPE> ::WindowCount = 0;

template <class DERIVED_TYPE>
int BaseWindow <DERIVED_TYPE> ::msgLoop() {
    MSG msg = { };
    int retMsg = GetMessage(&msg, NULL, 0,  0);
    if(retMsg) {
        TranslateMessage(&msg); 
        DispatchMessage(&msg);
    }else {
        BaseWindow::WindowCount--;
    }
    return retMsg;
}

template <class DERIVED_TYPE>
LRESULT CALLBACK BaseWindow <DERIVED_TYPE> ::WindowProc(HWND _hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    DERIVED_TYPE *pThis = NULL;

    if (uMsg == WM_NCCREATE) {
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
        SetWindowLongPtr(_hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
        pThis->hwnd = _hwnd;
    }else {
        pThis = (DERIVED_TYPE*)GetWindowLongPtr(_hwnd, GWLP_USERDATA);
    }


    if (pThis) {
        return ((DERIVED_TYPE*)pThis)->HandleMessage((UINT)uMsg, (WPARAM)wParam, (LPARAM)lParam);
    }else {
        return DefWindowProc(_hwnd, uMsg, wParam, lParam);
    }
    
}


template <class DERIVED_TYPE>
void BaseWindow <DERIVED_TYPE> ::Create(
        PCWSTR lpWindowName,
        DWORD dwStyle,
        DWORD dwExStyle,
        int x,
        int y,
        int nWidth,
        int nHeight,
        HWND hWndParent,
        HMENU hMenu
    ) {
    //FreeConsole(); //hides console as soon as possible
    hInstance = GetModuleHandle(nullptr);

    wc = {0};

    wc.lpfnWndProc   = DERIVED_TYPE::WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = L"Test Window";

    RegisterClass(&wc);

    
    //DERIVED_TYPE *as_derived = (DERIVED_TYPE*)this;

    hwnd = CreateWindowEx(
        dwExStyle,                              // Optional window styles.
        L"Test Window",                         // Window class
        lpWindowName,                           // Window text
        dwStyle,                                // Window style

        // Size and position
        x, y, nWidth, nHeight,

        hWndParent,                             // Parent window    
        hMenu,                                  // Menu
        hInstance,                              // Instance handle
        this                                    // Additional application data
        );

    if(hwnd == NULL) {
        throw "Window::Window: Couldn't Create window (no info given)!";
    }
    
    WindowCount++;
}

template <class DERIVED_TYPE>
void BaseWindow <DERIVED_TYPE> ::showWindow(int nCmdShow) {
    ShowWindow(hwnd, nCmdShow);
} 


//Against linking problems function doesnt need to be called
//Should actually be BaseWindow<FWindow> but BaseWindow is an abstract class
//So we need to call FWindow which inherits from BaseWindow<FWindow>
void linkingFunction() {
    FWindow tempObj;
    tempObj.showWindow();
    tempObj.msgLoop();
    tempObj.HandleMessage((UINT)1, (WPARAM)1, (LPARAM)1);
    tempObj.ClassName();
    tempObj.Create();
}