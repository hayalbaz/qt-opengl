#include "dvdplayerlogo.h"
#include "MyOpenGLWidget.h"

DVDPlayerLogo::DVDPlayerLogo(MyOpenGLGraphicsItem *parent)
    : RectOpenGLGraphicsItem(0, 0, 100, 100, parent),
      QObject(nullptr),
      velocity(0.5, 0.5)
{

}

void DVDPlayerLogo::onAdvance()
{
    auto *widget = getWidget();
    if (widget ==  nullptr) {
        return;
    }

    if (getX() + rect.width() > widget->width() || getX() < 0) {
        velocity.setX(velocity.x() * -1);
    }
    if (getY() + rect.height() > widget->height() || getY() < 0) {
        velocity.setY(velocity.y() * -1);
    }

    move(velocity);
}
