#pragma once
#include "Window.h"
#include <d2d1.h>
#include <stdexcept>
#pragma comment(lib, "d2d1")

enum CBMSG {
    RESIZE,
    ONPAINT
};

class Shape;

class FWindow : public BaseWindow<FWindow>
{
    static const int MAX_SHAPE_COUNT = 100;
    static const int COUNT_CALLBACK_UMSG = 2;
    int currentShapes = 0;

    ID2D1Factory            *pFactory;
    ID2D1HwndRenderTarget   *pRenderTarget;

    HRESULT CreateGraphicsResources();
    void    DiscardGraphicsResources();
    void    OnPaint();
    void    Resize();

    Shape *shapes[MAX_SHAPE_COUNT];

    void (*msgCallbackFuncs[COUNT_CALLBACK_UMSG])(WPARAM, LPARAM);

    public:
    
    D2D1_COLOR_F backGroundColor = D2D1::ColorF(D2D1::ColorF::Moccasin);

    void setBackgroundColor(D2D1_COLOR_F color) {
        backGroundColor = color;
    }

    FWindow() : pFactory(NULL), pRenderTarget(NULL) {
        resetAllMsgFunc();
    }

    PCWSTR  ClassName() const { return L"Test Window"; };
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    static int getWindowCount() { return BaseWindow<FWindow>::getWindowCount(); }
    static int msgLoop() { return BaseWindow<FWindow>::msgLoop(); };

    bool addShape(Shape *_shape);
    bool removeShape(int id);
    bool removeShape(Shape *_shape);
    void removeAllShapes();

    D2D1_SIZE_F getCanvasSize() {
        D2D1_SIZE_F size;
        if(!pRenderTarget) {
            HRESULT hr = CreateGraphicsResources();
            if(FAILED(hr)) {
                throw std::runtime_error("Failed to create Graphics resources");
            }
        }
        size = pRenderTarget->GetSize();
        return (D2D1_SIZE_F)size;
    }

    void setMsgFunc(CBMSG uMsgType, void (*funcptr)(WPARAM, LPARAM)) {
        msgCallbackFuncs[uMsgType] = funcptr;
    }

    void resetMsgFunc(CBMSG uMsgType) {
        msgCallbackFuncs[uMsgType] = nullptr;
    }

    void resetAllMsgFunc() {
        for(int i = 0;i < COUNT_CALLBACK_UMSG;i++) {
            msgCallbackFuncs[i] = nullptr;
        }
    }

    int test() {return 1;}
};