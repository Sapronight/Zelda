#ifndef MAP_H
#define MAP_H

#include<QGraphicsRectItem>
#include <vector>
#include <QSize>
#include "ennemy.h"

class Map {
public:
    Map(QSize size);
    //Getters
    std::vector<int> getListeInt() const;
    std::vector<QGraphicsRectItem*> getListRect() const;
    std::vector<Ennemy*> getListeEnnemy() const;

    QSize getSizeMap();

    int getXRect();
    int getYRect();

    //Setters
    void setListeInt(std::vector<int> tabInt);
    void setListRect(std::vector<QGraphicsRectItem*> tabRect);
    void changeMapIndex(int nElement, int index);

    //Méthodes
    void updateImage();
    void emptyList();
    void mapDefaut0();
private:
    //Méthodes
    void wallIni();


    //Paramètres
    QSize m_mapSize;

    //Tableau
    std::vector<int> m_listeInt;
    std::vector<QGraphicsRectItem*> m_listeRect;
    std::vector<Ennemy*> m_listeEnnemy;

    //Pour la séparation de la map
    int m_xRect = 32;
    int m_yRect = 30;
};

#endif // MAP_H
