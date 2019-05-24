#include "map.h"
#include <QBrush>
using namespace std;


Map::Map(QSize size)
{
    //Initialisation des points de départ :
    m_mapSize.setWidth(size.width() / m_xRect);
    m_mapSize.setHeight(size.height() / m_yRect);

    QGraphicsRectItem * obj;
    //Remplissage des tableaux
    for(int y = 0; y < int(m_mapSize.height()); y ++){
        for(int x = 0; x < int(m_mapSize.width()); x ++){
            obj = new QGraphicsRectItem(0, 0, m_xRect, m_yRect);
            obj->setPos(x * m_xRect, y * m_yRect);
            m_listeInt.push_back(0);
            m_listeRect.push_back(obj);
        }
    }

    //Ajout des bordures de la map
    wallIni();

}

std::vector<int> Map::getListeInt() const
{
    return m_listeInt;
}

std::vector<QGraphicsRectItem*> Map::getListRect() const
{
    return m_listeRect;
}

std::vector<Ennemy *> Map::getListeEnnemy() const
{
    return m_listeEnnemy;
}

QSize Map::getSizeMap()
{
    return m_mapSize;
}

int Map::getXRect()
{
    return m_xRect;
}

int Map::getYRect()
{
    return m_yRect;
}

void Map::setListeInt(std::vector<int> tabInt)
{
    m_listeInt = tabInt;
}

void Map::setListRect(std::vector<QGraphicsRectItem *> tabRect)
{
    m_listeRect = tabRect;
}

void Map::changeMapIndex(int nElement, int index)
{
    m_listeInt[index] = nElement;
}

void Map::updateImage()
{
    QBrush grass;
    QBrush mountain;
    QBrush water;
    QBrush wall;
    QBrush doors;
    QBrush grass_Herbs;
    /*
     * On note les éléments suivant :
     * grass = 0
     * wall = 1
     * mountain = 2
     * water = 3
     * doors = 4
     * ennemy = 5;
     * */

    QImage * image = new QImage(":/level/sprites/background/grass_without_herbs.png");
    *image = image->scaled(m_xRect, m_yRect, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    grass.setTextureImage(*image);
    image = new QImage(":/level/sprites/background/mountain.png");
    *image = image->scaled(m_xRect, m_yRect, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    mountain.setTextureImage(*image);
    image = new QImage(":/level/sprites/background/wall.png");
    *image = image->scaled(m_xRect, m_yRect, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    wall.setTextureImage(*image);
    image = new QImage(":/level/sprites/background/water0.png");
    *image = image->scaled(m_xRect, m_yRect, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    water.setTextureImage(*image);
    image = new QImage(":/level/sprites/background/doors0.png");
    *image = image->scaled(m_xRect, m_yRect, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    doors.setTextureImage(*image);
    image = new QImage(":/level/sprites/background/grass_Herbs.png");
    *image = image->scaled(m_xRect, m_yRect, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    grass_Herbs.setTextureImage(*image);

    Ennemy * ennemy;
    QSize shape;
    shape.setWidth(m_xRect);
    shape.setHeight(m_yRect);
    int xPos, yPos;

    for(int i = 0; i < int(m_listeInt.size()); i ++){

        switch (m_listeInt[i]) {
            case 0:
                m_listeRect[i]->setBrush(grass);
                break;
            case 1:
                m_listeRect[i]->setBrush(wall);
                break;
            case 2:
                m_listeRect[i]->setBrush(mountain);
                break;
            case 3:
                m_listeRect[i]->setBrush(water);
                break;
            case 4:
                m_listeRect[i]->setBrush(doors);
                break;
            case 5:
                //Ajout de grass avec herbs sous l'ennemy
                ennemy = new Ennemy(shape);
                xPos = (i % m_mapSize.width());
                yPos = ((i - xPos) / m_mapSize.width()) * m_yRect;
                xPos = xPos * m_xRect;
                ennemy->setPos(xPos, yPos);
                m_listeEnnemy.push_back(ennemy);
                m_listeRect[i]->setBrush(grass_Herbs);
                break;
           }

    }

}

void Map::emptyList()
{
    m_listeInt.clear();
    m_listeRect.clear();
}

void Map::wallIni()
{
    int cpt = 0;
    for(int y = 0; y < int(m_mapSize.height()); y ++){
        for(int x = 0; x < int(m_mapSize.width()); x ++){
            if(y == 0){
                m_listeInt[cpt] = 1;
            }
            else if (x == 0 || x == int(m_mapSize.width() - 1)) {
                m_listeInt[cpt] = 1;
            }
            else if (y == int(m_mapSize.height() - 1)) {
                m_listeInt[cpt] = 1;
            }

            cpt ++;
        }
    }
}

void Map::mapDefaut0()
{
    QSize size;
    size.setWidth(1280 * 4);
    size.setHeight(720*4);

    m_mapSize.setWidth(size.width() / m_xRect);
    m_mapSize.setHeight(size.height() / m_yRect);



    //Vide l'ancien tableau
    emptyList();

    QGraphicsRectItem * obj;
    //Remplissage des tableaux
    for(int y = 0; y < int(m_mapSize.height()); y ++){
        for(int x = 0; x < int(m_mapSize.width()); x ++){
            obj = new QGraphicsRectItem(0, 0, m_xRect, m_yRect);
            obj->setPos(x * m_xRect, y * m_yRect);
            m_listeInt.push_back(0);
            m_listeRect.push_back(obj);
        }
    }

    //Ajout des bordures de la map
    wallIni();

    //Map par défaut
    int cpt = 0;
    for(int y = 0; y < int(m_mapSize.height()); y ++){
        for(int x = 0; x < int(m_mapSize.width()); x ++){
            if(x >= 5 && x <= 10 && y >= 35 && y <= 45){
                m_listeInt[cpt] = 3;
            }
            else if (x >= 15 && x <= 25 && y >= 10 && y <= 15) {
                m_listeInt[cpt] = 2;
            }
            else if (x == 20 && y >= 1 && y <= 9) {
                m_listeInt[cpt] = 1;
            }
            else if (x >= 70 && x <= 79 && y >= 45 && y <= 47) {
                m_listeInt[cpt] = 3;
            }
            else if (x == 5 && y == 15) {
                m_listeInt[cpt] = 4;
            }
            else if (x >= 15 && x <= 20 && y >= 3 &&y <= 9) {
                m_listeInt[cpt] = 5;
            }

            cpt ++;
        }
    }



}
