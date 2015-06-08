#include <QApplication>
#include <QWidget>

#include "application.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Application *game = new Application;
    game->show();

    return app.exec();
}
