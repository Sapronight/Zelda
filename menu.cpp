#include "menu.h"
#include "button.h"

#include <QBrush>
#include <QPixmap>
#include <QGraphicsTextItem>
#include <QFont>
#include <QFontDatabase>

Menu::Menu(QSize size, QObject * controller ,QGraphicsScene *parent) : QGraphicsScene (parent)
{
    //Ajustement de la taille
    m_size = size;
    setSceneRect(0, 0, size.width(), size.height());

    //Ajout du pointeur sur notre controller
    m_controller = controller;

    //Ajout du background :
    QPixmap * image = new QPixmap(":/images/background.jpg");
    *image = image->scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QBrush * background = new QBrush(*image);
    setBackgroundBrush(*background);

    //Ajout du text:
    QGraphicsTextItem * title = new QGraphicsTextItem(QString("JEU ZELDA"));
    QFontDatabase::addApplicationFont(":/fonts/Triforce.ttf");
    int sizeFont = (70 * size.width()) / 1280;
    int weightFont = (5 * size.width()) / 1280;
    QFont * zelda = new QFont("Triforce", sizeFont, weightFont);

    title->setFont(*zelda);
    addItem(title);
    int posX = int(m_size.width()/2 - title->boundingRect().width()/2);
    title->setPos(posX, 0);

    //Ajout du bouton play :
    sizeFont = (50 * size.width()) / 1280;
    QFont * buttonF = new QFont("Triforce", sizeFont, weightFont);
    Button * play = new Button("PLAY", buttonF);

    int xPos = int(m_size.width()/2 - play->boundingRect().width()/2);
    int yPos = int(title->boundingRect().height() + title->boundingRect().height()/2);

    play->setPos(xPos, yPos);
    addItem(play);

    //Ajout du bouton Option :
    Button * option = new Button("OPTIONS", buttonF);
    int spaceBetweenB = (10 * size.width()) / 1280;
    xPos = int(m_size.width()/2 - option->boundingRect().width()/2);
    yPos += play->boundingRect().height() + spaceBetweenB;

    option->setPos(xPos, yPos);
    addItem(option);

    //Ajout du bouton Quit :
    Button * quit = new Button("QUIT", buttonF);
    xPos = int(m_size.width()/2 - quit->boundingRect().width()/2);
    yPos += quit->boundingRect().height() + spaceBetweenB;
    quit->setPos(xPos, yPos);
    addItem(quit);

    //Connexion
    connect(play, SIGNAL(clicked()), m_controller, SLOT(firstLevel()));
    connect(quit, SIGNAL(clicked()), m_controller, SLOT(windowClose()));
}
