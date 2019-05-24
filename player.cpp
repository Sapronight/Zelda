#include "player.h"
#include <QKeyEvent>
#include <QBrush>
#include <QDebug>
#include <QGraphicsView>


Player::Player(QSize size,QPoint * posOnScene ,Map * actualMap, QObject * controller, QGraphicsView * view ,QGraphicsRectItem *parent) : QGraphicsRectItem (parent)
{
    //Initialisation des paramètres
    m_actualMap = actualMap;
    m_posOnScene = posOnScene;
    m_controller =controller;
    m_mainView = view;
    m_Hp = new Health();
    m_Score = new Score();

    //Initialisation Vision:
    m_directionVision = 1;


    //Connection:
    connect(this, SIGNAL(triggerScene()), m_controller, SLOT(nextScene()));
    connect(this, SIGNAL(fire()), m_controller, SLOT(addBulletToScene()));

    //Dessin du rectangle :
    setRect(0, 0, size.width(), size.height());
    m_posOnScene = nullptr;
    QBrush originalBrush;
    QImage * image = new QImage(":/sprites/link/linkDown.png");
    *image = image->scaled(size.width(),size.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    originalBrush.setTextureImage(*image);
    setBrush(originalBrush);
}

void Player::keyPressEvent(QKeyEvent * event)
{
    int yPos;
    int xPos;

    QBrush linkDown;
    QBrush linkLeft;
    QBrush linkUp;
    QBrush linkRight;

    QImage * image = new QImage(":/sprites/link/linkDown.png");
    *image = image->scaled(int(boundingRect().width()),int(boundingRect().height()), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    linkDown.setTextureImage(*image);
    image = new QImage(":/sprites/link/linkUp.png");
    *image = image->scaled(int(boundingRect().width()),int(boundingRect().height()), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    linkUp.setTextureImage(*image);
    image = new QImage(":/sprites/link/linkRight.png");
    *image = image->scaled(int(boundingRect().width()),int(boundingRect().height()), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    linkRight.setTextureImage(*image);
    image = new QImage(":/sprites/link/linkLeft.png");
    *image = image->scaled(int(boundingRect().width()),int(boundingRect().height()), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    linkLeft.setTextureImage(*image);


    if(m_posOnScene != nullptr){
        switch (event->key()) {
            case Qt::Key_S:
            //Déplacement bas
                m_directionVision = 1;
                setBrush(linkDown);
                if(collision(1)){
                    yPos = m_posOnScene->y();
                    yPos += m_pixelDeplacementY;
                    m_posOnScene->setY(yPos);
                    updatePos();
                    ensureVisible(m_posOnScene->x(), m_posOnScene->y(), 0, 0, 500, 300);
                    triggerEvent();                    
                }

                break;
            case Qt::Key_Z:
            //Déplacement haut
                m_directionVision = 0;
                setBrush(linkUp);
                if(collision(0)){
                    yPos = m_posOnScene->y();
                    yPos -= m_pixelDeplacementY;
                    m_posOnScene->setY(yPos);
                    updatePos();
                    ensureVisible(m_posOnScene->x(), m_posOnScene->y(), 0, 0, 500, 300);
                    triggerEvent();
                }

                break;
            case Qt::Key_Q:
            //Deplacement Gauche
                m_directionVision = 2;
                setBrush(linkLeft);
                if(collision(2)){
                    xPos = m_posOnScene->x();
                    xPos -= m_pixelDeplacementX;
                    m_posOnScene->setX(xPos);
                    updatePos();
                    ensureVisible(m_posOnScene->x(), m_posOnScene->y(), 0, 0, 500, 300);
                    triggerEvent();
                }
                break;
            case Qt::Key_D:
            //Deplacement Droite
                m_directionVision = 3;
                setBrush(linkRight);
                if(collision(3)){
                    xPos = m_posOnScene->x();
                    xPos += m_pixelDeplacementX;
                    m_posOnScene->setX(xPos);
                    updatePos();
                    ensureVisible(m_posOnScene->x(), m_posOnScene->y(), 0, 0, 500, 300);
                    triggerEvent();
                }
                break;
            case Qt::Key_Space:
                int xPos, yPos;
                QSize shape;
                switch (m_directionVision) {
                case 0:
                    shape.setWidth(int(boundingRect().width()/4));
                    shape.setHeight(int(boundingRect().height() * 2 / 3));
                    xPos = m_posOnScene->x() + int(boundingRect().width()/2) - int(shape.width()/2);
                    yPos = m_posOnScene->y() - m_pixelDeplacementY;
                    m_bullet = new Bullet(xPos, yPos, shape, 0, m_pixelDeplacementY*2, m_actualMap, m_Score);
                    break;
                case 1:
                    shape.setWidth(int(boundingRect().width()/4));
                    shape.setHeight(int(boundingRect().height() * 2 / 3));
                    xPos = m_posOnScene->x() + int(boundingRect().width()/2) - int(shape.width()/2);
                    yPos = m_posOnScene->y() + int(boundingRect().height()) + m_pixelDeplacementY;
                    m_bullet = new Bullet(xPos, yPos, shape, 1, m_pixelDeplacementY*2, m_actualMap, m_Score);
                    break;
                case 2:
                    shape.setWidth(int(boundingRect().width() * 2 / 3));
                    shape.setHeight(int(boundingRect().height() / 4));
                    xPos = m_posOnScene->x() - m_pixelDeplacementX - shape.width();
                    yPos = m_posOnScene->y() + int(boundingRect().width() / 2) - int(shape.height() / 2);
                    m_bullet = new Bullet(xPos, yPos, shape, 2, m_pixelDeplacementX*2, m_actualMap, m_Score);
                    break;
                case 3:
                    shape.setWidth(int(boundingRect().width() * 2 / 3));
                    shape.setHeight(int(boundingRect().height() / 4));
                    xPos = m_posOnScene->x() + m_pixelDeplacementX + int(boundingRect().width());
                    yPos = m_posOnScene->y() + int(boundingRect().width() / 2) - int(shape.height() / 2);
                    m_bullet = new Bullet(xPos, yPos, shape, 3, m_pixelDeplacementX*2, m_actualMap, m_Score);
                    break;
                }


                emit fire();
                break;
        }
    }

}

void Player::updatePos()
{
    if(m_posOnScene != nullptr)
    {
        setPos(*m_posOnScene);
        int xCenter = m_posOnScene->x() + int(boundingRect().width() / 2) - int(m_Hp->boundingRect().width()/2);
        int yCenter = m_posOnScene->y() - 10 - int(m_Hp->boundingRect().height());
        m_Hp->setPos(xCenter, yCenter);
        yCenter -= int(m_Score->boundingRect().height()) - 10;
        xCenter = m_posOnScene->x() + int(boundingRect().width()/2) - int(m_Score->boundingRect().width() / 2);
        m_Score->setPos(xCenter, yCenter);
    }


}

bool Player::collision(int direction)
{
    bool result = true;
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
    switch (direction) {
        case 3:
            realX = m_posOnScene->x() + int(boundingRect().width()) + m_pixelDeplacementX;
            realY = m_posOnScene->y();
            for(int i = 0; i < int(boundingRect().height()); i++){
                realY += 1;
                if(contain(m_collidingList, m_sizeOfCollingList, pointToCase(realX, realY))){
                    return false;
                }
            }
            break;
        case 0:
            realX = m_posOnScene->x();
            realY = m_posOnScene->y() - m_pixelDeplacementY;
            for(int i = 0; i < int(boundingRect().width()); i++){
                realX += 1;
                if(contain(m_collidingList, m_sizeOfCollingList, pointToCase(realX, realY))){
                    return false;
                }
            }
            break;
        case 1:
            realX = m_posOnScene->x();
            realY = m_posOnScene->y() + int(boundingRect().height()) + m_pixelDeplacementY;
            for(int i = 0; i < int(boundingRect().width()); i++){
                realX += 1;
                if(contain(m_collidingList, m_sizeOfCollingList, pointToCase(realX, realY))){
                    return false;
                }
            }
            break;
        case 2:
            realX = m_posOnScene->x() - m_pixelDeplacementX;
            realY = m_posOnScene->y();
            for(int i = 0; i < int(boundingRect().height()); i++){
                realY += 1;
                if(contain(m_collidingList, m_sizeOfCollingList, pointToCase(realX, realY))){
                    return false;
                }
            }
            break;
    }
    return result;
}

QPoint *Player::getPosOnScene() const
{
    return m_posOnScene;
}

void Player::setPosOnScene(QPoint *posOnScene)
{
    m_posOnScene = posOnScene;
}

Health *Player::getHealth() const
{
    return m_Hp;
}

void Player::setActualMap(Map *actualMap)
{
    m_actualMap = actualMap;
}

void Player::triggerEvent()
{
    switch (m_actualMap->getListeInt()[actualCase()]) {
        case 0:
            //Grass do nothing
            break;
        case 4:
            //Doors
            emit triggerScene();
            break;
        case 5:
            //Ennemy
            m_Hp->decrease();
            switch (m_directionVision) {
            case 0:
                m_posOnScene->setY(m_posOnScene->y() - 25);
                break;
            case 1:
                m_posOnScene->setY(m_posOnScene->y() + 25);
                break;
            case 2:
                m_posOnScene->setX(m_posOnScene->x() + 30);
                break;
            case 3:
                m_posOnScene->setX(m_posOnScene->x() - 30);
                break;
            }
            updatePos();
            break;
    }

}

int Player::actualCase()
{
    int result = NULL;
    if(m_posOnScene != nullptr){
        QPoint centre;
        centre.setX(m_posOnScene->x() + int(boundingRect().width()/2));
        centre.setY(m_posOnScene->y() + int(boundingRect().height()/2));

        int xCase = int(centre.x() / m_actualMap->getXRect());
        int yCase = int(centre.y() / m_actualMap->getYRect());

        result = xCase + yCase * m_actualMap->getSizeMap().width();

        return result;
    }
    return result;
}

int Player::pointToCase(int x, int y)
{
    //Retourne l'entier à l'intérieur d'un case :
    int result = NULL;
    int xCase = int(x / m_actualMap->getXRect());
    int yCase = int(y / m_actualMap->getYRect());

    int index = xCase + yCase * m_actualMap->getSizeMap().width();
    result = m_actualMap->getListeInt()[index];
    return result;
}

bool Player::contain(int list[], int size, int element)
{
    bool result = false;
    for(int i = 0; i < size; i++){
        if(element == list[i]){
            return true;
        }
    }

    return result;
}

Score *Player::getScore() const
{
    return m_Score;
}

Bullet *Player::getBullet() const
{
    return m_bullet;
}


