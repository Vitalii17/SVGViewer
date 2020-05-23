#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    if(argc > 1)
    {
        window.openFile(app.arguments().at(1));
    }

    return app.exec();
}
