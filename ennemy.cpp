#include "ennemy.h"
#include <QBrush>

Ennemy::Ennemy(QSize size, QGraphicsItem *parent) : QGraphicsRectItem (parent)
{
    setRect(0, 0, size.width(), size.height());

    QBrush originalBrush;
    QImage * image = new QImage(":/sprites/ennemy/ennemi0.png");
    *image = image->scaled(size.width(), size.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    originalBrush.setTextureImage(*image);

    setBrush(originalBrush);
}
