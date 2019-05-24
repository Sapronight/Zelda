#include "button.h"
#include <QBrush>
#include <QGraphicsTextItem>
#include <QFont>

Button::Button(QString text, QFont * font, int scaled,QBrush * brush,QGraphicsItem * parent) : QGraphicsRectItem(parent)
{
    //Initialisation
    m_text = text;
    m_scaled = scaled;


    //Création du texte
    QGraphicsTextItem * name = new QGraphicsTextItem(text, this);
    if(font){
        name->setFont(*font);
    }

    //On dessine le rectangle :

    /*
     * On dessine un rectangle en fonction de la taille/police du text rentrer
     * On obtient ainsi un bouton avec une taille responsive sachant que le scaled
     * permet d'augmenter la taille de notre rectangle sans changer la taille
     * du texte.
    */
    m_size.setWidth(int(name->boundingRect().width()) * scaled);
    m_size.setHeight(int(name->boundingRect().height()) * scaled);

    setRect(0, 0, m_size.width(), m_size.height());
    if(brush){
        setBrush(*brush);
    }
    else {
        QBrush defaultBrush;
        defaultBrush.setStyle(Qt::SolidPattern);
        defaultBrush.setColor(Qt::darkCyan);
        setBrush(defaultBrush);
    }

    //On centre le text
    int xPos = int(m_size.width()/2 - name->boundingRect().width()/2);
    int yPos = int(m_size.height()/2 - name->boundingRect().height()/2);

    name->setPos(xPos, yPos);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event){
        emit clicked();
    }
}
