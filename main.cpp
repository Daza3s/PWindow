#include "PWindow.h"


PWindow *w;

int main() {

    D2D1_POINT_2F p1;
    D2D1_POINT_2F p2;
    p1.x = 10;
    p1.y = 10;
    p2.x = 100;
    p2.y = 100;

    ExtendedShapes::Line *l1 = new ExtendedShapes::Line(p1, p2, 10);
    ExtendedShapes::Ellipse *e1 = new ExtendedShapes::Ellipse(p2, 50, 10);
    D2D1_RECT_F rectangle1 = D2D1::RectF(
            200.0f,
            200.0f,
            300.0f,
            400.0f
            );
    ExtendedShapes::Rectangle *r1 = new ExtendedShapes::Rectangle(&rectangle1);

    w = new PWindow();

    w->addShape((Shape*)l1);
    w->addShape((Shape*)e1);
    w->addShape((Shape*)r1);


    w->showWindow();


    while(FWindow::msgLoop() > 0 && FWindow::getWindowCount() > 0);
    //Logger::log("exiting main msg loop close console at discression", FLAG::VERBOSE);
    //while (true);
    return 0;
}