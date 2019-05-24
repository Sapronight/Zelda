#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsRectItem>
#include <QPoint>
#include "map.h"
#include "health.h"
#include "bullet.h"
#include "score.h"

class Player : public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Player(QSize size,QPoint * posOnScene,Map * actualMap,QObject * controller, QGraphicsView * view ,QGraphicsRectItem * parent = nullptr);
    void keyPressEvent(QKeyEvent * event);
    void updatePos();
    bool collision(int direction);

    //Getters
    QPoint * getPosOnScene() const;
    Health * getHealth() const;
    Bullet *getBullet() const;
    Score *getScore() const;

    //Setters
    void setActualMap(Map * actualMap);
    void setPosOnScene(QPoint * posOnScene);





signals:
    void triggerScene();
    void fire();

private:
    //Méthodes
    void triggerEvent();
    int actualCase();
    int pointToCase(int x, int y);
    bool contain(int list[], int size, int element);

    //Paramètre
    QPoint * m_posOnScene;
    Map * m_actualMap;
    QObject * m_controller;
    QGraphicsView * m_mainView;

    //Hp over player
    Health * m_Hp;

    //Score over player
    Score * m_Score;

    //Bullet
    Bullet * m_bullet;
    //Vision Direction
    int m_directionVision;

    //Colliding list:
    int m_collidingList[3] = {1, 2, 3};
    int m_sizeOfCollingList = 3;

    //Paramètre de déplacement
    int m_pixelDeplacementX = 8;
    int m_pixelDeplacementY = 6;
};

#endif // PLAYER_H
