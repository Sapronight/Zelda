#include "bullet.h"
#include "ennemy.h"
#include <QBrush>
#include <QTimer>
#include <QDebug>


Bullet::Bullet(int xPos, int yPos, QSize size, int direction, int decrement,Map * actualMap, Score * score ,QGraphicsItem *parent) :QGraphicsRectItem (parent)
{
    //Initialisation
    m_decrement = decrement;
    m_direction = direction;
    m_actualMap = actualMap;
    m_score = score;

    setRect(0, 0, size.width(), size.height());
    setPos(xPos, yPos);

    QBrush originalBrush;
    QImage * image = new QImage(":/level/sprites/background/iconZelda.png");
    *image = image->scaled(size.width(), size.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    originalBrush.setTextureImage(*image);

    setBrush(originalBrush);

    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(70);

}

void Bullet::move()
{
    if(m_timer != 0 && collisionMap() != true){
        switch (m_direction) {
        case 0:
            setPos(pos().x(), pos().y() - m_decrement);
            break;
        case 1:
            setPos(pos().x(), pos().y() + m_decrement);
            break;
        case 2:
            setPos(pos().x() - m_decrement, pos().y());
            break;
        case 3:
            setPos(pos().x() + m_decrement, pos().y());
            break;

        }
        m_timer --;
    }
    else{
        for(int i = 0; i < int(m_destroyList.size()); i++){
            m_actualMap->changeMapIndex(0, m_destroyList[i] - 1);
        }
        delete this;
    }





}

bool Bullet::collisionMap()
{
    bool result = false;
    /*
     * Si il y a collision return false
     * Direction :
     *  up = 0
     *  down = 1
     *  left = 2
     *  right = 3
     * */
    int realX = 0;
    int realY = 0;

    switch (m_direction) {
        case 3:
            realX = int(pos().x()) + int(boundingRect().width()) + m_decrement;
            realY = int(pos().y());
            for(int i = 0; i < int(boundingRect().height()); i++){
                realY += 1;
                if(contain(m_collidingList, m_sizeOfCollingList, pointToCase(realX, realY))){
                    return true;
                }
            }
            break;
        case 0:
            realX = int(pos().x());
            realY = int(pos().y()) - m_decrement;
            for(int i = 0; i < int(boundingRect().width()); i++){
                realX += 1;

                if(contain(m_collidingList, m_sizeOfCollingList, pointToCase(realX, realY))){
                    return true;
                }
            }
            break;
        case 1:
            realX = int(pos().x());
            realY = int(pos().y()) + int(boundingRect().height()) + m_decrement;
            for(int i = 0; i < int(boundingRect().width()); i++){
                realX += 1;
                if(contain(m_collidingList, m_sizeOfCollingList, pointToCase(realX, realY))){
                    return true;
                }
            }
            break;
        case 2:
            realX = int(pos().x()) - m_decrement;
            realY = int(pos().y());
            for(int i = 0; i < int(boundingRect().height()); i++){
                realY += 1;
                if(contain(m_collidingList, m_sizeOfCollingList, pointToCase(realX, realY))){
                    return true;
                }
            }
            break;
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0; i < colliding_items.size(); i++){
        if(typeid (*(colliding_items[i])) == typeid(Ennemy)){
            //increase score
            m_score->increase();
            qDebug() << int(colliding_items[i]->pos().x()) << "y :" << int(colliding_items[i]->pos().y());
            int c = int(colliding_items[i]->pos().x() / m_actualMap->getYRect()) + int((colliding_items[i]->pos().y()/ m_actualMap->getYRect() ) * m_actualMap->getSizeMap().width());
            m_destroyList.push_back(c);

            delete colliding_items[i];
            return true;
        }
    }

    return result;
}

int Bullet::pointToCase(int x, int y)
{
    //Retourne l'entier à l'intérieur d'un case :
    int result = NULL;
    int xCase = int(x / m_actualMap->getXRect());
    int yCase = int(y / m_actualMap->getYRect());

    int index = xCase + yCase * m_actualMap->getSizeMap().width();
    result = m_actualMap->getListeInt()[index];
    return result;
}

bool Bullet::contain(int list[], int size, int element)
{
    bool result = false;
    for(int i = 0; i < size; i++){
        if(element == list[i]){
            return true;
        }
    }

    return result;
}
