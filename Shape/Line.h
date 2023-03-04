#pragma once
#include "Shape.h"

namespace ExtendedShapes {

class Line : Shape {
    public:
    Line(D2D_POINT_2F p1, D2D_POINT_2F p2, float sW, D2D1_COLOR_F fill = D2D1::ColorF(D2D1::ColorF::Black)) 
        : startPoint(p1), endPoint(p2), strokeWidth(sW), pBrush(NULL) {
            fillColor = fill;
        };

    ~Line() {
        DiscardGraphicsResources();
    }

    void DiscardGraphicsResources() {
        SafeRelease<ID2D1SolidColorBrush>(&pBrush);
    }

    D2D_POINT_2F startPoint;
    D2D_POINT_2F endPoint;
    float strokeWidth;

    ID2D1SolidColorBrush* pBrush;
    void draw(ID2D1HwndRenderTarget *rTarget) {
        rTarget->SetTransform(transformMatrix);

        HRESULT hr_brush = rTarget->CreateSolidColorBrush(fillColor, &pBrush);
        if(SUCCEEDED(hr_brush)) {
            rTarget->DrawLine(startPoint, endPoint, pBrush, strokeWidth);
        }

        rTarget->SetTransform(D2D1::Matrix3x2F::Identity());
    }
};

};