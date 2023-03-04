#pragma once
#include <d2d1.h>
#include <Windows.h>

template <class T> void SafeRelease(T **ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

class Shape {
    protected:
    int id;
    static int nextId;
    static int getNextId() {
        return nextId++;
    }
    public:
    Shape() {
        id = Shape::getNextId();
    }
    int getId() {
        return id;
    }

    virtual ~Shape() = 0;
    virtual void DiscardGraphicsResources() = 0;

    D2D1::Matrix3x2F transformMatrix = D2D1::Matrix3x2F::Identity();

    void setTransformMatrix(D2D1::Matrix3x2F _tM) {
        transformMatrix = _tM;
    }

    void resetTranformMatrix() {
        transformMatrix = D2D1::Matrix3x2F::Identity();
    }

    D2D1_COLOR_F fillColor;
    D2D1_COLOR_F strokeColor;
    virtual void draw(ID2D1HwndRenderTarget *rTarget) = 0;
};