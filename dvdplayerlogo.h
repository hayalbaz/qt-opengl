#ifndef DVDPLAYERLOGO_H
#define DVDPLAYERLOGO_H

#include "RectOpenGLGraphicsItem.h"
#include <QObject>

class DVDPlayerLogo : public QObject, public RectOpenGLGraphicsItem
{
    Q_OBJECT
public:
    DVDPlayerLogo(MyOpenGLGraphicsItem *parent = nullptr);

public slots:
    void onAdvance();

protected:
    QVector2D velocity;
};

#endif // DVDPLAYERLOGO_H
