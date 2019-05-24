#include "game.h"
#include "button.h"
#include <QEvent>
#include <iostream>
#include <QDebug>
#include <QKeyEvent>
using namespace std;


Game::Game(QString name,int width, int height ,QWidget *parent) : QWidget (parent)
{
    //Initialisation des paramètre :
    m_posLevel = -1;
    //Ajout du nom de la fenêtre et set taille
    setWindowTitle(name);
    m_size.setWidth(width);
    m_size.setHeight(height);
    setFixedSize(m_size);

    //Initialisation de la view
    m_mainView = new QGraphicsView(this);
    m_mainView-> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_mainView-> setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_mainView->installEventFilter(this);

    //Initialisation du menu :
    m_menu = new Menu(m_size, this);

    //Ajout du joueur
    QSize taillePlayer;
    taillePlayer.setWidth(32);
    taillePlayer.setHeight(30);
    m_player = new Player(taillePlayer, m_posOnScene, m_actualMap,this, m_mainView);

    //Initialisation du premier level
    QSize sizeMap;
    sizeMap.setWidth(5120);
    sizeMap.setHeight(2880);
    Level * lvl0 = new Level(sizeMap, m_player,this);
    lvl0->iniMapDefaut0();
    m_levelListe.push_back(lvl0);

    //Second level :

    Level * lvl1 = new Level(sizeMap, m_player,this);
    m_levelListe.push_back(lvl1);

    //Position du joueur null au lancement du menu:
    m_posOnScene = nullptr;



    //Set view on the menu
    m_mainView->setScene(m_menu);

    //Set focus on player;
    m_player->setFlag(QGraphicsItem::ItemIsFocusable);
    m_player->setFocus();

    //SetCamera on the player:

    m_mainView->centerOn(m_player);

}

void Game::nextScene()
{
    m_levelListe[m_posLevel]->removePlayerToScene();
    if(int(m_levelListe.size()) <= m_posLevel + 1){
        m_posLevel = 0;
    }
    else {
        m_posLevel += 1;
    }
    updateScene();
    updatePosOnScene();
    m_levelListe[m_posLevel]->addPlayerToScene();

    //Set focus on the player:
    m_player->setFocus();
}

void Game::windowClose()
{
    this->close();
}

void Game::firstLevel()
{
    m_posLevel = 0;
    updateScene();
    updatePosOnScene();
    if(m_addToFirstScene == false){
        m_levelListe[m_posLevel]->addPlayerToScene();
        m_addToFirstScene = true;
    }
    //Set focus on player:
    m_player->setFocus();

}

void Game::addBulletToScene()
{
    m_levelListe[m_posLevel]->getScene()->addItem(m_player->getBullet());
}

bool Game::eventFilter(QObject *object, QEvent *event)
{
    if(object == m_mainView && event->type() == QEvent::Wheel){
        //cout << "Wheel Blocked" << endl;
        return true;
    }
    //cout << "Mouse Wheel still doing something" << endl;
    return false;

}

vector<Level*> Game::getLevelListe() const
{
    return m_levelListe;
}

Map *Game::getActualMap() const
{
    return m_actualMap;
}

void Game::setLevelListe(const vector<Level*> &levelListe)
{
    m_levelListe = levelListe;
}

void Game::updateScene()
{
    m_mainView->setScene(m_levelListe[m_posLevel]->getScene());
    updateMap();
}

void Game::updatePosOnScene()
{
    m_posOnScene = m_levelListe[m_posLevel]->getPosOnScene();
    m_player->setPosOnScene(m_posOnScene);
}

void Game::mainMenu()
{
    m_mainView->setScene(m_menu);
}

void Game::keyPressEvent(QKeyEvent *event)
{
    if(event){
        if(event->key() == Qt::Key_Backspace){
            mainMenu();
        }
        if(event->key() == Qt::Key_L){
            nextScene();
        }
    }
}

void Game::updateMap()
{
    m_actualMap = m_levelListe[m_posLevel]->getMap();
    m_player->setActualMap(m_actualMap);
}
