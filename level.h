#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>
#include <vector>
#include "map.h"
#include "player.h"

class Level:public QGraphicsScene{
    Q_OBJECT
public:
    Level(QSize size,Player * player ,QObject * controller ,QGraphicsScene * parent = nullptr);


    //Getters
    QGraphicsScene *getScene() const;
    QPoint * getPosOnScene();
    Map *getMap() const;

    //Setters
    void setScene(QGraphicsScene *scene);


    //Méthodes
    void iniMapDefaut0();
    void addPlayerToScene();
    void removePlayerToScene();

private:
    //méthodes
    void addMap(std::vector<QGraphicsRectItem*> tabRect);
    void addEnnemy();

    //paramètres
    QSize m_size;
    QGraphicsScene * m_scene;
    QObject * m_controller;
    Player * m_player;


    //Position de départ du player
    QPoint * m_posOnScene;

    //La carte
    Map * m_mainMap;
};

#endif // LEVEL_H
