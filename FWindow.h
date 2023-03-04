#pragma once
#include "Window.h"
#include <d2d1.h>
#pragma comment(lib, "d2d1")

class Shape;

class FWindow : public BaseWindow<FWindow>
{
    static const int MAX_SHAPE_COUNT = 100;
    int currentShapes = 0;

    ID2D1Factory            *pFactory;
    ID2D1HwndRenderTarget   *pRenderTarget;

    HRESULT CreateGraphicsResources();
    void    DiscardGraphicsResources();
    void    OnPaint();
    void    Resize();

    Shape *shapes[MAX_SHAPE_COUNT];

    public:
    
    D2D1_COLOR_F backGroundColor = D2D1::ColorF(D2D1::ColorF::Moccasin);

    void setBackgroundColor(D2D1_COLOR_F color) {
        backGroundColor = color;
    }

    FWindow() : pFactory(NULL), pRenderTarget(NULL) {}

    PCWSTR  ClassName() const { return L"Test Window"; };
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    static int getWindowCount() { return BaseWindow<FWindow>::getWindowCount(); }
    static int msgLoop() { return BaseWindow<FWindow>::msgLoop(); };

    bool addShape(Shape *_shape);
    bool removeShape(int id);
    bool removeShape(Shape *_shape);

    D2D1_SIZE_F getCanvasSize() {
        return pRenderTarget->GetSize();
    }

    int test() {return 1;}
};