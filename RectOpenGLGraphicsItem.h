#ifndef RECTOPENGLGRAPHICSITEM_H
#define RECTOPENGLGRAPHICSITEM_H

#include "MyOpenGLGraphicsItem.h"
#include <QRect>
#include <QMatrix4x4>

class QOpenGLBuffer;
class QOpenGLVertexArrayObject;
class RectOpenGLGraphicsItem : public MyOpenGLGraphicsItem
{
public:
    RectOpenGLGraphicsItem(qreal x, qreal y, qreal width, qreal height, MyOpenGLGraphicsItem *parent = nullptr);
    RectOpenGLGraphicsItem(const QRect &rect, MyOpenGLGraphicsItem *parent);
    virtual ~RectOpenGLGraphicsItem();

protected:
    virtual void initialize() override;
    virtual void paint(QOpenGLShaderProgram *program) override;

protected:
    QRectF rect;
    QOpenGLVertexArrayObject *vao;
    QOpenGLBuffer *vbo, *ibo;

};

#endif // RECTOPENGLGRAPHICSITEM_H
