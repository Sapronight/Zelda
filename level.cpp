#include "level.h"
#include <vector>
#include <QPainter>
#include <QGraphicsRectItem>
#include <QDebug>
using namespace std;

Level::Level(QSize size,Player * player,QObject * controller ,QGraphicsScene * parent)
{
    //Initialisation
    m_scene = new QGraphicsScene(parent);
    m_scene->setSceneRect(0, 0, size.width(), size.height());
    m_controller = controller;
    Map * carte = new Map(size);
    m_mainMap = carte;
    m_player = player;

    //Initialisation position de départ :
    m_posOnScene = new QPoint();
    m_posOnScene->setX(128);
    m_posOnScene->setY(120);

    //Recupération des tableaux
    vector<QGraphicsRectItem*> tabRect = carte->getListRect();
    vector<int> tabInt = carte->getListeInt();

    //Ajout de la carte :
    carte->updateImage();
    tabRect = carte->getListRect();
    addMap(tabRect);
}

QGraphicsScene *Level::getScene() const
{
    return m_scene;
}

QPoint *Level::getPosOnScene()
{
    return m_posOnScene;
}

Map *Level::getMap() const
{
    return m_mainMap;
}

void Level::setScene(QGraphicsScene *scene)
{
    m_scene = scene;
}

void Level::iniMapDefaut0()
{
    m_posOnScene->setX(50);
    m_posOnScene->setY(50);
    m_scene->clear();
    m_mainMap->mapDefaut0();
    m_mainMap->updateImage();
    addMap(m_mainMap->getListRect());
}

void Level::addPlayerToScene()
{
    m_scene->addItem(m_player);
    m_player->setPosOnScene(m_posOnScene);
    m_player->updatePos();
    m_scene->addItem(m_player->getHealth());
    m_scene->addItem(m_player->getScore());

}

void Level::removePlayerToScene()
{
    m_scene->removeItem(m_player);
    m_player->setPosOnScene(nullptr);
    m_scene->removeItem(m_player->getHealth());
    m_scene->removeItem(m_player->getScore());
}

void Level::addMap(vector<QGraphicsRectItem *> tabRect)
{
    for(int i = 0; i < int(tabRect.size()); i++){
        m_scene->addItem(tabRect[i]);
    }
    addEnnemy();
}

void Level::addEnnemy()
{
    for(int i = 0; i < int(m_mainMap->getListeEnnemy().size()); i++){
        m_scene->addItem(m_mainMap->getListeEnnemy()[i]);
    }
}
