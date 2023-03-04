#include <iostream>
#include "FWindow.h"
#include "Shape/Shape.h"


HRESULT FWindow::CreateGraphicsResources()
{
    HRESULT hr = S_OK;
    if (pRenderTarget == NULL)
    {
        RECT rc;
        GetClientRect(hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        hr = pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(hwnd, size),
            &pRenderTarget);                                                    //Places hwndRenderTarget in pRenderTarget
    }
    return hr;
}

void FWindow::DiscardGraphicsResources()
{
    SafeRelease<ID2D1HwndRenderTarget>(&pRenderTarget);

    for(int i = 0;i < currentShapes;i++) {
        shapes[i]->DiscardGraphicsResources();
    }
}

bool FWindow::addShape(Shape *_shape) {
    if(currentShapes >= FWindow::MAX_SHAPE_COUNT) {
        return false;
    }
    shapes[currentShapes] = _shape;
    currentShapes++;
    return true;
}

bool FWindow::removeShape(int id) {
    for(int i = 0;i < currentShapes;i++) {
        if(shapes[i]->getId() == id) {
            delete shapes[i];
            shapes[i] = nullptr;
            for(int j = i;j < currentShapes - 1;j++) {
                shapes[i] = shapes[i + 1];
            }
            shapes[i] = nullptr;
            currentShapes--;
            return true;
        }
    }
    return false;
}

bool FWindow::removeShape(Shape *_shape) {
    return removeShape(_shape->getId());
}

void FWindow::OnPaint()
{
    HRESULT hr = CreateGraphicsResources();
    if (SUCCEEDED(hr))
    {
        PAINTSTRUCT ps;
        BeginPaint(hwnd, &ps);
     
        pRenderTarget->BeginDraw();

        pRenderTarget->Clear( backGroundColor );

        for(int i = 0;i < currentShapes;i++) {
            shapes[i]->draw(pRenderTarget);
        }

        hr = pRenderTarget->EndDraw();
        if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
        {
            DiscardGraphicsResources();
        }
        EndPaint(hwnd, &ps);
    }
}

void FWindow::Resize()
{
    if (pRenderTarget != NULL)
    {
        RECT rc;
        GetClientRect(hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        pRenderTarget->Resize(size);
        InvalidateRect(hwnd, NULL, FALSE);
    }
}

LRESULT FWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
        case WM_SIZE:
            {
                Resize();
                return 0;
            }
        case WM_PAINT:
            {
                OnPaint();
                return 0;
            }
        case WM_CLOSE: 
            {
                /*if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK) {
                    DestroyWindow(hwnd);
                }*/
                DestroyWindow(hwnd);
                // Else: User canceled. Do nothing.
                return 0;
            }
        case WM_DESTROY:
            {
                DiscardGraphicsResources();
                SafeRelease(&pFactory);;
                PostQuitMessage(0);
                return 0;
            }

        case WM_CREATE:
            {
                if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory))) {      //Automaticly places Factory in pFactory
                    return -1;  // Fail CreateWindowEx.
                }
                return 0;
            }
    
        
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
