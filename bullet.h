#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsRectItem>
#include "map.h"
#include "score.h"

class Bullet: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Bullet(int xPos, int yPos, QSize size,int direction, int decrement,Map * actualMap,Score * score,QGraphicsItem * parent = nullptr);

public slots:
    void move();
private:
    //Méthodes
    bool collisionMap();
    int pointToCase(int x, int y);
    bool contain(int list[], int size, int element);

    //Paramètres
    int m_direction;
    int m_decrement;

    Score * m_score;
    std::vector<int> m_destroyList;

    //Colliding list:
    int m_collidingList[3] = {1, 2, 3};
    int m_sizeOfCollingList = 3;

    Map* m_actualMap;

    int m_timer = 60;
};

#endif // BULLET_H
