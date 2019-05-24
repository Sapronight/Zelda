#ifndef GAME_H
#define GAME_H
#include "menu.h"
#include "level.h"
#include "player.h"
#include "map.h"
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSize>
#include <vector>

class Game: public QWidget{
    Q_OBJECT
public:
    Game(QString name,int width, int height ,QWidget * parent = nullptr);


    //Getters
    std::vector<Level*> getLevelListe() const;
    Map *getActualMap() const;

    //Setters
    void setLevelListe(const std::vector<Level*> &levelListe);



    //Méthodes
    void updateScene();
    void updatePosOnScene();
    void mainMenu();
    void keyPressEvent(QKeyEvent * event);
    void updateMap();

public slots:
    void nextScene();
    void windowClose();
    void firstLevel();
    void addBulletToScene();

private:
    //Methodes
    bool eventFilter(QObject *object, QEvent *event);


    //Pointeurs sur les scenes :
    Menu * m_menu;

    //Pointeurs sur les views
    QGraphicsView * m_mainView;

    //Liste des level et la position dans la liste:
    std::vector<Level*> m_levelListe;
    int m_posLevel;

    //Joueur
    Player * m_player;
    //Récupération de la position de départ selon le niveau
    QPoint * m_posOnScene;

    //Carte de la map actuel:
    Map * m_actualMap;

    //Liste d'ennemies TODO


    //Autre paramètres
    QSize m_size;
    bool m_addToFirstScene = false;
};

#endif // GAME_H
