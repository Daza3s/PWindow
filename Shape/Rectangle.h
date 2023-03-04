#pragma once
#include "Shape.h"

namespace ExtendedShapes {

class Rectangle : Shape {
    public:
    Rectangle(D2D1_RECT_F *rect, float sW = 1.0f, D2D1_COLOR_F fill = D2D1::ColorF(D2D1::ColorF::Black), D2D1_COLOR_F stroke = D2D1::ColorF(D2D1::ColorF::White)) 
        : rectangle(rect), strokeWidth(sW), pBrush(NULL), pStroke(NULL) {
        fillColor = fill;
    }
    ~Rectangle() {
        DiscardGraphicsResources();
    }
    void DiscardGraphicsResources() {
        SafeRelease<ID2D1SolidColorBrush>(&pBrush);
        SafeRelease<ID2D1SolidColorBrush>(&pStroke);
    }
    
    D2D1_RECT_F *rectangle;
    float strokeWidth;
    ID2D1SolidColorBrush* pBrush;
    ID2D1SolidColorBrush* pStroke;

    void draw(ID2D1HwndRenderTarget *rTarget) {
        rTarget->SetTransform(transformMatrix);
        HRESULT hr_brush = rTarget->CreateSolidColorBrush(fillColor, &pBrush);
        HRESULT hr_stroke = rTarget->CreateSolidColorBrush(fillColor, &pStroke);
        if(SUCCEEDED(hr_brush) && SUCCEEDED(hr_stroke)) {
            rTarget->FillRectangle(rectangle, pBrush);
            rTarget->DrawRectangle(rectangle, pStroke);
        }
        rTarget->SetTransform(D2D1::Matrix3x2F::Identity());
    }
};

};