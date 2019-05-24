#include "health.h"

#include "QFont"
Health::Health(QGraphicsItem * parent) : QGraphicsTextItem (parent)
{
   m_hp = 8;

   setPlainText(QString("HP : ") + QString::number(m_hp));
    setDefaultTextColor(Qt::red);
    setFont(QFont("Triforce", 12));
}

void Health::decrease()
{
    m_hp--;
    setPlainText(QString("HP : ") + QString::number(m_hp));
}

int Health::getHp()
{
    return m_hp;
}
