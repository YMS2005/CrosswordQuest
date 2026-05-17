#include <QApplication>
#include "Homepage.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    // Qt6: high-DPI scaling is enabled by default, no flags needed

    Homepage window;
    window.show();

    return app.exec();
}
