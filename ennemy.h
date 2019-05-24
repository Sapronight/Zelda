#ifndef ENNEMY_H
#define ENNEMY_H
#include <QGraphicsRectItem>

class Ennemy: public QGraphicsRectItem{
public:
    Ennemy(QSize size, QGraphicsItem * parent = nullptr);
private:
};

#endif // ENNEMY_H
