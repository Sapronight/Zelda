#include <QApplication>
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game * mainWindow = new Game("Zelda AlphaStudent", 1280, 720);
    mainWindow->show();


    return a.exec();
}
