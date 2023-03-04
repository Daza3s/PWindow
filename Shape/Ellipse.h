#pragma once
#include "Shape.h"

namespace ExtendedShapes {

class Ellipse : Shape {
    public:
    Ellipse(D2D_POINT_2F _p1, float rad_1, float rad_2, D2D1_COLOR_F fill = D2D1::ColorF(D2D1::ColorF::Black), D2D1_COLOR_F stroke = D2D1::ColorF(D2D1::ColorF::White)) 
        : center(_p1), radius_x(rad_1), radius_y(rad_2), pFillBrush(NULL), pStrokeBrush(NULL) {
            fillColor = fill;
            strokeColor = stroke;
            dEllipse = D2D1::Ellipse(center, radius_x, radius_y);
        };

    ~Ellipse() {
        DiscardGraphicsResources();
    }

    void DiscardGraphicsResources() {
        SafeRelease<ID2D1SolidColorBrush>(&pFillBrush);
        SafeRelease<ID2D1SolidColorBrush>(&pStrokeBrush);
    }

    D2D_POINT_2F center;
    D2D1_ELLIPSE dEllipse;

    float radius_x;
    float radius_y;

    ID2D1SolidColorBrush* pFillBrush;
    ID2D1SolidColorBrush* pStrokeBrush;

    void draw(ID2D1HwndRenderTarget *rTarget) {
        rTarget->SetTransform(transformMatrix);

        HRESULT hr_fill = rTarget->CreateSolidColorBrush(fillColor, &pFillBrush);
        HRESULT hr_stroke = rTarget->CreateSolidColorBrush(strokeColor, &pStrokeBrush);
        if(SUCCEEDED(hr_fill) && SUCCEEDED(hr_stroke)) {
            rTarget->FillEllipse(dEllipse, pFillBrush);
        }

        rTarget->SetTransform(D2D1::Matrix3x2F::Identity());
    }
};

};