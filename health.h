#ifndef HEALTH_H
#define HEALTH_H


#include <QGraphicsTextItem>

class Health :public QGraphicsTextItem
{
public:
    Health(QGraphicsItem * parent = nullptr);
    void decrease();
    int getHp();
private:
    int m_hp;
};


#endif // HEALTH_H
