#ifndef MENU_H
#define MENU_H

#include <QGraphicsScene>

class Menu:public QGraphicsScene{
    Q_OBJECT
public:
    Menu(QSize size,QObject * controller , QGraphicsScene * parent = nullptr);
private:
    QSize m_size;
    QObject * m_controller;
};

#endif // MENU_H
