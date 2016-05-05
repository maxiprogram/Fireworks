#include "mainform.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat surface;
    surface.setDepthBufferSize(24);

    MainForm w;
    w.setFormat(surface);
    w.setWidth(800);
    w.setHeight(600);
    w.setMinimumWidth(800);
    w.setMinimumHeight(600);
    w.show();
    //w.showFullScreen();

    return a.exec();
}
