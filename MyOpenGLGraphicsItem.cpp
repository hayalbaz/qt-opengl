#include "MyOpenGLGraphicsItem.h"
#include <QOpenGLShaderProgram>

MyOpenGLGraphicsItem::MyOpenGLGraphicsItem(MyOpenGLGraphicsItem *parent)
    : parent(parent),
      modelMatrix(1, 0, 0, 0,
                  0, 1, 0, 0,
                  0, 0, 1, 0,
                  0, 0, 0, 1),
      widget(nullptr)
{

}

MyOpenGLGraphicsItem::~MyOpenGLGraphicsItem()
{
    for (auto *item : items) {
        delete item;
    }
}

void MyOpenGLGraphicsItem::initializeGL()
{
    initialize();
    for (auto *item : items) {
        item->initializeGL();
    }
}

void MyOpenGLGraphicsItem::paintGL(QOpenGLShaderProgram *program)
{
    program->setUniformValue("u_model", modelMatrix);
    paint(program);
    for (auto *item : items) {
        item->paintGL(program);
    }
}

void MyOpenGLGraphicsItem::setX(const float x)
{
    modelMatrix(0, 3) = x;
}

void MyOpenGLGraphicsItem::setY(const float y)
{
    modelMatrix(1, 3) = y;
}

float& MyOpenGLGraphicsItem::getX()
{
    return modelMatrix(0, 3);
}

float& MyOpenGLGraphicsItem::getY()
{
    return modelMatrix(1, 3);
}

void MyOpenGLGraphicsItem::setPos(const float x, const float y)
{
    setX(x);
    setY(y);
}

void MyOpenGLGraphicsItem::setPos(const QPointF &pos)
{
    setPos(pos.x(), pos.y());
}

void MyOpenGLGraphicsItem::move(const float dx, const float dy)
{
    getX() += dx;
    getY() += dy;
}

void MyOpenGLGraphicsItem::move(const QVector2D &dp)
{
    move(dp.x(), dp.y());
}

void MyOpenGLGraphicsItem::setWidget(MyOpenGLWidget *widget)
{
    this->widget = widget;
}

MyOpenGLWidget* MyOpenGLGraphicsItem::getWidget()
{
    return widget;
}
