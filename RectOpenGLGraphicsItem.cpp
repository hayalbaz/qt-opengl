#include "RectOpenGLGraphicsItem.h"
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QVector2D>

RectOpenGLGraphicsItem::RectOpenGLGraphicsItem(qreal x, qreal y, qreal width, qreal height, MyOpenGLGraphicsItem *parent)
    : MyOpenGLGraphicsItem(parent),
      rect(x, y, width, height),
      vbo(nullptr),
      ibo(nullptr)
{
    setPos(x, y);
}

RectOpenGLGraphicsItem::RectOpenGLGraphicsItem(const QRect &rect, MyOpenGLGraphicsItem *parent)
    : MyOpenGLGraphicsItem(parent),
      rect(rect),
      vbo(nullptr),
      ibo(nullptr)
{
    setPos(rect.x(), rect.y());
}

RectOpenGLGraphicsItem::~RectOpenGLGraphicsItem()
{
    delete vao;
    delete vbo;
    delete ibo;
}

void RectOpenGLGraphicsItem::initialize()
{
    auto *ctx = QOpenGLContext::currentContext();
    auto *f = ctx->functions();

    vao = new QOpenGLVertexArrayObject;
    vao->create();
    vao->bind();

    auto height = static_cast<float>(rect.height());
    auto width = static_cast<float>(rect.width());
    const std::vector<QVector2D> vertices {
        {0.0f,  height},
        {width, height},
        {width, 0.0f},
        {0.0f,  0.0f}
    };
    vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo->create();
    vbo->bind();
    vbo->allocate(vertices.data(), vertices.size() * sizeof(QVector2D));
    f->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(QVector2D), 0);
    f->glEnableVertexAttribArray(0);

    static const std::vector<GLuint> indices {
        0, 1, 2,
        2, 3, 0
    };
    ibo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    ibo->create();
    ibo->bind();
    ibo->allocate(indices.data(), indices.size() * sizeof(GLuint));
}

void RectOpenGLGraphicsItem::paint(QOpenGLShaderProgram *program)
{
    vao->bind();
    auto *f = QOpenGLContext::currentContext()->functions();
    f->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
