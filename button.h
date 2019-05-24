#ifndef BUTTON_H
#define BUTTON_H
#include <QGraphicsRectItem>

class Button:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Button(QString text = "Default", QFont * font = nullptr, int scaled = 1,
           QBrush * brush = nullptr ,QGraphicsItem * parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void clicked();
private:
    QSize m_size;
    QString m_text;
    int m_scaled;
};

#endif // BUTTON_H
